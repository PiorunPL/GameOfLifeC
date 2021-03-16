#include <stdio.h>

#include "fileOut.h"

typedef struct LogicalScreenDescriptor
{
    int width;
    int height;

    int globalColorTable;
    int colorRes;
    int sortFlag;
    int sizeOfGlobalColorTable;
    char * packedField;

    int backgroundColorIndex;
    int pxAscpectRatio;
}LogicalScreenDescriptor_t;

typedef struct GlobalColorTable
{
    char * color1;
    char * color2;
}GlobalColorTable_t;

typedef struct ApplicationExtensionBlock
{
    char * extentionName;
    char * applicationName;
    int lengthOfDataBlock;
    int numberLoop;
}ApplicationExtensionBlock_t;

typedef struct GraphicControlExtension
{
    char * extensionHeader;
    char byteSize;
    char packedField;
    int delayTime;
    char transparentColorIndex;
}GraphicControlExtension_t;

typedef struct ImageDescriptor
{
    char imageSeparator;
    char * imageLeft;
    char * imageTop;
    int imageWidth;
    int imageHeight;
    char packedField;   //There are options such as local color table
                        //but it won't be used in this program (everything 0)
}ImageDescriptor_t;

typedef struct GIFHeader
{
    char * header;
    LogicalScreenDescriptor_t LSD;
    GlobalColorTable_t GCT;
    ApplicationExtensionBlock_t AEB;
    GraphicControlExtension_t GCE;
    ImageDescriptor_t ID;
}GIFHeader_t;

//Do przemyślenia
typedef struct ImageData
{
    char LZWMinimumCodeSize;
    char * sizeOfDataBlock;
}ImageData_t;



static GIFHeader_t * head = NULL;

FILE * createGIF(char * dirName)
{
    char * fileName = "life.gif";

    char *path = malloc(sizeof(char) * (strlen(dirName) + strlen(fileName) + 2));
    strcpy(path, dirName);
    strcat(path, "/");
    strcat(path, fileName);

    FILE * fGIF = fopen(path, "w");
    free(path);

    return fGIF;
}

