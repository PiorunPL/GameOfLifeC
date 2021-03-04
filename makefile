#
#   VARIABLES
#

OBJ = bin/obj/
BIN = bin/
SRC = src/
CC = cc
OBJOPTS = -I $(SRC) -c -o $@ $<
BINOPTS = $^ -o $@ -L src
DEBUGOPTS = -ggdb -DDEBUG

vpath $(SRC)

#
#   BIN FILES
#

$(BIN)moore: $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)moore.o $(OBJ)fileOut.o 
	$(CC) $(BINOPTS) -lm

$(BIN)neumann: $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)neumann.o $(OBJ)fileOut.o
	$(CC) $(BINOPTS) -lm

$(BIN)tormoore: $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)tormoore.o $(OBJ)fileOut.o 
	$(CC) $(BINOPTS) -lm

$(BIN)torneumann: $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)torneumann.o $(OBJ)fileOut.o
	$(CC) $(BINOPTS) -lm


#
#   OBJECT FILES
#

$(OBJ)main.o: $(SRC)main.c $(SRC)game.h $(SRC)fileOut.h
	$(CC) $(OBJOPTS) 

$(OBJ)filesops.o: $(SRC)filesops.c
	$(CC) $(OBJOPTS)

$(OBJ)game.o: $(SRC)game.c $(SRC)nbrhood.h
	$(CC) $(OBJOPTS)

$(OBJ)moore.o: $(SRC)moore.c
	$(CC) $(OBJOPTS)

$(OBJ)neumann.o: $(SRC)neumann.c
	$(CC) $(OBJOPTS)

$(OBJ)fileOut.o: $(SRC)fileOut.c
	$(CC) $(OBJOPTS) -lm

$(OBJ)tormoore.o: $(SRC)/torus/moore.c
	$(CC) $(OBJOPTS)

$(OBJ)torneumann.o: $(SRC)/torus/neumann.c
	$(CC) $(OBJOPTS)

#
#   DEBUG
#

$(BIN)dmoore: $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dmoore.o $(OBJ)dfileOut.o
	$(CC) $(BINOPTS) $(DEBUGOPTS) -lm

$(BIN)dneumann: $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dneumann.o $(OBJ)dfileOut.o
	$(CC) $(BINOPTS) $(DEBUGOPTS)

$(BIN)dtormoore: $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dtormoore.o $(OBJ)dfileOut.o 
	$(CC) $(BINOPTS) $(DEBUGOPTS) -lm

$(BIN)dtorneumann: $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dtorneumann.o $(OBJ)dfileOut.o
	$(CC) $(BINOPTS) $(DEBUGOPTS) -lm

$(OBJ)dmain.o: $(SRC)main.c $(SRC)game.h $(SRC)fileOut.h
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dfilesops.o: $(SRC)filesops.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dgame.o: $(SRC)game.c $(SRC)nbrhood.h
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dmoore.o: $(SRC)moore.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dneumann.o: $(SRC)neumann.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dfileOut.o: $(SRC)fileOut.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS) -lm

$(OBJ)dtormoore.o: $(SRC)/torus/moore.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dtorneumann.o: $(SRC)/torus/neumann.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

#
#   CLEAN
#

.PHONY: clean

clean:
	rm -f $(BIN){*,.*} $(OBJ)*.o
