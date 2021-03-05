#
#   VARIABLES
#

OBJ = obj/
BIN = bin/
SRC = src/
CC = cc
OBJOPTS = -I $(SRC) -c -o $@ $<
BINOPTS = $^ -o $@
DEBUGOPTS = -ggdb

vpath $(SRC)

#
#   BFORE COMPILATION
#

dirs:
	mkdir $(BIN) $(OBJ)

#
#   BIN FILES
#

$(BIN)moore: dirs $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)moore.o $(OBJ)fileOut.o
	-$(CC) $(BINOPTS) -lm

$(BIN)neumann: dirs $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)neumann.o $(OBJ)fileOut.o
	-$(CC) $(BINOPTS) -lm

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

#
#   DEBUG
#

$(BIN)dmoore: dirs $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dmoore.o $(OBJ)dfileOut.o
	-$(CC) $(BINOPTS) $(DEBUGOPTS) -lm

$(BIN)dneumann: dirs $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dneumann.o $(OBJ)dfileOut.o
	-$(CC) $(BINOPTS) $(DEBUGOPTS)

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

#
#   CLEAN
#

.PHONY: clean

clean:
	rm -rd $(BIN) $(OBJ)