void initGIFHeader(int width, int height)
{
    head = malloc(sizeof(GIFHeader_t));
    head->header = "GIF89a";

//LogicalScreenDescriptor
    head->LSD.width = width;
    head->LSD.height = height;
    head->LSD.globalColorTable = 1;
    head->LSD.colorRes = 0;         // 1 bit/pixel
    head->LSD.sortFlag = 0;
    head->LSD.sizeOfGlobalColorTable = 0; 
    head->LSD.backgroundColorIndex = 0;
    head->LSD.pxAscpectRatio = 0;

    char * sizeOfGCTChar = malloc(sizeof(char)*4);
    decimalToBin(head->LSD.sizeOfGlobalColorTable, 3, sizeOfGCTChar);
    char * colorResChar = malloc(sizeof(char)*4);    
    decimalToBin(head->LSD.colorRes, 3, colorResChar);

    head->LSD.packedField = malloc(sizeof(char)*9);
    head->LSD.packedField[0] = head->LSD.globalColorTable;
    head->LSD.packedField[1] = colorResChar[0];
    head->LSD.packedField[2] = colorResChar[1];
    head->LSD.packedField[3] = colorResChar[2];
    head->LSD.packedField[4] = head->LSD.sortFlag;
    head->LSD.packedField[5] = sizeOfGCTChar[0];
    head->LSD.packedField[6] = sizeOfGCTChar[1];
    head->LSD.packedField[7] = sizeOfGCTChar[2];
    head->LSD.packedField[8] = '\0';

    free(colorResChar);
    free(sizeOfGCTChar);

//GlobalColorTable
    //Color 1 = white
    head->GCT.color1 = malloc(sizeof(char)*4);
    head->GCT.color1[0] = 0xff;     //Red
    head->GCT.color1[1] = 0xff;     //Green
    head->GCT.color1[2] = 0xff;     //Blue
    head->GCT.color1[3] = '\0';

    //Color 2 = green
    head->GCT.color2 = malloc(sizeof(char)*4);
    head->GCT.color2[0] = 0x00;     //Red
    head->GCT.color2[0] = 0xff;     //Green
    head->GCT.color2[0] = 0x00;     //Blue
    head->GCT.color2[0] = '\0';

//AplicationExtentionBlock
    head->AEB.extentionName = malloc(sizeof(char)*4);
    head->AEB.extentionName[0] = 0x21;
    head->AEB.extentionName[1] = 0xff;
    head->AEB.extentionName[2] = 0x0b;
    head->AEB.extentionName[3] = '\0';

    head->AEB.applicationName = "NETSCAPE2.0";

    head->AEB.lengthOfDataBlock = 3;
    head->AEB.numberLoop = 0;

//GraphicControlExtension
    head->GCE.extensionHeader = malloc(sizeof(char)*3);
    head->GCE.extensionHeader[0] = 0x21;
    head->GCE.extensionHeader[1] = 0xf9;
    head->GCE.extensionHeader[2] = '\0';

    head->GCE.byteSize = 0x04;
    head->GCE.packedField = 0x00;
    head->GCE.delayTime = 10;
    head->GCE.transparentColorIndex = 0x00;

//ImageDescriptor
    head->ID.imageSeparator = 0x2c;

    head->ID.imageLeft = malloc(sizeof(char)*3);
    head->ID.imageLeft[0] = 0;
    head->ID.imageLeft[1] = 0;
    head->ID.imageLeft[2] = '\0';

    head->ID.imageTop = malloc(sizeof(char)*3);
    head->ID.imageTop[0] = 0;
    head->ID.imageTop[1] = 0;
    head->ID.imageTop[2] = '\0';
    
    head->ID.imageWidth = width;
    head->ID.imageHeight = height;

    head->ID.packedField = 0x00; //local color table, sort flag, and more (we are not using it)
}

void writeGIFHeader(FILE * file)
{
    int i;

    for(i = 0; i < 6; i++)
    {
        fputc(head->header[i],file);
    }
    
    //width
    char * hex = malloc(sizeof(char)*5);
    decimalToHex(head->LSD.width, hex, 4);
    char * hexByte = malloc(sizeof(char)*3);
    hexToByte(hex, hexByte, 2);
    for(i = 0; i < 2; i++)
        fputc(hexByte[i], file);

    //height
    decimalToHex(head->LSD.height, hex, 4);
    hexToByte(hex, hexByte, 2);
    for(i = 0; i < 2; i++)
        fputc(hexByte[i], file);

    free(hex);
    free(hexByte);

    //Packed field
    int decimal = binToDecimal(head->LSD.packedField,8);
    hex = malloc(sizeof(char)*3);
    decimalToHex(decimal, hex, 2);
    hexByte = malloc(sizeof(char)*2);
    hexToByte(hex, hexByte, 1);
    fputc(hexByte[0], file);

    free(hex);
    free(hexByte);

    //background color index
    hex = malloc(sizeof(char)*3);
    decimalToHex(head->LSD.backgroundColorIndex, hex, 2);
    hexByte = malloc(sizeof(char)*2);
    hexToByte(hex, hexByte, 1);
    fputc(hexByte[0], file);

    free(hex);
    free(hexByte);

    //PixelAspectRatio
    hex = malloc(sizeof(char)*3);
    decimalToHex(head->LSD.pxAscpectRatio, hex, 2);
    hexByte = malloc(sizeof(char)*2);
    hexToByte(hex, hexByte, 1);
    fputc(hexByte[0], file);

    free(hex);
    free(hexByte);

    //GlobalColorTable
    //color 1
    for(i = 0; i < 3; i++)
        fputc(head->GCT.color1[i], file);

    //color 2
    for(i = 0; i < 3; i++)
        fputc(head->GCT.color2[i], file);

//AplicationBlock
    //extensionName
    for(i = 0; i < 3; i++)
        fputc(head->AEB.extentionName[i], file);

    //ApplicationName
    for(i = 0; i < 11; i++)
        fputc(head->AEB.applicationName[i], file);

    //Length of Data Sub-block
    hex = malloc(sizeof(char)*3);
    decimalToHex(head->AEB.lengthOfDataBlock, hex, 2);
    hexByte = malloc(sizeof(char)*2);
    hexToByte(hex, hexByte, 1);

    fputc(hexByte[0], file);

    free(hex);
    free(hexByte);

    //Always 1
    fputc(0x00, file);

    //Number of loops (0 means infinite)
    hex = malloc(sizeof(char)*5);
    decimalToHex(head->AEB.numberLoop, hex, 4);
    hexByte = malloc(sizeof(char)*3);
    hexToByte(hex, hexByte, 2);

    for(i = 0; i < 2; i++)
        fputc(hexByte[i], file);

    free(hex);
    free(hexByte);

    //Terminator of data sub-block
    fputc(0x00, file);
}

