#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
 *  This function creates random map. 
 *  It returns pointer to the array with the map if succed and
 *  NULL if failed.
 */
int **randmap(int rows, int cols) {
    int r, c;
    int **map;

    if ((map = malloc(rows * sizeof(int *))) == NULL) return NULL;

    for (r = 0; r < rows; r++)
        if ((map[r] = malloc(cols * sizeof(int))) == NULL) return NULL;

    srand(time(NULL));

    for (r = 0; r < rows; r++)
        for (c = 0; c < cols; c++)
            map[r][c] = rand() % 2;

    return map;
}
