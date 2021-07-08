#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

// Types of neighborhood
#define MOORE         0
#define NEUMANN       1
#define EXTENDED      2

int** searchNeighbours(int**, int, int, int, int);

#endif