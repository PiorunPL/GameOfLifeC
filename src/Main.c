#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h> //do funkcji access

int **getPrimaryGen(int rows, int cols, FILE *in);
int getRows(FILE *in);
int getCols(FILE *in);

char *help = 
"NAME\n"
"   %s - simulation of Conway's Game of Life\n\n"
"SYNOPSIS\n"
"   %s -m map-file [options]\n\n"
"OPTIONS\n"
"   -i number-of-generations,   by default it is 100\n"
"   -d name-of-directory,       directory, where BMP files are stored,\n"
"                               by default it is 'life'\n\n"
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
    int i;

    while ((opt = getopt(argc, argv, "m:i:d:")) != -1) {
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
	if(access(map, F_OK) == 0){
		in = fopen(map, "r");
	} else{
		fprintf(stderr, "File %s doesn`t exist!\n", map);
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
	//int **generation = getPrimaryGen(rows, cols, in);
	fclose(in);

    for (i = 0; i < iterations; i++)
        //play(generation, rows, cols);

    return EXIT_SUCCESS;
}
