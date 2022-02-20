#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    //open files
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL)
        exit(-1);

    fseek(f, 0, SEEK_END);
    const unsigned int filesize = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char *filemap = malloc(filesize);

    if (fread(filemap, filesize, 1, f) != 1)
        exit(100);
    fclose(f);

    //Read file header
    register unsigned char *header_reader = filemap;

    while (*header_reader != '\n')
    {
        header_reader++;
    }
    header_reader++;
    //read width
    register int width = 0;
    while (*header_reader != '\n')
    {
        width = width * 10 + *header_reader - '0';
        header_reader++;
    }
    header_reader++;
    //read height
    register int height = 0;
    while (*header_reader != '\n')
    {
        height = height * 10 + *header_reader - '0';
        header_reader++;
    }
    header_reader++;
    //skip constant
    while (*header_reader != '\n')
    {
        header_reader++;
    }
    header_reader++;

    //initialize variables
    register unsigned char *line1ptr = header_reader;
    register unsigned char *line2ptr = header_reader + 3 * width;
    register unsigned char *line3ptr = line2ptr + 3 * width;

    unsigned int histogram[6] = {0};
    register int grayscale;

    unsigned char *ptr = header_reader;

    //for each line
    for (register int v = 0; v < height; ++v)
    {
        for (register int h = 0; h < width; ++h)
        {
            unsigned char r = (*ptr++);
            unsigned char g = (*ptr++);
            unsigned char b = (*ptr++);
            printf("%d %d: %d %d %d\n", v, h, r, g, b);
        }
    }

    free(filemap);
    return 0;
}