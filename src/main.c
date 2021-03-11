#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "game.h"
#include "fileOut.h"

int **getPrimaryGen(int rows, int cols, FILE *in);
void saveGen(int **gen, int rows, int cols, char *filename);
void cleanTab(int **tab, int rows);

char *help = 
"NAME\n"
"   %s - simulation of Conway's Game of Life\n\n"
"SYNOPSIS\n"
"   %s -m map-file [options]\n\n"
"OPTIONS\n"
"   -i number-of-generations,   by default it is 100\n"
"   -d name-of-directory,       directory, where BMP files are stored,\n"
"                               by default it is 'life'\n"
"   -o name-of-output-file      file, where the last generation is saved\n"
"                               in the map-file format,\n"
"                               by default it is 'data/lastgens/map'\n\n"
"AUTHORS\n"
"   Jakub Maciejewski, Michal Ziober, Sebastian Gorka, students of\n"
"   Warsaw University of Technology.\n"
"   This program is JIMP2 coursework.\n";

int main(int argc, char **argv) {
    char *progname = argv[0];
    int opt;
    int iterations = 100;
    char *dirname = "life";
    char *map = "noname";
    char *output = "data/lastgens/map";
    int i;

    while ((opt = getopt(argc, argv, "m:i:d:o:")) != -1) {
        switch (opt) {
        case 'm':
            map = optarg;
            break;
        case 'i':
           iterations = atoi(optarg); 
            break;
        case 'd':
            dirname = optarg;
            break;
        case 'o':
            output = optarg;
            break;
        default:
            printf(help, progname, progname);
            return EXIT_FAILURE;
            break;
        }
    }
    
    if (strcmp(map, "noname") == 0) {
        fprintf(stderr, "Wrong syntax, name of map-file is required.\n");
        fprintf(stderr, help, progname, progname);
        return EXIT_FAILURE;
    }
	


	FILE *in;
	//Sprawdzanie czy plik istnieje
	if( (in = fopen(map, "r")) != NULL){
		//File exists
	}else{
		fprintf(stderr, "Input file %s doesn`t exist!\n", map);
		return EXIT_FAILURE;
	}


	//rows i cols są usatwione na -1, aby w razie błędu został wyłapany
	int rows = -1;
	int cols = -1;
	if( fscanf(in, "%d %d", &rows, &cols) != 2 ){
		fprintf(stderr, "Invalid format of file (in the first line)\n");
		fclose(in);
		return EXIT_FAILURE;
	}	
	
	if( rows == -1 || cols == -1 ){
		fclose(in);
		fprintf(stderr, "Invalid format of file %s\n", map);
		return EXIT_FAILURE;
	}

	int **generation = getPrimaryGen(rows, cols, in);
	fclose(in);
    creatingBMP(generation, rows, cols, 0, iterations, dirname);

    for (i = 0; i < iterations; i++)
    {
        play(generation, rows, cols);
        creatingBMP(generation, rows, cols, i + 1, iterations, dirname);
    }
	saveGen(generation, rows, cols, output);


	cleanTab(generation, rows);

    return EXIT_SUCCESS;
}

