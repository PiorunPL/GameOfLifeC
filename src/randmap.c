#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int **randmap(int rows, int cols) {
    int r, c;
    int **map = malloc(rows * sizeof(int *));

    for (r = 0; r < rows; r++)
        map[r] = malloc(cols * sizeof(int));

    srand(time(NULL));

    for (r = 0; r < rows; r++)
        for (c = 0; c < cols; c++)
            map[r][c] = rand() % 2;

    return map;
}
