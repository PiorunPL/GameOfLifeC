/**
 *  This function counts and returns cell's (row: posR, column: posC) alive neighbours,
 *  using rules of Von Neumann neighborhood.
 *  If the cell is on the border of the map, function is teating cells outside map 
 *  as they were alive.
 */
int countNeighbours(int **generation, int rows, int cols, int posR, int posC) {
    int aliveNeighbours = 0;
    
    if (posR != 0) 
        if (generation[posR - 1][posC] == 1
         || generation[posR - 1][posC] == 3)
            aliveNeighbours++;
    if (posC != 0)
        if (generation[posR][posC - 1] == 1
         || generation[posR][posC - 1] == 3)
            aliveNeighbours++;

    if (posR != rows - 1)
        if (generation[posR][posC - 1] == 1
         || generation[posR][posC - 1] == 2)
            aliveNeighbours++;
    
    if (posC != cols - 1)
        if (generation[posR][posC - 1] == 1
         || generation[posR][posC - 1] == 2)
            aliveNeighbours++;

    return aliveNeighbours;
}
