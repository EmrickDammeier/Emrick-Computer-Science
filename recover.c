#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
#define FILENAME_LENGTH 8

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) // Check for correct number of arguments
    {
        fprintf(stderr, "Usage: %s IMAGE\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r"); // opens file image
    if (!file) // checks if file can be open
    {
        fprintf(stderr, "Could not open %s for reading\n", argv[1]);
        return 1;
    }
// Variables needed for JPEG
    FILE *img = NULL;
    char filename[FILENAME_LENGTH];
    int img_count = 0;
    BYTE buffer[BLOCK_SIZE];
// Iterates over blocks
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // Formula that is required
        {
            if (img)
                fclose(img); // closes image if already open

            sprintf(filename, "%03d.jpg", img_count++);
            img = fopen(filename, "w"); // creates new file
            if (!img)
            {
                fclose(file);
                fprintf(stderr, "Could not create %s\n", filename);
                return 1;
            }
        }

        if (img)
            fwrite(buffer, 1, BLOCK_SIZE, img);
    }

    if (img)
        fclose(img); // closes the last file

    fclose(file); // closes forensic file

    return 0;
}
