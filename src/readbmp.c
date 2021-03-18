#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "readbmp.h"

FILE *isbmp(char *filename) {
    FILE *file = NULL;
    int i = 0, j;

    while (&filename[i] != NULL) {
        if (filename[i++] == '.') {
            if (filename[i++] == 'b') {
                if (filename[i++] == 'm') {
                    if (filename[i++] == 'p') {
                        if (filename[i++] == '\0') {
                            file = fopen(filename, "rb");
                        }
                    }
                }
            }
            break;
        }
    }

    return file;
}

int readBMPh (FILE *file, struct BMP_header *header) {

    fread(header->name, sizeof(char), 2, file);

    if (header->name[0] != 'B' || header->name[1] != 'M') {
        fclose(file);
        return 1;
    }

    fread(&header->filesize, sizeof(int), 1, file);
    fread(&header->garbage, sizeof(int), 1, file);
    fread(&header->offset, sizeof(int), 1, file);

    printf("name: %c%c\n", header->name[0], header->name[1]);
    printf("filesize: %d\n", header->filesize);
    printf("garbage: %d\n", header->garbage);
    printf("offset: %d\n\n", header->offset);

    return 0;
}

    void prarr(int **array, int rows, int cols);
int readDIB(FILE *file, struct DIB_header *header) {
    fread(&header->size, 4, 1, file);

    if (header->size != 40) {
        fclose(file);
        return 1;
    }

    fread(&header->width, 4, 1, file);
    fread(&header->height, 4, 1, file);
    fread(&header->planes, 2, 1, file);
    fread(&header->bitcount, 2, 1, file);
    fread(&header->compression, 4, 1, file);

    if (header->compression != 0) {
        fclose(file);
        return 1;
    }

    fread(&header->imagesize, 4, 1, file);
    fread(&header->xppm, 4, 1, file);
    fread(&header->yppm, 4, 1, file);
    fread(&header->usedcolors, 4, 1, file);
    fread(&header->importantcolors, 4, 1, file);

    printf("size: %d\n", header->size);
    printf("width: %d\n", header->width);
    printf("height: %d\n", header->height);
    printf("planes: %d\n", header->planes);
    printf("bitcount: %d\n", header->bitcount);
    printf("compression: %d\n", header->compression);
    printf("image size: %d\n", header->imagesize);
    printf("x: %d\n", header->xppm);
    printf("y: %d\n", header->yppm);
    printf("used: %d\n", header->usedcolors);
    printf("important: %d\n\n", header->importantcolors);

    return 0;
}
/*
int readCT(FILE *file, struct color_table *CT) {
    struct color_table *tab;

    printf("num: %d\n", CT->usedcolors);

    int i;
    for (i = 0; i < CT->usedcolors; i++) {
        fread(&CT->colors[i].blue, 1, 1, file);
        fread(&CT->colors[i].green, 1, 1, file);
        fread(&CT->colors[i].red, 1, 1, file);

        printf("red: %d\n", CT->colors[i].red);
        printf("green: %d\n", CT->colors[i].red);
        printf("blue: %d\n", CT->colors[i].red);
        printf("reserved: %d\n\n", CT->colors[i].red);
    }

    return 0;
}
*/
int **readbmp(FILE *file, int *rows, int *cols) {
    struct BMP_header BMP;
    struct DIB_header DIB;
    struct color_table CT;

    readBMPh(file, &BMP);
    readDIB(file, &DIB);

    CT.usedcolors = pow(2, DIB.bitcount);
    
    CT.colors = malloc(CT.usedcolors * sizeof(struct color_table));

    //readCT(file, &CT); 

    *rows = DIB.height;
    *cols = DIB.width;

    unsigned int rowsize = ((*cols + 31) / 32) * 4;

    printf("rowsize: %d\n\n", rowsize);

    int **generation = malloc(*rows * sizeof(int *));

    int i, j, bit;
    unsigned char tmp;
    unsigned char byte[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    unsigned int tmpoffset = BMP.offset;

    for (i = *rows - 1; i >= 0; i--) {
        fseek(file, tmpoffset, SEEK_SET);
        generation[i] = malloc(*cols * sizeof(int));

        for (j = 0; j < *cols; j++) {
            fread(&tmp, 1, 1, file);

            for (bit = 7; bit >= 0; bit--, j++) {
                if (byte[bit] & tmp == pow(2, bit)) generation[i][j] = 1;
                else generation[i][j] = 0;
            }
        }
        tmpoffset += rowsize;
    }

    prarr(generation, *rows, *cols);

    return generation;
}

void prarr(int **array, int rows, int cols) {
    int r, c;

    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++)
            printf("%d ", array[r][c]);
        printf("\n");
    }
    printf("\n");
}
