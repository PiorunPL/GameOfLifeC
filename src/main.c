#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "readbmp.h"
#include "game.h"
#include "randmap.h"
#include "fileIn.h"
#include "fileOut.h"
#include "fileGIF.h"

char *help = 
"----------------------------------------------------------------\n"
"NAME\n"
"   %s - simulation of Conway's Game of Life\n\n"
"SYNOPSIS\n"
"   %s [ -m map-file | -r [rows]x[columns] ] [options]\n\n"
"DESCRIPTION\n"
"   %s plays Conway's Game of Life. There are ways of playing the game:\n"
"       1. Insert properly formated text file (after '-m' option).\n"
"          File should have two integer values seperated by space\n"
"          in the first row: number of rows and numer of columns.\n"
"          Directly underneath should be table with values {0, 1}.\n"
"          Table should have number of rows equal to that in the first\n"
"          line. Each line should consist of number of values equal to\n"
"          the one at the top of the file.\n"
"       2. Insert bmp file (after '-m' option).\n"
"          Currently only 1 bit per pixel (bpp) files are accepted.\n"
"       3. Insert number of rows and columns separated by 'x'.\n"
"          When that kind of string appears after '-r' option, program\n"
"          generates random map of given dimensions and plays on that map.\n\n"
"   There are availible two versions of program:\n"
"       1. moore - bahaves as if outside map borders all cells were dead\n"
"       2. tormoore - behaves as if map was surface of torus\n\n"
"OPTIONS\n"
"   -i number-of-generations,   by default it is 100\n"
"   -d name-of-directory,       directory, where BMP files are stored,\n"
"                               by default it is 'life'\n"
"   -o name-of-output-file      file, where the last generation is saved\n"
"                               in the map-file format,\n"
"                               by default it is 'data/lastgens/map'\n"
"   --bmp                       with this non-argument option passed,\n"
"                               program creates bmp file\n"
"   --gif                       with this non-argument option passed,\n"
"                               program creates gif file\n\n"
"AUTHORS\n"
"   Jakub Maciejewski, Michal Ziober, Sebastian Gorka,\n"
"   students of Warsaw University of Technology.\n"
"   This program is JIMP2 coursework.\n"
"----------------------------------------------------------------\n";

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
    int dobmp = 0, dogif = 0;

    struct option long_options[] = {
        {"bmp", no_argument,  NULL,   'b'},
        {"gif", no_argument,  NULL,   'f'}
    };

    int long_index = 0;

//  collects command line options and arguments
    while ((opt = getopt_long(argc, argv, "m:i:d:o:r:b:f", long_options, NULL)) != -1) {
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
        case 'b':
            dobmp = 1;
            break;
        case 'f':
            dogif = 1;
            break;
        default:
            fprintf(stderr, help, progname, progname, progname);
            return EXIT_FAILURE;
            break;
        }
    }

    FILE *in;
    int **generation;

//  no arguments were passed to the program -> print usage and finish
    if (optind == 1) {
            fprintf(stderr, help, progname, progname, progname);
            return EXIT_SUCCESS;
    }

//  checks if dimensions for randomly generated map are
//  provided and if yes, checks if they are correct
    if (randdimensions != NULL) {
        if (sscanf(randdimensions, "%dx%d", &rows, &cols) != 2) {
            fprintf(stderr, "Wrong syntax, after '-r' parameter should be\n"
                            "[number of rows]x[number of columns] instead of '%s'.\n\n", randdimensions);
            fprintf(stderr, help, progname, progname, progname);
            return EXIT_FAILURE;
        }
    }

//  BMP header is correct -> read generation from .bmp file
    if ((in = isbmp(map)) != NULL) {
        if ((generation = readbmp(in, &rows, &cols)) == NULL) {
            fclose(in);
            fprintf(stderr, "File %s cannot be read correctly.\n\n", map);
            fprintf(stderr, help, progname, progname, progname);
            return EXIT_FAILURE;
        }
        fclose(in);
    }
 
