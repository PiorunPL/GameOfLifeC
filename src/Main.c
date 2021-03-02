#include<stdio.h>
#include<unistd.h> //do funkcji access

int **getPrimaryGen(int rows, int cols, FILE *in);
int getRows(FILE *in);
int getCols(FILE *in);

int main( int argc, char** argv ){
	if( argc<2 ){
		fprintf(stderr, "Nie podano pliku wejsciowego\n");
		return 1;
	}

	FILE *in;
	if( access(argv[1], F_OK ) == 0 ){
		in = fopen(argv[1], "r");
	} else{
		fprintf(stderr, "Plik %s nie istnieje!\n", argv[1]);
		return 2;
	}

	//rows i cols są usatwione na -1, aby w razie błędu został wyłapany
	int rows = -1;
	int cols = -1;
	if( fscanf(in, "%d %d", &rows, &cols) != 2 ){
		fprintf(stderr, "Cos poszlo nie tak, pewnie przez niepoprawny format pliku\n");
		fclose(in);
		return 3;
	}	
	
	if( rows == -1 || cols == -1 ){
		fclose(in);
		fprintf(stderr, "Niepoprawny format pliku %s, zajrzyj do instrukcji\n", argv[1]);
		return 3;
	}
	//printf("%d %d\n", rows, cols);
	int **primaryGen = getPrimaryGen(rows, cols, in);
	fclose(in);

	//Od tego miejsca możecie dodawać dalsze funkcje, ale jeszcze nie skończyłem wczytywania tablicy

	return 0;
}
