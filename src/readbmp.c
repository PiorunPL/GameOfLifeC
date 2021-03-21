#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "readbmp.h"

/*
 *  This function checks if filename includes '.bmp', which is a clue
 *  it could be BMP file. It returns file pointer in case of success.
 */
FILE *isbmp(char *filename) {
    FILE *file = NULL;
    int i = 0, j;

    while (filename[i] != '\0') {
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

/*
 *  This fuction reads BMP header and writes data into BMP_header structure.
 *  Returns 1 (error) or 2 (wrong values in header) if failed and 0 if succeed.
 */
int readBMPh (FILE *file, struct BMP_header *header) {
    if (fread(header->name, 1, 2, file) != 2) return 1;

    if (header->name[0] != 'B' || header->name[1] != 'M') {
        fprintf(stderr, "Wrong values in header field: 0x%X and 0x%X.\n"
                        "Instead of 0x42 and 0x4D.\n\n", header->name[0], header->name[1]);
        return 2;
    }

    if (fread(&header->filesize, 4, 1, file) != 1) return 1;
    if (fread(&header->garbage, 4, 1, file) != 1) return 1;
    if (fread(&header->offset, 4, 1, file) != 1) return 1;

    return 0;
}

/*
 *  This function reads DIB header and writes data into DIB_header structure.
 *  Returns 1 (error) or 2 (wrong values in header) if failed and 0 if succeed.
 */
int readDIB(FILE *file, struct DIB_header *header) {
    if (fread(&header->size, 4, 1, file) != 1) return 1;
    if (header->size != 40) return 1;

    if (fread(&header->width, 4, 1, file) != 1) return 1;
    if (fread(&header->height, 4, 1, file) != 1) return 1;
    if (fread(&header->planes, 2, 1, file) != 1) return 1;

    if (header->planes != 1) {
        fprintf(stderr, "Wrong number of planes: %d.\n\n", header->planes);
        return 2;
    }

    if (fread(&header->bitcount, 2, 1, file) != 1) return 1;
    if (fread(&header->compression, 4, 1, file) != 1) return 1;

    if (header->compression != 0) {
        fprintf(stderr, "This file is compressed.\n"
                        "Compressed files are not supported.\n\n");
        return 2;
    }

    if (fread(&header->imagesize, 4, 1, file) != 1) return 1;
    if (fread(&header->xppm, 4, 1, file) != 1) return 1;
    if (fread(&header->yppm, 4, 1, file) != 1) return 1;
    if (fread(&header->usedcolors, 4, 1, file) != 1) return 1;
    if (fread(&header->importantcolors, 4, 1, file) != 1) return 1;

    return 0;
}

/*
 *  This function reads array of pixels into array of ints.
 *  It reads array of pixels of BMP file with 1 bpp color depth.
 *  Returns NULL if failed and pointer to the array if succeed.
 */
int **onebpp(FILE *file, struct BMP_header BMP, struct DIB_header DIB) {
    unsigned int rowsize = ((DIB.width + 31) / 32) * 4;

    int **generation;
    if ((generation = (int **)malloc(DIB.height * sizeof(int *))) == NULL) return NULL;

    int i, j, k, bit;
    unsigned char tmp;
    unsigned char byte[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    unsigned int tmpoffset = BMP.offset;

    for (i = DIB.height - 1; i >= 0; i--) {
        if (fseek(file, tmpoffset, SEEK_SET) == -1) return NULL;
        if ((generation[i] = (int *)malloc(DIB.width * sizeof(int))) == NULL) return NULL;

        for (j = 0; j < DIB.width; j++) {
            if (fread(&tmp, 1, 1, file) != 1) return NULL;

            for (bit = 7, k = 0; bit >= 0 && j < DIB.width; bit--, j++) {
                if ((byte[bit] & tmp) == pow(2, bit)) generation[i][j] = 0;
                else generation[i][j] = 1;
            }
            j--;
        }
        tmpoffset += rowsize;
    }

    return generation;
}

/*
 *  This function is responsible for management of BMP file reading.
 *  It controls other functions aimed for reading parts of BMP file.
 *  Returns NULL if failed and pointer to the array of ints with pixel
 *  map in it if succeed. In case of success it also changes values of 
 *  rows and columns passed to the function.
 */
int **readbmp(FILE *file, int *rows, int *cols) {
    struct BMP_header BMP;
    struct DIB_header DIB;
    struct color_table CT;
    int returned;

    if ((returned = readBMPh(file, &BMP)) == 1) {
        fprintf(stderr, "BMP header cannot be read correctly.\n\n");
        return NULL;
    }
    else if (returned == 2) {
        fprintf(stderr, "Data inside BMP header is not correct.\n\n");
        return NULL;
    }

    if ((returned = readDIB(file, &DIB)) == 1) {
        fprintf(stderr, "DIB header cannot be read correctly.\n\n");
        return NULL;
    }
    else if (returned == 2) {
        fprintf(stderr, "Data inside DIB header is not correct.\n\n");
        return NULL;
    }


    if (DIB.bitcount == 1) {
        *rows = DIB.height;
        *cols = DIB.width;
        return onebpp(file, BMP, DIB);
    }
    else {
        fprintf(stderr, "This file has %d bits per pixel color depth. "
                        "This kind of files are not supported..\n\n", DIB.bitcount);
        return NULL;
    }
}
