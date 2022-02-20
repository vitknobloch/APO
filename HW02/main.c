#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    //open files
    FILE* f_in = fopen(argv[1], "rb");
    FILE* f_out = fopen("output.ppm", "wb");

    int w_temp;
    int h_temp;
    if(fscanf(f_in, "%*c %*c %d %d %*d%*c", &w_temp, &h_temp) != 2)
        exit(100);
    register int width = w_temp;
    register int height = h_temp;
    //copy header
    fprintf(f_out, "P6\n%d\n%d\n255\n", width, height);
    
    unsigned char *line_buffer = malloc(width * 3 * 3);

    //initialize moving pointers
    register unsigned char *line_prev = line_buffer;
    register unsigned char *line_cur = line_prev + 3*width;
    register unsigned char *line_next = line_cur + 3*width;
    register unsigned char *outptr = line_buffer;
    //initialize stable pointers
    register unsigned char *line_buffer_prev = line_prev;
    register unsigned char *line_buffer_cur = line_cur;
    register unsigned char *line_buffer_next = line_next;
    register unsigned char *line_buffer_out = outptr;

    if(fread(line_buffer_cur, width * 3 * 2, 1, f_in)!=1)
        exit(100);

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
    fwrite(line_buffer_cur, width*3, 1, f_out);
    for(register int i = 0; i < width; ++i){
        r = *(line_cur++);
        g = *(line_cur++);
        b = *(line_cur++);
        grayscale = (int)((0.2126 * r + 0.7152 * g + 0.0722 * b) + 0.5);
        histogram[grayscale / 51] += 1;
    }

    //for each line
    for(register int v = 0; v < height-2; ++v){
        //rotate lines
        line_next = line_buffer_prev;
        line_buffer_prev = line_buffer_cur;
        line_buffer_cur = line_buffer_next;
        line_buffer_next = line_next;
        line_buffer_out = line_buffer_prev;
        //load next line
        if(fread(line_buffer_next, width*3, 1, f_in) != 1)
            exit(100);

        //reset moving pointers to start of line
        line_prev = line_buffer_prev + 3;
        line_cur = line_buffer_cur;
        line_next = line_buffer_next + 3;
        outptr = line_buffer_out;

        //copy first pixel
        r = *(line_cur++);
        g = *(line_cur++);
        b = *(line_cur++);
        grayscale = (int)((0.2126 * r + 0.7152 * g + 0.0722 * b) + 0.5);
        histogram[grayscale / 51] += 1;
        *(outptr++) = r;
        *(outptr++) = g;
        *(outptr++) = b;

        rn = *(line_cur++);
        gn = *(line_cur++);
        bn = *(line_cur++);

        //copy pixels in between
        for(register int h = 0; h < width - 2; ++h){
            //shift window
            rp = r; gp = g; bp = b;
            r = rn; g = gn; b = bn;
            rn = *(line_cur++);
            gn = *(line_cur++);
            bn = *(line_cur++);
            //calculate output
            //red
            ro = 5*r - rp - rn - *(line_prev++) - *(line_next++);
            if (ro > 0xff)
            {
                ro = 0xff;
            }
            else if (ro < 0x00)
            {
                ro = 0x00;
            }
            //green
            go = 5*g - gp - gn - *(line_prev++) - *(line_next++);
            if (go > 0xff)
            {
                go = 0xff;
            }
            else if (go < 0x00)
            {
                go = 0x00;
            }
            //blue
            bo = 5*b - bp - bn - *(line_prev++) - *(line_next++);
            if (bo > 0xff)
            {
                bo = 0xff;
            }
            else if (bo < 0x00)
            {
                bo = 0x00;
            }
            
            //histogram
            grayscale = (int)((0.2126 * ro + 0.7152 * go + 0.0722 * bo) + 0.5);
            histogram[grayscale / 51] += 1;
            //save
            *(outptr++) = ro;
            *(outptr++) = go;
            *(outptr++) = bo;

        }

        //copy last pixel
        grayscale = (int)((0.2126 * rn + 0.7152 * gn + 0.0722 * bn) + 0.5);
        histogram[grayscale / 51] += 1;
        *(outptr++) = rn;
        *(outptr++) = gn;
        *(outptr++) = bn;

        fwrite(line_buffer_out, width*3, 1, f_out);
    }

    //copy last line
    line_cur = line_buffer_next;
    fwrite(line_buffer_next, width*3, 1, f_out);
    for (register int i = 0; i < width; ++i){
        r = *(line_cur++);
        g = *(line_cur++);
        b = *(line_cur++);
        grayscale = (int)((0.2126 * r + 0.7152 * g + 0.0722 * b) + 0.5);
        histogram[grayscale / 51] += 1;
    }

    fclose(f_in);
    fclose(f_out);

    FILE *out_histogram = fopen("output.txt", "w");
    fprintf(out_histogram, "%u %u %u %u %u", histogram[0], histogram[1], histogram[2], histogram[3], histogram[4] + histogram[5]);
    fclose(out_histogram);

    free(line_buffer);

    return 0;
}
