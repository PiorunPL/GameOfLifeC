#include <stdio.h>
#include <ctype.h> //do funkcji isspace
#include <stdlib.h>
#include <unistd.h>

/*
* Fnkcja wczytuje układ punktów żywych i martwych z podanego pliku
* rows - ilość wierszy
* cols - ilość kolumn
* *in - plik do wczytania
*/
int **getPrimaryGen(int rows, int cols, FILE *in){

	//alokowanie miejsca
	int **tabOfInt = (int **)malloc( (sizeof(int *) ) * rows );
	int i;
	int j;
	for(i = 0; i<rows; i++)
		tabOfInt[i] = (int *)malloc( cols * sizeof(int) );

	//inty do sprawdzenia czy w pliku rzeczywiście jest tyle wierszy i kolumn ile zadeklarowaliśmy
	int countLines = 0;
	int countColumns = 0;

	int c;
	//Zignorowanie pierwszej linijki (z zadeklarowaną ilością wierszy i kolumn)
	while( (c = fgetc(in)) != EOF && c != '\n' )
		;
	
	//Chodzenie po pliku i ewentualne szukanie błędów
	while( (c = fgetc(in)) != EOF ){
		if( isspace(c) ){
			if( c == '\n' ){
				countLines++;
				if( countColumns != cols ){
					fprintf(stderr, "Declared size and number of elements are not the same\n");
					exit(6);
				}
				countColumns = 0;
			}
			else if( c == ' ' )
				;
		}
		else if( c != '0' && c != '1' ){
			fprintf(stderr, "Incorrect value in input file!\n");
			exit(4);
		}
		else{
			tabOfInt[countLines][countColumns] = (int)(c - '0');
			countColumns++;
	
		}
	}

	if( countLines != rows ){
		fprintf(stderr, "Declared size and number of elements are not the same\n");
		exit(6);
	}

	return tabOfInt;
}
/*
* Funkcja zapisuje stan generacji do pliku
* rows - ilość wierszy
* cols - ilość kolumn
* *filename - ścieżka do pliku, do którego zapisać
*/
void saveGen(int **gen, int rows, int cols, char *filename){
	
	FILE *out = fopen(filename, "w");
	char firstline[32];
	sprintf(firstline, "%d %d\n", rows, cols);
	fputs( firstline, out );
	int i, j;
	for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
			char actual[4];
			sprintf( actual, "%d", gen[i][j]);
			fputs( actual, out );
			if( j == (cols-1) )
				fputs( "\n", out );
			else
				fputs( " ", out );
		}
	}
	fclose(out);
}
