//  dimensions are correct (greater than 0) and
//  map-file name was not inserted -> generate random map
    else if ((rows > 0 && cols > 0) && strcmp(map, "noname") == 0) {
        if ((generation = randmap(rows, cols)) == NULL) {
            fprintf(stderr, "Random map cannot be created.\n\n");
            fprintf(stderr, help, progname, progname, progname);
            return EXIT_FAILURE;
        }
    }

//  neither dimensions nor name of map-file were inserted -> print
//  manual on the screen and exit
    else if ((rows == -1 && cols == -1) && strcmp(map, "noname") == 0) {
        fprintf(stderr, "Wrong syntax: map-file or random map dimensions are required.\n\n");
        fprintf(stderr, help, progname, progname, progname);
        return EXIT_FAILURE;
    }

//  map-file name was not inserted and dimensions are not correct -> print
//  manual on the screen and exit
    else if ((rows <= 0 || cols <= 0) && strcmp(map, "noname") == 0) {
        fprintf(stderr, "Wrong dimensions: %dx%d\n\n", rows, cols);
        fprintf(stderr, help, progname, progname, progname);
        return EXIT_FAILURE;
    }

//  dimensions were not inserted, but map-file name was -> open
//  this file and check if it is formated correctly, if it is
//  read map from this file
    else if ((rows == -1 && cols == -1) && strcmp(map, "noname") != 0) {
        if ((in = fopen(map, "r")) == NULL) {
            fprintf(stderr, "Input file '%s' does not exist.\n\n", map);
            fprintf(stderr, help, progname, progname, progname);
            return EXIT_FAILURE;
        }

        if (fscanf(in, "%d %d", &rows, &cols) != 2) {
            fprintf(stderr, "Invalid format of file (in the first line).\n\n");
            fprintf(stderr, help, progname, progname, progname);
            fclose(in);
            return EXIT_FAILURE;
        }	

        generation = getPrimaryGen(rows, cols, in);
        fclose(in);
    }

//  idk, just in case
    else {
        fprintf(stderr, "Wrong syntax: map-file or random map dimensions are required.\n\n");
        fprintf(stderr, help, progname, progname, progname);
        return EXIT_FAILURE;
    }
	
//  no matter how generation was filled, if it is filled correctly, then
//  graphical files are created here
//  if nothing goes wrong inside functions, program finishes with success
    if (generation != NULL) {
        dirname = changeDirName(dirname);
        dirname = checkDIR(dirname);

        if (dogif == 1 || (dobmp == 0 && dogif == 0)) {
            fprintf(stdout, "Creating GIF file.\n");
            GIFInit(dirname, cols, rows);
            writeToGIF(generation);
        }
    
        char * path;
        if (dobmp == 1 || (dobmp == 0 && dogif == 0)) {
            fprintf(stdout, "Creating %d BMP file(s).\n", iterations);
            path = createBMP(0,iterations, dirname);
            editBMP(generation, rows, cols, path);
        }

        for (i = 0; i < iterations; i++) {
            play(generation, rows, cols);
            path = createBMP(i+1, iterations, dirname);
            if (dobmp == 1 || (dobmp == 0 && dogif == 0)) editBMP(generation, rows, cols, path);
            if (dogif == 1 || (dobmp == 0 && dogif == 0)) writeToGIF(generation);
	    free(path);
        }
	    
	if (dobmp == 0 && dogif == 0) fprintf(stdout, "%d graphical output files were placed in %s.\n", i + 1, dirname);
	else fprintf(stdout, "%d graphical output files were placed in %s.\n", i * dobmp + dogif, dirname);

        free(dirname);

        saveGen(generation, rows, cols, output);

        if (dogif == 1 || (dobmp == 0 && dogif == 0)) writeEndOfFile();
	    
        //cleanHead();

        cleanTab(generation, rows);

        return EXIT_SUCCESS;
    }
    else {
        fprintf(stderr, help, progname, progname, progname);
        return EXIT_FAILURE;
    }
}
