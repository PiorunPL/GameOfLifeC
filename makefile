#
#   VARIABLES
#

OBJ=bin/obj/
BIN=bin/
SRC=src/
CC=cc
OBJOPTS= -I $(SRC) -c -o $@ $<
BINOPTS=$^ -o $@ -L src

vpath $(SRC)

#
#   BIN FILES
#

$(BIN)moore: $(OBJ)main.o $(OBJ)FilesOperations.o $(OBJ)game.o $(OBJ)moore.o
	$(CC) $(BINOPTS) 

$(BIN)neumann: $(OBJ)main.o $(OBJ)FilesOperations.o $(OBJ)game.o $(OBJ)neumann.o
	$(CC) $(BINOPTS)

#
#   OBJECT FILES
#

$(OBJ)main.o: $(SRC)main.c $(SRC)game.h
	$(CC) $(OBJOPTS) 

$(OBJ)FilesOperations.o: $(SRC)FilesOperations.c
	$(CC) $(OBJOPTS)

$(OBJ)game.o: $(SRC)game.c $(SRC)nbrhood.h
	$(CC) $(OBJOPTS)

$(OBJ)moore.o: $(SRC)moore.c
	$(CC) $(OBJOPTS)

$(OBJ)neumann.o: $(SRC)neumann.c
	$(CC) $(OBJOPTS)

#
#   CLEAR
#

clearobj:
	rm *.o

clear:
	rm *o life
