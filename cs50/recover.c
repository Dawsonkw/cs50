#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define JAR 512

typedef unsigned char BYTE;
 
int main(int argc, char *argv[])
{
    // Check for invalid usage
    if(argc != 2)
    {
        printf("Usage: recover [filename.raw]\n");
        return 1;
    }
    
    char* card = argv[1];
   
    // Open file or return error message if not able to open
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    
    BYTE buffer[JAR];
    
    int counter;
    counter = 0;
    
    FILE* img;
    
    char pic[8];
    
    while (fread(buffer, sizeof(buffer), 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter > 0)
            {
                fclose(img);
                
                sprintf(pic, "%03d.jpg", counter);
                counter += 1;
                
                img = fopen(pic, "w");
                
                fwrite(buffer, sizeof(buffer), 1, img);
            }
            if (counter == 0)
            {
                sprintf(pic, "%03d.jpg", counter);
                counter += 1;
                
                img = fopen(pic, "w");
                
                fwrite(buffer, sizeof(buffer), 1, img);
            }
        }
        
        else if (counter > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }
        
    }
    
    fclose(img);
    fclose(file);
    return 0;
}
    
    

    
    // Look for beginning of JPEG file --> use JPEG header signature --> fread(data, size, number, inptr);
    // Open new JPEG file
    // Write 512 bytes until new JPEG file is found  --> fwrite(data, size, number, outptr);
    // Stop at end of file
    
    // open memory card
    // repeat until end of card:
        // read 512 bytes into a buffer
        // if start of new JPEG
            // if first JPEG
            // ... 
            // Else
            // ...
        // Else
            // if already found JPEG
            // ...
    // Close any remaining files