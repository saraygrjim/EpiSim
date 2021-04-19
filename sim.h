#ifndef SIM_H_INCLUDED
#define SIM_H_INCLUDED

#define N     50

// Types of cell states
#define NO_CHANGE     0
#define NO_INFECTIOUS 1
#define INFECTED      2
#define RECOVER       3
#define QUARANTINE    4
#define DIE           5

// Types of neighborhood
#define MOORE         0
#define NEUMANN       1
#define EXTENDED      2

void initGrid(int, int);
void drawGrid();
// void drawCell(Cell **cells);

#endif