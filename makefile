#
#   VARIABLES
#

OBJ = obj/
BIN = bin/
SRC = src/
CC = cc
OBJOPTS = -I $(SRC) -c -o $@ $<
BINOPTS = -o $@ -L src
DEBUGOPTS = -ggdb -DDEBUG

vpath $(SRC)

all: $(BIN)moore $(BIN)tormoore

#
#   BEFORE COMPILATION
#

dirs:
ifeq (,$(wildcard ./bin))
	mkdir ./bin
endif
ifeq (,$(wildcard ./obj))
	mkdir ./obj
endif

#
#   BIN FILES
#

$(BIN)moore: dirs $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)moore.o $(OBJ)fileOut.o $(OBJ)randmap.o $(OBJ)readbmp.o $(OBJ)fileGIF.o
	$(CC) $(BINOPTS) $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)moore.o $(OBJ)fileOut.o -lm $(OBJ)randmap.o $(OBJ)readbmp.o $(OBJ)fileGIF.o

$(BIN)tormoore: dirs $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)tormoore.o $(OBJ)fileOut.o $(OBJ)randmap.o $(OBJ)readbmp.o $(OBJ)fileGIF.o
	$(CC) $(BINOPTS) $(OBJ)main.o $(OBJ)filesops.o $(OBJ)game.o $(OBJ)tormoore.o $(OBJ)fileOut.o -lm $(OBJ)randmap.o $(OBJ)readbmp.o $(OBJ)fileGIF.o

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

$(OBJ)fileOut.o: $(SRC)fileOut.c
	$(CC) $(OBJOPTS) -lm

$(OBJ)tormoore.o: $(SRC)tormoore.c
	$(CC) $(OBJOPTS)

$(OBJ)randmap.o: $(SRC)randmap.c
	$(CC) $(OBJOPTS)
	
$(OBJ)fileGIF.o: $(SRC)fileGIF.c
	$(CC) $(OBJOPTS) -lm

$(OBJ)readbmp.o: $(SRC)readbmp.c $(SRC)readbmp.h 
	$(CC) $(OBJOPTS) -lm

#
#   DEBUG
#

debug: $(BIN)dmoore $(BIN)dtormoore

$(BIN)dmoore: dirs $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dmoore.o $(OBJ)dfileOut.o $(OBJ)drandmap.o $(OBJ)dreadbmp.o $(OBJ)dfileGIF.o
	$(CC) $(BINOPTS) $(DEBUGOPTS) $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dmoore.o $(OBJ)dfileOut.o -lm $(OBJ)drandmap.o $(OBJ)dreadbmp.o $(OBJ)dfileGIF.o

$(BIN)dtormoore: dirs $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dtormoore.o $(OBJ)dfileOut.o $(OBJ)drandmap.o $(OBJ)dreadbmp.o $(OBJ)dfileGIF.o
	$(CC) $(BINOPTS) $(DEBUGOPTS) $(OBJ)dmain.o $(OBJ)dfilesops.o $(OBJ)dgame.o $(OBJ)dtormoore.o $(OBJ)dfileOut.o -lm $(OBJ)drandmap.o $(OBJ)dreadbmp.o $(OBJ)dfileGIF.o

$(OBJ)dmain.o: $(SRC)main.c $(SRC)game.h $(SRC)fileOut.h
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dfilesops.o: $(SRC)filesops.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dgame.o: $(SRC)game.c $(SRC)nbrhood.h
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dmoore.o: $(SRC)moore.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dfileOut.o: $(SRC)fileOut.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS) -lm

$(OBJ)dtormoore.o: $(SRC)tormoore.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)drandmap.o: $(SRC)randmap.c
	$(CC) $(OBJOPTS) $(DEBUGOPTS)

$(OBJ)dfileGIF.o: $(SRC)fileGIF.c $(SRC)fileGIF.h
	$(CC) $(OBJOPTS) $(DEBUGOPTS) -lm

$(OBJ)dreadbmp.o: $(SRC)readbmp.c $(SRC)readbmp.c 
	$(CC) $(OBJOPTS) $(DEBUGOPTS) -lm

#
#   CLEAN
#

.PHONY: clean

clean:
ifneq (,$(wildcard ./bin))
	rm -rd ./bin
endif
ifneq (,$(wildcard ./obj))
	rm -rd ./obj
endif