void writeImageDescriptor(FILE * file)
{
    //image separator
    fputc(head->ID.imageSeparator, file);

    //position of image to left
    int i;
    for(i = 0; i < 2; i++)
        fputc(head->ID.imageLeft[i], file);

    //position of image to top
    for(i = 0; i < 2; i++)
        fputc(head->ID.imageTop[i], file);

    //width of image
    char * hex = malloc(sizeof(char)*5);
    decimalToHex(head->ID.imageWidth, hex, 4);
    char * hexByte = malloc(sizeof(char)*3);
    hexToByte(hex, hexByte, 2);

    for(i = 0; i < 2; i++)
        fputc(hexByte[i], file);

    //height of image
    decimalToHex(head->ID.imageHeight, hex, 4);
    hexToByte(hex, hexByte, 2);

    for(i = 0; i < 2; i++)
        fputc(hexByte[i], file);
    
    free(hex);
    free(hexByte);

    //packed field
    fputc(head->ID.packedField, file);
}

void writeGraphicControlExtension(FILE * file)
{
    int i;
    
    //Header of GCE
    for(i =0; i < 2; i++)
        fputc(head->GCE.extensionHeader[i], file);

    //byteSize
    fputc(head->GCE.byteSize, file);

    //packedField
    fputc(head->GCE.packedField, file);

    //Delay Time
    char * hex = malloc(sizeof(char)*5);
    decimalToHex(head->GCE.delayTime, hex, 4);
    char * hexByte = malloc(sizeof(char)*3);
    hexToByte(hex, hexByte, 2);

    for(i = 0; i < 2; i++)
        fputc(hexByte[i], file);

    free(hex);
    free(hexByte);

    //transpartent color index
    fputc(head->GCE.transparentColorIndex, file);
    
    //Terminator
    fputc(0x00, file);
}

void writeEndOfFIle(FILE * file)
{
    //trailer (ending file)
    fputc(0x3b, file);
    fclose(file);

    cleanHead();
}

void decimalToBin(int number, int digits, char * output)
{
    int workingNumber = number;
    int i;
    for(i = digits-1; i >=0; i--)
    {
        output[i] = workingNumber % 2;
    }

    output[digits] = '\0';
}

void cleanHead()
{
    free(head->GCT.color1);
    free(head->GCT.color2);
    free(head->AEB.extentionName);
    free(head->GCE.extensionHeader);
    free(head->ID.imageLeft);
    free(head->ID.imageTop);
    free(head);
}

void hexToByte(char * hex, char * hexByte, int number)
{
    int i;
    int j = number-1;
    for(i = 0; i < number; i++)
    {
        hexByte[i] = 16*hex[j] + hex[j+1];
        j--;
    }

    hexByte[number-1] = '\0';
}

int binToDecimal(char * bin, int digits)
{
    int i = 0;
    int sum = 0;
    int multi = 1;
    for(i = digits-1; i >=0; i--)
    {
        sum += bin[i] * multi;
        multi*=2;
    }

    return sum;
}

