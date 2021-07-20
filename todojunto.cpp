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
	double cquaratinedays;
	bool quarantined;
	bool medication;
	int cinmunity;
	int cduration;
	int cincubation;
	bool infected;
	bool alive;
	int state;
	Cell();
	void infect();
};
Cell::Cell()
{

	cquaratinedays = 1.0;
	quarantined = false;
	medication = false;
	cinmunity = 1;
	cduration = 1;
	cincubation = 1;
	infected = false;
	alive = true;
	state = 0;
}

void Cell::infect()
{
	infected = true;
	state = 1;
	cincubation = incubation;
	cduration = duration;
}
string foundVariable(Cell c, string variable)
{
	char aux[100];
	string ret = "";
	if (variable.compare("cquaratinedays") == 0)
	{
		sprintf(aux, "%f", c.cquaratinedays);
	}
	if (variable.compare("quarantined") == 0)
	{
		sprintf(aux, "%d", c.quarantined);
	}
	if (variable.compare("medication") == 0)
	{
		sprintf(aux, "%d", c.medication);
	}
	if (variable.compare("cinmunity") == 0)
	{
		sprintf(aux, "%d", c.cinmunity);
	}
	if (variable.compare("cduration") == 0)
	{
		sprintf(aux, "%d", c.cduration);
	}
	if (variable.compare("cincubation") == 0)
	{
		sprintf(aux, "%d", c.cincubation);
	}
	if (variable.compare("infected") == 0)
	{
		sprintf(aux, "%d", c.infected);
	}
	if (variable.compare("alive") == 0)
	{
		sprintf(aux, "%d", c.alive);
	}
	if (variable.compare("state") == 0)
	{
		sprintf(aux, "%d", c.state);
	}
	ret = aux;
	return ret;
}
int count(int **neighbours, string variable, string value, vector<vector<Cell>> &cells)
{
	int i = 0;
	int x = neighbours[i][0];
	int y = neighbours[i][1];
	int found = 0;
	while (found == false && i < MAX_NEIGH)
	{
		if (x != -1)
		{
			if (foundVariable(cells[x][y], variable).compare(value) == 0)
			{
				found++;
			}
		}
		x = neighbours[i][0];
		y = neighbours[i][1];
		i++;
	}
	return found;
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

				if (cells[i][j].state == NO_INFECTIOUS && (count(c_neighbours, string("quarantined"), std::to_string(true), cells) > 2))
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

				if (cells[i][j].state == HINFECTED && (count(c_neighbours, string("state"), std::to_string(HINFECTED), cells) > 1))
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
