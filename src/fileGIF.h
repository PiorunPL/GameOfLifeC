#include <stdio.h>

void initStreamList();
void addToStreamList(int number);
void mainCompressingFuction(int ** map);
void streamListToByteList(FILE * file);
int itemsInStreamList();
void clearList();
void initLZWList();
int searchForCode(char * name);
int addToList(char * name);
FILE * createGIF(char * dirName);
void initGIFHeader(int width, int height);
void writeGIFHeader(FILE * file);
void writeImageDescriptor(FILE * file);
void writeGraphicControlExtension(FILE * file);
void writeImageData(FILE * file);
void initImageData();
void writeEndOfFile(FILE * file);
void decimalToBin(int number, int digits, char * output);
void cleanHead();
void hexToByte(char * hex, char * hexByte, int number);
int binToDecimal(char * bin, int digits);
void clearStreamList();