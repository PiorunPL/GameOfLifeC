#include <stdio.h>
#include <ctype.h> //do funkcji isspace
#include <stdlib.h>
#include <unistd.h>

/*
* Funkcja służy do czyszczenia zalokowanego miejsca po tablicy
* int **tab - tablica do wyczyszczenia
* int rows - ilosć wierszy w tej tablicy
*/
void cleanTab(int **tab, int rows){
	int it;
	for( it = rows-1; it>= 0; it--)
		free(tab[it]);
	free(tab);
}

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
		//Sprawdzenie czy faktyczna ilość wierszy nie jest większa niż zadeklarowana
		if(countLines+1 > rows){
			fprintf(stderr, "Declared number of rows are not the same as rows in input file! (Declared < real)\n");
			cleanTab(tabOfInt, rows);
			fclose(in);
			exit(7);
		}

		//Sprawdzenie czym jest wczytany znak, dla nowej linii inkrementuje licznik linii, dla spacji leci dalej, dla 0 lub 1 przypisuje do tablicy 
		if( isspace(c) ){
			if( c == '\n' ){
				if(( c = fgetc(in)) == '\n'){
				//	fclose(in);
					return tabOfInt;
				}
				else{
					ungetc(c, in);
					countLines++;
					if( countColumns != cols ){
						fprintf(stderr, "Declared size and number of elements are not the same\n");
						cleanTab(tabOfInt, rows);
						fclose(in);
						exit(6);
					}
					countColumns = 0;
				}
			}
			else if( c == ' ' )
				;
		}
		else if( c != '0' && c != '1' ){
			fprintf(stderr, "Incorrect value in input file!\n");
			cleanTab(tabOfInt, rows);
			fclose(in);
			exit(4);
		}
		else{
			tabOfInt[countLines][countColumns] = (int)(c - '0');
			countColumns++;
	
		}
	}

	if( countLines != rows ){
		fprintf(stderr, "Declared size and number of elements are not the same\n");
		cleanTab(tabOfInt, rows);
		fclose(in);
		exit(6);
	}

	return tabOfInt;
}
