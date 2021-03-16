#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "game.h"
#include "fileOut.h"

int **getPrimaryGen(int rows, int cols, FILE *in);
void saveGen(int **gen, int rows, int cols, char *filename);
void cleanTab(int **tab, int rows);
int **randmap(int rows, int cols);   

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
    char *randdimensions = NULL;
    int i;
	int rows = -1, cols = -1;

    while ((opt = getopt(argc, argv, "m:i:d:o:r:")) != -1) {
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
        case 'r':
            randdimensions = optarg;
            break;
        default:
            fprintf(stderr, help, progname, progname);
            return EXIT_FAILURE;
            break;
        }
    }

    if (randdimensions != NULL) {
        if (sscanf(randdimensions, "%dx%d", &rows, &cols) != 2) {
            fprintf(stderr, "Wrong syntax, after '-r' parameter should be\n"
                            "[number of rows]x[number of columns] instead of '%s'.\n\n", randdimensions);
            fprintf(stderr, help, progname, progname);
            return EXIT_FAILURE;
        }
    }

    int **generation;

    if ((rows > 0 && cols > 0) && strcmp(map, "noname") == 0) {
        generation = randmap(rows, cols);
    }
    else if ((rows == -1 && cols == -1) && strcmp(map, "noname") == 0) {
        fprintf(stderr, "Wrong syntax: map-file or random map dimensions are required.\n\n");
        fprintf(stderr, help, progname, progname);
        return EXIT_FAILURE;
    }
    else if ((rows <= 0 && cols <= 0) && strcmp(map, "noname") == 0) {
        fprintf(stderr, "Wrong dimensions: %dx%d\n\n", rows, cols);
        fprintf(stderr, help, progname, progname);
        return EXIT_FAILURE;
    }
    else if ((rows == -1 && cols == -1) && strcmp(map, "noname") != 0) {
        FILE *in;

        if ((in = fopen(map, "r")) == NULL) {
            fprintf(stderr, "Input file %s doesn't exist!\n\n", map);
            fprintf(stderr, help, progname, progname);
            return EXIT_FAILURE;
        }

        if (fscanf(in, "%d %d", &rows, &cols) != 2) {
            fprintf(stderr, "Invalid format of file (in the first line)\n\n");
            fprintf(stderr, help, progname, progname);
            fclose(in);
            return EXIT_FAILURE;
        }	

        generation = getPrimaryGen(rows, cols, in);
        fclose(in);
    }
    else {
        fprintf(stderr, "Wrong syntax: map-file or random map dimensions are required.\n\n");
        fprintf(stderr, help, progname, progname);
        return EXIT_FAILURE;
    }

    checkDIR(dirname);
    char *path = createBMP(0,iterations, dirname);
    editBMP(generation, rows, cols, path);

    for (i = 0; i < iterations; i++) {
        play(generation, rows, cols);
        path = createBMP(i+1, iterations, dirname);
        editBMP(generation, rows, cols, path);
    }

	saveGen(generation, rows, cols, output);

	cleanTab(generation, rows);

    return EXIT_SUCCESS;
}
