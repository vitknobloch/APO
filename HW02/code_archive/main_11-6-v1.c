#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    FILE* f = fopen(argv[1], "rb");

    fseek(f, 0, SEEK_END);
    const unsigned int filesize = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char *filemap = malloc(filesize);
    unsigned char *outfile = malloc(filesize);

    if(fread(filemap, filesize, 1, f) != 1)
        exit(100);
    fclose(f);

    //Read file header
    register unsigned char *header_reader = filemap;
    register unsigned char *outptr = outfile;
    while(*header_reader != '\n'){
        *(outptr++) = *(header_reader++);
    }
    *(outptr++) = *(header_reader++);
    //read width
    int width = 0;
    while(*header_reader != '\n'){
        width = width * 10 + *header_reader - '0';
        *(outptr++) = *(header_reader++);
    }
    *(outptr++) = *(header_reader++);
    //read height
    int height = 0;
    while (*header_reader != '\n')
    {
        height = height * 10 + *header_reader - '0';
        *(outptr++) = *(header_reader++);
    }
    *(outptr++) = *(header_reader++);
    //skip constant
    while(*header_reader != '\n'){
        *(outptr++) = *(header_reader++);
    }
    *(outptr++) = *(header_reader++);

    register unsigned char *line1ptr = header_reader;
    register unsigned char *line2ptr = header_reader + 3*width;
    register unsigned char *line3ptr = line2ptr + 3*width;

    unsigned int histogram[6] = {0};
    register int grayscale;

    //copy first line
    for(int i = 0; i < 3*width; ++i){
        if (!(i % 3) && i > 0){
            grayscale = (int)round(0.2126 * *(outptr - 3) + 0.7152 * *(outptr - 2) + 0.0722 * *(outptr - 1));
            histogram[grayscale / 51] += 1;
        }
        *(outptr++) = *(line1ptr++);
    }
    grayscale = (int)round(0.2126 * *(outptr - 3) + 0.7152 * *(outptr - 2) + 0.0722 * *(outptr - 1));
    histogram[grayscale / 51] += 1;
    line1ptr = header_reader;

    //for each line
    register int sum;
    for(int v = 0; v < height-2; ++v){
        //copy first pixel
        for (int i = 0; i < 3; ++i){
            *(outptr++) = (*line2ptr++);
        }
        line1ptr += 3;
        line3ptr += 3;

        //copy pixels in between
        for(int h = 0; h < width*3 - 6; ++h){

            if (!(h % 3)){ //histogram count
                grayscale = (int)round(0.2126 * *(outptr - 3) + 0.7152 * *(outptr - 2) + 0.0722 * *(outptr - 1));
                histogram[grayscale / 51] += 1;
            }
            sum = 5*(*line2ptr) - *(line1ptr) - *(line2ptr-3) - *(line2ptr+3) - *(line3ptr);
            line2ptr++; line1ptr++; line3ptr++;
            if(sum > 0xff){
                sum = 0xff;
            }                
            else if(sum < 0x00){
                sum = 0x00;
            }
            *(outptr++) = sum;
        }
        grayscale = (int)round(0.2126 * *(outptr - 3) + 0.7152 * *(outptr - 2) + 0.0722 * *(outptr - 1));
        histogram[grayscale / 51] += 1;

        //copy last pixel
        for (int i = 0; i < 3; ++i){
            *(outptr++) = (*line2ptr++);
        }
        line1ptr += 3;
        line3ptr += 3;
        grayscale = (int)round(0.2126 * *(outptr - 3) + 0.7152 * *(outptr - 2) + 0.0722 * *(outptr - 1));
        histogram[grayscale / 51] += 1;
    }

    //copy last lane
    for (int i = 0; i < 3 * width; ++i)
    {
        if (!(i % 3) && i > 0)
        {
            grayscale = (int)round(0.2126 * *(outptr - 3) + 0.7152 * *(outptr - 2) + 0.0722 * *(outptr - 1));
            histogram[grayscale / 51] += 1;
        }
        *(outptr++) = *(line2ptr++);
    }
    grayscale = (int)round(0.2126 * *(outptr - 3) + 0.7152 * *(outptr - 2) + 0.0722 * *(outptr - 1));
    histogram[grayscale / 51] += 1;

    FILE *out = fopen("output.ppm", "wb");
    fwrite(outfile, filesize, 1, out);
    fclose(out);

    FILE *out_histogram = fopen("output.txt", "w");
    fprintf(out_histogram, "%u %u %u %u %u", histogram[0], histogram[1], histogram[2], histogram[3], histogram[4] + histogram[5]);
    fclose(out_histogram);

    free(filemap);
    free(outfile);
    return 0;
}
