/** TORUS - game field is surface of a torus
 *  This function counts and returns cell's (row: posR, column: posC) alive neighbours,
 *  using rules od Moore neighourhood.
 *  If the cell is on the border of the map, function is teating cells outside map 
 *  as they were alive.
 */
int countNeighbours(int **generation, int rows, int cols, int posR, int posC) {
    int r, c, ri, ci;
    int aliveNeighbours = 0;

    for (r = ri = -1; ri <= 1; r++, ri++) {
        for (c = ci = -1; ci <= 1; c++, ci++) {
            if (r + posR >= rows) r = r - rows;
            else if (r + posR < 0) r = r + rows;

            if (c + posC >= cols) c = c - cols;
            else if (c + posC < 0) c = c + cols;

            if (ri == 0 && ci == 0)
                continue;

            if(generation[posR + r][posC + c] == 1)
                aliveNeighbours++;
            else if ((((ri >= 0 && ci >= 0) && posR + ri >= 0 && posR + ri < rows && posC + ci >= 0 && posC + ci < cols) ||
                        (ri > 0 && posR + ri >= 0 && posR + ri < rows) ||
                        (posC + ci < 0 && ci < 0 && ri >= 0 && posR + ri < rows) ||
                        (posC + ci >= cols && ci > 0 && ri > 0 && posR + ri < rows) ||
                        (posR + ri < 0 && ri < 0)) &&
                        (generation[posR + r][posC + c] == 2))
                aliveNeighbours++;
            else if ((((ri <= 0 && ci <= 0) && posR + ri >= 0 && posR + ri < rows && posC + ci >= 0 && posC + ci < cols) ||
                       (ri < 0 && posR + ri >= 0 && posR + ri < rows) ||
                       (posC + ci < 0 && ci < 0 && ri < 0) ||
                       (posC + ci >= cols && ci > 0 && ri <= 0) ||
                       (posR + ri >= rows && ri > 0)) &&
                       (generation[posR + r][posC + c] == 3))
                aliveNeighbours++;
        }
    }

    return aliveNeighbours;
}
