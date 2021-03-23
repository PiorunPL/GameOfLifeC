#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>

#include "fileOut.h"

//checking if dir exist, if not creating new one
void checkDIR(char * dirName)
{
    struct stat stats;
    stat(dirName, &stats);

    if (S_ISDIR(stats.st_mode))
    {
        //folder exists
    }
    else
    {  
        mkdir(dirName, 0777);
    }
}

//Creating BMP File with specific name based on iteration
char * createBMP(int iteration, int maxIteration, char *dirName)
{
    int iterationWorking = iteration;

    int n = log10(maxIteration) + 1;
    int m;

    if (iteration == 0)
    {
        m = 1;
    }
    else
    {
        m = log10(iteration) + 1;
    }

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

    char *path = malloc(sizeof(char) * (strlen(dirName) + strlen(fileName) + 2));
    strcpy(path, dirName);
    strcat(path, "/");
    strcat(path, fileName);

    free(fileName);

    return path;
}

//Writing into BMP File
void editBMP(int **map, int row, int col, char * path)
{
    int pixelNumber = row * col;
   

    FILE *file = fopen(path, "w");

    //BM
    fputc(0x42, file);
    fputc(0x4d, file);

    //Size of the BMP file (in bytes)
    int RowSize = ((col * 8 + 31) / 32) * 4;
    int BMPSize = 62 + 8 * row * RowSize;

    char *hex = malloc(sizeof(char) * 8);
    decimalToHex(BMPSize, hex, 8);

    char hexByte[4];
    hexByte[0] = 16 * hex[6] + hex[7];
    hexByte[1] = 16 * hex[4] + hex[5];
    hexByte[2] = 16 * hex[2] + hex[3];
    hexByte[3] = 16 * hex[0] + hex[1];

    int i;

    for (i = 0; i < 4; i++)
    {
        fputc(hexByte[i], file);
    }

    //unused
    for (i = 0; i < 4; i++)
        fputc(0x00, file);

    //offset where the pixel array can be found
    fputc(0x3e, file);
    for (i = 0; i < 3; i++)
        fputc(0x00, file);

    //Number of bytes in DIB header
    fputc(0x28, file);
    for (i = 0; i < 3; i++)
        fputc(0x00, file);

    //Width of bitmap in pixel
    int widthInPix = col * 8;
    decimalToHex(widthInPix, hex, 8);

    hexByte[0] = 16 * hex[6] + hex[7];
    hexByte[1] = 16 * hex[4] + hex[5];
    hexByte[2] = 16 * hex[2] + hex[3];
    hexByte[3] = 16 * hex[0] + hex[1];

    for (i = 0; i < 4; i++)
        fputc(hexByte[i], file);

    //Height of bitmap in pixel
    int heightInPix = row * 8;
    decimalToHex(heightInPix, hex, 8);

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
    int sizeRawBMP = 8 * row * RowSize;
    decimalToHex(sizeRawBMP, hex, 8);

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

    //colour 1 - green
    fputc(0x00,file);
    fputc(0xff,file);
    fputc(0x00,file);
    fputc(0x00,file);

    //colour 2 - white
    for (i = 0; i < 3; i++)
        fputc(0xff, file);
    fputc(0x00, file);

    //Including Map of Game of Life into the file(making squares 8x8 pixels)
    for (i = 0; i < row; i++)
    {
        int j = 0;
        for (j = 0; j < 8; j++)
        {
            int k = 0;
            for (k = 0; k < RowSize; k++)
            {
                if (k >= col)
                {
                    fputc(0x00, file);
                }
                else
                {
                    if (map[row - i - 1][k] == 1)
                    {
                        fputc(0x00, file);
                    }
                    else
                    {
                        fputc(0xff, file);
                    }
                }
            }
        }
    }

    fclose(file);
    free(hex);
    free(path);
}

//changing decimal number into hex number
void decimalToHex(int number, char *result, int digits)
{
    int remainder;
    int i = digits-1;

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
        result[i--] = 0;
    }
}

/*
* Funkcja zapisuje stan generacji do pliku
* rows - ilość wierszy
* cols - ilość kolumn
* *filename - ścieżka do pliku, do którego zapisać
*/
void saveGen(int **gen, int rows, int cols, char *filename){
    
    FILE *out = fopen(filename, "w");
    char firstline[32];
    sprintf(firstline, "%d %d\n", rows, cols);
    fputs( firstline, out );
    int i, j;
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            char actual[4];
            sprintf( actual, "%d", gen[i][j]);
            fputs( actual, out );
            if( j == (cols-1) )
                fputs( "\n", out );
            else
                fputs( " ", out );                                                 
        }
    }
    fclose(out);
}

