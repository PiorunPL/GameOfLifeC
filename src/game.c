#include "nbrhood.h"
/**
 *  This function simulates and returns one generation.
 *  States of cell:
 *      0 - dead
 *      1 - alive
 *      2 - born
 *      3 - died
 */
int **play(int **generation, int rows, int cols) {
    int r, c;
    int neighbours;

    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            if ((neighbours = countNeighbours(generation, rows, cols, r, c)) == 2) {
                if (generation[r][c] == 2) generation[r][c] = 1;
                else if (generation[r][c] == 3) generation[r][c] = 0;
            }
            else if (neighbours == 3) {
                if (generation[r][c] == 0) generation[r][c] = 2;
                else if (generation[r][c] == 2) generation[r][c] = 1;
                else if (generation[r][c] == 3) generation[r][c] = 2;
            }
            else {
                if (generation[r][c] == 1) generation[r][c] = 3;
                else if (generation[r][c] == 2) generation[r][c] = 3;
                else if (generation[r][c] == 3) generation[r][c] = 0;
            }
        }
    }

    return generation;
}

int **genoutformat(int **generation, int rows, int cols) {
    int r, c;

    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            if (generation[r][c] == 2) generation[r][c] = 1;
            else if (generation[r][c] == 3) generation[r][c] = 0;
        }
    }

    return generation;
}
