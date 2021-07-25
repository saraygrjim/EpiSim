#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "sim.h"
#include "grid.h"
#include <vector>

using namespace std;
using std::vector;

#define MAX_NEIGH 12
#define NO_CHANGE 0

#define N 100
#define DIE 1
#define QUARANTINE 2
#define RECOVER 3
#define NO_INFECTIOUS 4
#define SINFECTED 5


ofstream MyFile("filename.csv");

int nStates = 6;
int neighType = NEUMANN;
int days = 200;
int nStrain = 2;

double probability = 0.6;
int daystoinfect = 4;
int gincubation = 3;
int gduration = 10;
double deadliness = 0.2;
double inmunity = 0.5;
int quaratineinit = 100;
int quaratinedays = 7;

class Cell
{
public:
    int cquaratinedays;
    bool quarantined;
    bool medication;
    double cinmunity;
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

    cquaratinedays = 0;
    quarantined = false;
    medication = false;
    cinmunity = 0.0;
    cduration = 0;
    cincubation = 0;
    infected = false;
    alive = true;
    state = 0;
}

void Cell::infect()
{
    infected = true;
    state = NO_INFECTIOUS;
}
string foundVariable(Cell c, string variable)
{
    char aux[100];
    string ret = "";
    if (variable.compare("cquaratinedays") == 0)
    {
        sprintf(aux, "%d", c.cquaratinedays);
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
        sprintf(aux, "%f", c.cinmunity);
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
    int results[nStates];
    for (int i=0; i<nStates; i++){
        results[i] = 0;
    }
    if (currentTick == 0){
        MyFile << "ticks;NO_CHANGE;DIE;QUARANTINE;RECOVER;NO_INFECTIOUS;SINFECTED\n";
    }
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

                if (cells[i][j].state == NO_CHANGE && count(c_neighbours, string("state"), std::to_string(SINFECTED), cells) > 0 && ((rand() % (1001)) / 1000.0) < probability)
                {
                    cells[i][j].state = NO_INFECTIOUS;
                    cells[i][j].infected = true;
                    cells[i][j].cincubation = gincubation;
                    cells[i][j].cduration = gduration;
                    continue;
                }

                if (cells[i][j].state == RECOVER && count(c_neighbours, string("state"), std::to_string(cells[i][j].infected), cells) > 0 && ((rand() % (1001)) / 1000.0) < cells[i][j].cinmunity)
                {
                    cells[i][j].state = NO_INFECTIOUS;
                    cells[i][j].infected = true;
                    cells[i][j].cincubation = gincubation;
                    cells[i][j].cduration = gduration;
                    continue;
                }

                if (cells[i][j].state != cells[i][j].infected && cells[i][j].state != DIE && cells[i][j].state != RECOVER && count(c_neighbours, string("state"), std::to_string(cells[i][j].infected), cells) && quaratineinit < currentTick)
                {
                    cells[i][j].state = QUARANTINE;
                    cells[i][j].quarantined = true;
                    cells[i][j].cquaratinedays = quaratinedays;
                    continue;
                }

                if (cells[i][j].state == QUARANTINE)
                {
                    if (cells[i][j].cquaratinedays > 0)
                    {
                        cells[i][j].cquaratinedays = cells[i][j].cquaratinedays - 1;
                        if (cells[i][j].infected)
                        {
                            if (cells[i][j].cincubation > 0)
                            {
                                cells[i][j].cincubation = cells[i][j].cincubation - 1;
                            }
                            else
                            {
                                if (cells[i][j].cduration > 0)
                                {
                                    cells[i][j].cduration = cells[i][j].cduration - 1;
                                }
                                else
                                {
                                    if (((rand() % (1001)) / 1000.0) < deadliness)
                                    {
                                        cells[i][j].state = DIE;
                                        cells[i][j].alive = false;
                                        cells[i][j].infected = false;
                                        cells[i][j].quarantined = false;
                                        cells[i][j].cquaratinedays = -1;
                                        cells[i][j].cduration = -1;
                                        cells[i][j].cincubation = -1;
                                    }
                                    else
                                    {
                                        cells[i][j].infected = false;
                                        cells[i][j].cincubation = 0;
                                        cells[i][j].cduration = 0;
                                        if (cells[i][j].cinmunity == 0)
                                        {
                                            cells[i][j].cinmunity = inmunity;
                                        }
                                        else
                                        {
                                            cells[i][j].cinmunity = cells[i][j].cinmunity * 1.1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (cells[i][j].infected)
                        {
                            cells[i][j].cquaratinedays = 2;
                        }
                        else
                        {
                            cells[i][j].state = RECOVER;
                            cells[i][j].quarantined = false;
                            cells[i][j].cquaratinedays = 0;
                        }
                    }
                }
                else if (cells[i][j].state == NO_INFECTIOUS)
                {
                    if (cells[i][j].cincubation > 0)
                    {
                        cells[i][j].cincubation = cells[i][j].cincubation - 1;
                    }
                    else
                    {
                        cells[i][j].state = SINFECTED;
                        cells[i][j].cduration = cells[i][j].cduration - 1;
                    }
                }
                else if (cells[i][j].state == SINFECTED)
                {
                    if (cells[i][j].cduration > 0)
                    {
                        cells[i][j].cduration = cells[i][j].cduration - 1;
                    }
                    else
                    {
                        if (((rand() % (1001)) / 1000.0) < deadliness)
                        {
                            cells[i][j].state = DIE;
                            cells[i][j].alive = false;
                            cells[i][j].infected = false;
                            cells[i][j].cduration = 0;
                            cells[i][j].cincubation = 0;
                        }
                        else
                        {
                            cells[i][j].state = RECOVER;
                            cells[i][j].infected = false;
                            cells[i][j].cincubation = 0;
                            cells[i][j].cduration = 0;
                            if (cells[i][j].cinmunity == 0)
                            {
                                cells[i][j].cinmunity = inmunity;
                            }
                            else
                            {
                                cells[i][j].cinmunity = cells[i][j].cinmunity * 1.1;
                            }
                        }
                    }
                }
            }
        }
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                results[cells[i][j].state]++;
            }
        }
        MyFile << currentTick ;
        for(int i=0; i<nStates;i++){
            MyFile <<  ";" << results[i];
        }
        MyFile << "\n";
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
            case SINFECTED:
                glColor3f(1.000000, 0.000000, 0.000000);
                break;
            case NO_INFECTIOUS:
                glColor3f(1.000000, 0.800000, 0.600000);
                break;
            case RECOVER:
                glColor3f(0.000000, 1.000000, 0.000000);
                break;
            case QUARANTINE:
                glColor3f(0.600000, 0.800000, 1.000000);
                break;
            case DIE:
                glColor3f(0.000000, 0.000000, 0.000000);
                break;
            }
            glRectd(i, j, i + 1, j + 1);
        }
    }
}
