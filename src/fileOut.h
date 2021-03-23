#ifndef FILEOUT_H
#define FILEOUT_H

char * createBMP(int iteration, int maxIteration, char *dirName);
void editBMP(int **map, int row, int col, char * path);
void checkDIR(char * dirName);
void decimalToHex(int number, char *result, int digits);
void saveGen(int **gen, int rows, int cols, char *filename);

#endif
