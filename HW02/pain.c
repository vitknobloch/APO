#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    for (int r = 0; r < 256; r+=1)    {
        for(int g = 0; g < 256; g+=1){
            for(int b = 0; b < 256; b+=1){
                int no_trick = (int)round(0.2126 * (unsigned char)r + 0.7152 * (unsigned char)g + 0.0722 * (unsigned char)b);
                int trick = (int)((0.2126 * (unsigned char)r + 0.7152 * (unsigned char)g + 0.0722 * (unsigned char)b) + 0.5);

                if (trick != no_trick)
                    printf("%d %d \n", no_trick, trick);
            }
        }        
    }
    return 0;
}
