#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *f = fopen(argv[1], "rb");

    fseek(f, 0, SEEK_END);
    const unsigned int filesize = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char *filemap = malloc(filesize);
    unsigned char *outfile = malloc(filesize);

    if (fread(filemap, filesize, 1, f) != 1)
        exit(100);
    fclose(f);

    //Read file header
    register unsigned char *header_reader = filemap;
    register unsigned char *outptr = outfile;
    while (*header_reader != '\n')
    {
        *(outptr++) = *(header_reader++);
    }
    *(outptr++) = *(header_reader++);
    //read width
    register int width = 0;
    while (*header_reader != '\n')
    {
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
    while (*header_reader != '\n')
    {
        *(outptr++) = *(header_reader++);
    }
    *(outptr++) = *(header_reader++);

    unsigned int histogram[6] = {0};

        

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
