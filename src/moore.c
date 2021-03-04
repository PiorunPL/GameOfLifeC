/** FLAT - game field is flat surface
 *  This function counts and returns cell's (row: posR, column: posC) alive neighbours,
 *  using rules od Moore neighourhood.
 *  If the cell is on the border of the map, function is teating cells outside map 
 *  as they were alive.
 */
int countNeighbours(int **generation, int rows, int cols, int posR, int posC) {
    int r, c;
    int startR = -1, startC = -1;
    int finR = 1, finC = 1;
    int aliveNeighbours = 0;
    
    if (posR == 0) startR = 0;
    if (posC == 0) startC = 0;
    if (posR == rows - 1) finR = 0;
    if (posC == cols - 1) finC = 0;

    for (r = startR; r <= finR; r++) {
        for (c = startC; c <= finC; c++) {
            if (r == 0 && c == 0)
                continue;
            else if(generation[posR + r][posC + c] == 1)
                aliveNeighbours++;
            else if (((r >= 0 && c >= 0) || r > 0) && (generation[posR + r][posC + c] == 2))
                aliveNeighbours++;
            else if (((r <= 0 && c <= 0) || r < 0) && (generation[posR + r][posC + c] == 3))
                aliveNeighbours++;
        }
    }

    return aliveNeighbours;
}
