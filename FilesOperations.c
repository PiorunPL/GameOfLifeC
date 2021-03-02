#include<stdio.h>
#include<ctype.h> //do funkcji isspace
#include<stdlib.h>
/*
* Fnkcja wczytuje układ punktów żywych i martwych z podanego pliku
*/
//do dokończenia
int **getPrimaryGen(int rows, int cols, FILE *in){
	//inty do sprawdzenia czy w pliku rzeczywiście jest tyle wierszy i kolumn ile zadeklarowaliśmy
	int countLines = 0;
	int countColumns = 0;

	//alokowanie miejsca
	int **tabOfInt = malloc( (sizeof (int) ) * rows );

/*	Tutaj jest jakiś błąd	
	int it;
	for( it = 0; it<cols; it++ ){
		*tabOfInt = malloc( (sizeof (int) ) * cols );
		tabOfInt++;
	}
*/
	
	int c;
	//Zignorowanie pierwszej linijki (z zadeklarowaną ilością wierszy i kolumn)
	while( (c = fgetc(in)) != EOF && c != '\n' )
		;
	
	//Chodzenie po pliku i ewentualne szukanie błędów
	while( (c = fgetc(in)) != EOF ){
		//printf("%d ", (int)(c - '0') );
		if( isspace(c) ){
			if( c == '\n' )
				countLines++;
			else if( c == ' ' )
				;
		}
		else if( c != '0' && c != '1' ){
			fprintf(stderr, "Podano niepoprawna wartosc w pliku z danymi wejściowymi!\n");
			exit(4);
		}
		else{
			//Zapisanie stanu komówki do tablicy
		}
	}
	return tabOfInt;
}

