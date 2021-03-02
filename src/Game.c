/**
 *  This function counts and return cell's (row: posR, column: posC) alive neighbours.
 *  If the cell is on the border of the map, function is teating cells outside map 
 *  as they were alive.
 */
int aliveNeighbours(int **generation, int rows, int cols, int posR, int posC) {
    int r, c;
    int startR = -1, startC = -1;
    int finR = 1, finC = 1;
    int aliveNeighbours = 0;
    
    if (posR == 0) startR = 0;
    if (posC == 0) startC = 0;
    if (posR == rows - 1) finR = rows - 1;
    if (posC == cols - 1) finC = cols - 1;

    for (r = startR; r <= finR; r++)
        for (c = startC; c <= finC; c++)
            if (generation[posR + r][posC + c] == 1 || generation[posR + r][posC + c] == 3)
                aliveNeighbours++;

    return aliveNeighbours;
}

/**
 *  This function simulates and returns one generation.
 *  States of cell:
 *      0 - dead
 *      1 - alive
 *      2 - born
 *      3 - died
 */
int **play(int **generation, int rows, int cols) {
    int c, r;
    int neighbours;

    for (r = 0; r < rows; r++)
        for (c = 0; c < cols; c++) {
            if ((neighbours = aliveNeighbours(generation, rows, cols, r, c)) == 2) {
                if (generation[r][c] == 2) generation[r][c] = 1;
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

    return generation;
}
