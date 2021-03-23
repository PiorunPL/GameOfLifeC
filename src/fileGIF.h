#ifndef FILEGIF_H
#define FILEGIF_H

void GIFInit(char * dirname, int cols, int rows);
void writeToGIF(int ** map);
void writeEndOfFile();
#endif
