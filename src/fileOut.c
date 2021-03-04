#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void creatingBMP(int **map, int row, int col, int iteration, int maxIteration, char *dirName)
{
    int pixelNumber = row * col;
    int iterationWorking = iteration;

    int n = log10(maxIteration) + 1;
    int m = log10(iteration) + 1;

    char *fileName = malloc(sizeof(char) * n + 5);

    int i = 0;
    for (i = 0; i < n - m; i++)
    {
        fileName[i] = '0';
    }

    for (i = n - 1; i > n - m - 1; i--)
    {
        fileName[i] = (iterationWorking % 10) + '0';
        iterationWorking = iterationWorking / 10;
    }

    fileName[n] = '.';
    fileName[n + 1] = 'b';
    fileName[n + 2] = 'm';
    fileName[n + 3] = 'p';
    fileName[n + 4] = '\0';

    DIR *dir = opendir(dirName);

    if (dir)
    {
        //folder exists
        closedir(dir);
    }
    else if (ENOENT == errno)
    {
        //folder does not exists
        mkdir(dirName, 0777);
    }
    else
    {
        //opening folder failed
        printf("Wystapił problem z folderem docelowym!");
        return;
    }

    FILE *file = open(strcat(strcat(dirName, '/'),fileName), "w");

    //BM
    fputc(0x42, file);
    fputc(0x4d, file);

    //Size of the BMP file (in bytes)
    int BMPSize = 62 + 8 * pixelNumber;

    char *hex = malloc(sizeof(char) * 8);
    decimalToHex(BMPSize, hex);

    char hexByte[4];
    hexByte[0] = 16 * hex[6] + hex[7];
    hexByte[1] = 16 * hex[4] + hex[5];
    hexByte[2] = 16 * hex[2] + hex[3];
    hexByte[3] = 16 * hex[0] + hex[1];

    for (i = 0; i < 4; i++)
    {
        fputc(hexByte[i], file);
    }

    //unused
    for (i = 0; i < 4; i++)
        fputc(0x00, file);

    //offset where the pixel array can be found
    fputc(0x3e, file);

    //Number of bytes in DIB header
    fputc(0x28, file);
    for (i = 0; i < 3; i++)
        fputc(0x00, file);

    //Width of bitmap in pixel
    int widthInPix = col * 8;
    decimalToHex(widthInPix, hex);

    hexByte[0] = 16 * hex[6] + hex[7];
    hexByte[1] = 16 * hex[4] + hex[5];
    hexByte[2] = 16 * hex[2] + hex[3];
    hexByte[3] = 16 * hex[0] + hex[1];

    for (i = 0; i < 4; i++)
        fputc(hexByte[i], file);

    //Height of bitmap in pixel
    int heightInPix = row * 8;
    decimalToHex(heightInPix, hex);

    hexByte[0] = 16 * hex[6] + hex[7];
    hexByte[1] = 16 * hex[4] + hex[5];
    hexByte[2] = 16 * hex[2] + hex[3];
    hexByte[3] = 16 * hex[0] + hex[1];

    for (i = 0; i < 4; i++)
        fputc(hexByte[i], file);

    //Number of color planes
    fputc(0x01, file);
    fputc(0x00, file);

    //Number of bits per pixel
    fputc(0x01, file);
    fputc(0x00, file);

    //compression used (NO Compression)
    for (i = 0; i < 4; i++)
        fputc(0x00, file);

    //size of the raw bitmap
    int sizeRawBMP = 8 * pixelNumber;
    decimalToHex(sizeRawBMP, hex);

    hexByte[0] = 16 * hex[6] + hex[7];
    hexByte[1] = 16 * hex[4] + hex[5];
    hexByte[2] = 16 * hex[2] + hex[3];
    hexByte[3] = 16 * hex[0] + hex[1];

    for (i = 0; i < 4; i++)
        fputc(hexByte[i], file);

    //resolution
    for (i = 0; i < 8; i++)
        fputc(0x00, file);

    //Number of colors in palette
    for (i = 0; i < 4; i++)
        fputc(0x00, file);

    //Importants of colors(0 means all are important)
    for (i = 0; i < 4; i++)
        fputc(0x00, file);

    //colour 1 - black
    for (i = 0; i < 4; i++)
        fputc(0x00, file);

    //colour 2 - white
    for (i = 0; i < 3; i++)
        fputc(0xff, file);
    fputc(0x00, file);

    for (i = 0; i < row; i++)
    {
        int j = 0;
        for (j = 0; j < 8; j++)
        {
            int k = 0;
            for (k = 0; k < col; k++)
            {
                int l = 0;
                for (l = 0; l < 8; l++)
                {
                    fputc(map[row][col], file);
                }
            }
        }
    }

    fclose(file);
    free(hex);
    free(fileName);
}

void decimalToHex(int number, char *result)
{
    int remainder;
    int i = 7;

    while (number != 0)
    {
        remainder = number % 16;

        if (remainder < 10)
            result[i--] = remainder;
        else
            result[i--] = remainder;

        number = number / 16;
    }

    while (i >= 0)
    {
        result[i--] = '0';
    }
}

int hexDigitsFunc(int number)
{
    int hexDigits = 0;
    while (number != 0)
    {
        number = number / 16;
        hexDigits++;
    }
    return hexDigits;
}