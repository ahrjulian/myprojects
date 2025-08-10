#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{

    if (argc != 2)//check if command line argument is valid
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    int j = 0;//j = Anzahl der gefundenen JPEG files
    FILE*card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 1;
    }
    uint8_t buffer[512];//each chunck has 512 bytes
    char filename[8];
    FILE*img = NULL;
    while (fread(buffer, 1, 512, card) == 512)
    {
        //create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)//if this statement true, JPEG f, "w");
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg",j);//declare filename
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(card);
                return 1;
            }
            j++;
        }
        if (img != NULL)
        {
            //keep writing to it
            fwrite(buffer, 1, 512, img);

        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
    return 0;
}

