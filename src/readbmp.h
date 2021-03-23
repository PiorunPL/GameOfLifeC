#ifndef READBMP_H
#define READBMP_H

#include <stdio.h>

FILE *isbmp(char *filename);

int **readbmp(FILE *file, int *rows, int *cols);

#endif
