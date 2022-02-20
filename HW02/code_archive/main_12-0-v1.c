#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    //open files
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
    register int width = 0;
    while(*header_reader != '\n'){
        width = width * 10 + *header_reader - '0';
        *(outptr++) = *(header_reader++);
    }
    *(outptr++) = *(header_reader++);
    //read height
    register int height = 0;
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

    //initialize variables
    register unsigned char *line1ptr = header_reader;
    register unsigned char *line2ptr = header_reader + 3*width;
    register unsigned char *line3ptr = line2ptr + 3*width;

    unsigned int histogram[6] = {0};
    register int grayscale;

    //current colors
    register unsigned char r, g, b;
    //previous colors
    register unsigned char rp, gp, bp;
    //next colors
    register unsigned char rn, gn, bn;
    //output colors
    register int ro, go, bo;

    //copy first line
    for(register int i = 0; i < width; ++i){
        r = *(line1ptr++);
        g = *(line1ptr++);
        b = *(line1ptr++);
        grayscale = (int)round(0.2126 * r + 0.7152 * g + 0.0722 * b);
        histogram[grayscale / 51] += 1;
        *(outptr++) = r;
        *(outptr++) = g;
        *(outptr++) = b;
    }
    
    line1ptr = header_reader;

    //for each line
    for(register int v = 0; v < height-2; ++v){
        //copy first pixel
        r = *(line2ptr++);
        g = *(line2ptr++);
        b = *(line2ptr++);
        grayscale = (int)round(0.2126 * r + 0.7152 * g + 0.0722 * b);
        histogram[grayscale / 51] += 1;
        *(outptr++) = r;
        *(outptr++) = g;
        *(outptr++) = b;
        line1ptr += 3;
        line3ptr += 3;

        rn = *(line2ptr++);
        gn = *(line2ptr++);
        bn = *(line2ptr++);

        //copy pixels in between
        for(register int h = 0; h < width - 2; ++h){
            //shift window
            rp = r; gp = g; bp = b;
            r = rn; g = gn; b = bn;
            rn = *(line2ptr++);
            gn = *(line2ptr++);
            bn = *(line2ptr++);
            //calculate output
            //red
            ro = 5*r - rp - rn - *(line1ptr++) - *(line3ptr++);
            if (ro > 0xff)
            {
                ro = 0xff;
            }
            else if (ro < 0x00)
            {
                ro = 0x00;
            }
            //green
            go = 5*g - gp - gn - *(line1ptr++) - *(line3ptr++);
            if (go > 0xff)
            {
                go = 0xff;
            }
            else if (go < 0x00)
            {
                go = 0x00;
            }
            //blue
            bo = 5*b - bp - bn - *(line1ptr++) - *(line3ptr++);
            if (bo > 0xff)
            {
                bo = 0xff;
            }
            else if (bo < 0x00)
            {
                bo = 0x00;
            }
            
            //histogram
            grayscale = (int)round(0.2126 * ro + 0.7152 * go + 0.0722 * bo);
            histogram[grayscale / 51] += 1;
            //save
            *(outptr++) = ro;
            *(outptr++) = go;
            *(outptr++) = bo;
        }

        //copy last pixel
        grayscale = (int)round(0.2126 * rn + 0.7152 * gn + 0.0722 * bn);
        histogram[grayscale / 51] += 1;
        *(outptr++) = rn;
        *(outptr++) = gn;
        *(outptr++) = bn;
        line1ptr += 3;
        line3ptr += 3;
    }

    //copy last lane
    for (register int i = 0; i < width; ++i){
        r = *(line2ptr++);
        g = *(line2ptr++);
        b = *(line2ptr++);
        grayscale = (int)round(0.2126 * r + 0.7152 * g + 0.0722 * b);
        histogram[grayscale / 51] += 1;
        *(outptr++) = r;
        *(outptr++) = g;
        *(outptr++) = b;
    }

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
