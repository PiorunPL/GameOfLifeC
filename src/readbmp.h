#ifndef READBMP_H
#define READBMP_H

#include <stdio.h>

struct BMP_header {
    char name[2];
    unsigned int filesize;
    int garbage;
    unsigned int offset;
};

struct DIB_header {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitcount;
    unsigned int compression;
    unsigned int imagesize;
    unsigned int xppm;
    unsigned int yppm;
    unsigned int usedcolors;
    unsigned int importantcolors;
};

struct RGB {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct color_table {
    unsigned int usedcolors;
    struct RGB *colors;
};

FILE *isbmp(char *filename);

int readBMPh(FILE *file, struct BMP_header *header);

int readDIB(FILE *file, struct DIB_header *header);

int readCT(FILE *file, struct color_table *CT);

int **readbmp(FILE *file, int *rows, int *cols);

int **onebpp(FILE *file, struct BMP_header BMP, struct DIB_header DIB);

#endif
