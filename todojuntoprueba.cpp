#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include "sim.h"
#include "grid.h"
#include <vector>

using namespace std;
using std::vector;

#define MAX_NEIGH 12

#define N 100
#define DIE 0
#define QUARANTINE 1
#define RECOVER 2
#define HINFECTED 3
#define NO_INFECTIOUS 4
#define NO_CHANGE 5

int neighType = MOORE;

int days = 100;

int nStrain = 1;

double probability = 0.6;
int daystoinfect = 4;
int incubation = 3;
int duration = 10;
double deadliness = 0.2;
double inmunity = 0.5;
int quaratineinit = 100;
int quaratinedays = 7;

class Cell
{
public:
	int state;
	bool cquaratinedays;
	bool quarantined;
	bool medication;
	bool cinmunity;
	bool cduration;
	bool cincubation;
	bool infected;
	bool alive;
	Cell();
	void infect();
};
Cell::Cell()
{

	state = 0;
	cquaratinedays = 1;
	quarantined = false;
	medication = false;
	cinmunity = 1;
	cduration = 1;
	cincubation = 1;
	infected = false;
	alive = true;
}

void Cell::infect()
{
	infected = true;
	state = 1;
	cincubation = incubation;
	cduration = duration;
}
bool search(int **neighbours, int state, vector<vector<Cell>> &cells)
{
	int i = 0;
	int x = neighbours[i][0];
	int y = neighbours[i][1];
	bool found = false;
	while (found == false && i < MAX_NEIGH)
	{
		if (x != -1)
		{
			if (cells[x][y].state == state)
			{
				found = true;
			}
		}
		x = neighbours[i][0];
		y = neighbours[i][1];
		i++;
	}
	return found;
}

int sum_quarantined(int **neighbours, vector<vector<Cell>> &cells)
{
	int i = 0;
	int x = neighbours[i][0];
	int y = neighbours[i][1];
	int sum = 0;
	while (i < MAX_NEIGH)
	{
		if (x != -1 && cells[x][y].quarantined)
		{
			sum++;
		}

		x = neighbours[i][0];
		y = neighbours[i][1];
		i++;
	}
	return sum;
}

void evaluation(vector<vector<Cell>> &cells, int currentTick)
{

	if (currentTick >= 0)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{

				int **c_neighbours;
				c_neighbours = (int **)malloc(MAX_NEIGH * sizeof(int *));
				for (int i = 0; i < MAX_NEIGH; i++)
				{
					c_neighbours[i] = (int *)malloc(2 * sizeof(int));
				}
				for (int i = 0; i < MAX_NEIGH; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						c_neighbours[i][j] = -1;
					}
				}
				searchNeighbours(c_neighbours, N, i, j, neighType);

				if (cells[i][j].state == NO_INFECTIOUS)
				{
					cells[i][j].state = HINFECTED;
					cells[i][j].infected = true;
					cells[i][j].cincubation = incubation;
					cells[i][j].cduration = duration;
				}
			}
		}
	}
	if (currentTick >= 50)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{

				int **c_neighbours;
				c_neighbours = (int **)malloc(MAX_NEIGH * sizeof(int *));
				for (int i = 0; i < MAX_NEIGH; i++)
				{
					c_neighbours[i] = (int *)malloc(2 * sizeof(int));
				}
				for (int i = 0; i < MAX_NEIGH; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						c_neighbours[i][j] = -1;
					}
				}
				searchNeighbours(c_neighbours, N, i, j, neighType);

				if (cells[i][j].state == HINFECTED)
				{
					cells[i][j].state = RECOVER;
					cells[i][j].infected = true;
					cells[i][j].cincubation = incubation;
					cells[i][j].cduration = duration;
				}
			}
		}
	}
}
void drawCell(vector<vector<Cell>> &cells)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			switch (cells[i][j].state)
			{
			case NO_CHANGE:
				glColor3f(1.000000, 1.000000, 1.000000);
				break;
			case NO_INFECTIOUS:
				glColor3f(0.980400, 0.776500, 0.000000);
				break;
			case HINFECTED:
				glColor3f(0.843100, 0.353000, 0.114900);
				break;
			case RECOVER:
				glColor3f(0.941000, 0.552900, 0.251000);
				break;
			case QUARANTINE:
				glColor3f(0.203900, 0.733300, 0.854000);
				break;
			case DIE:
				glColor3f(0.000000, 0.000000, 0.000000);
				break;
			}
			glRectd(i, j, i + 1, j + 1);
		}
	}
}
