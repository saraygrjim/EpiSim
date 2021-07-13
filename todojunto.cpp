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

#define MAX_NEIGH  12

/*HASTA AQUI*/

#define N 200

// Types of cell states
#define NO_CHANGE     0
#define NO_INFECTIOUS 1
#define INFECTED      2
#define RECOVER       3
#define QUARANTINE    4
#define DIE           5

// For the simulation
int days       = 170;  // Days to simulate
int neighType  = NEUMANN;

// Simulation parameters
double probability  = 0.6;   // Probability that infections happens
int    daysToInfect = 4;     // Days to become infect
int    incubation   = 3;     // Days of incubation before the cell is infectious
int    duration     = 10;    // How man days to finish and recover or to get worse
double deadliness   = 0.02;  // How deadly is the disease
double inmunity     = 0.5;   // How inmune the cell is to infection after recovery

// Measures
// int    medDay          = 150;   // Day when the cell take the medicine
// double medEfficacy     = 0.5;   // Efficacy of the medicine
int    quaratineInit       = 100;   // Day when the cell start quarentine
int    quaratineDays       = 7;
// double quarentEfficacy = 0.3;   // Efficacy of the quarentine
// double quarentProb     = 0.7;


class Cell{
   public:
    bool alive;
    int incubation;           //Days of incubation before the cell is infectious
    bool infected;            // If the cell is infected or not
    int duration;             // How many days to finish and recover or to get worse
    int inmunity;             // How inmune the cell is to infection after recovery or not
    bool medication;          // If the cell has taken its medication or not
    bool quarantined;         // If the cell is in quarantine
    int state;
    int quaratineDays; 

    Cell();
    void infect(int, int);

};


Cell::Cell (){
    alive         = true;
    state         = 0;
    infected      = false;       // If the cell is infected or not

    //Parámetros a partir de aquí
    incubation    = -1;          // Days of incubation before the cell is infectious
    duration      = -1;          // How many days to finish and recover or to get worse
    inmunity      = -1;          // How inmune the cell is to infection after recovery or not
    medication    = false;       // If the cell has taken its medication or not
    quarantined   = false;       // If the cell is in quarantine
    quaratineDays = -1;
}

// Esto hay que ver como hacerlo y que variables tienen que existir si o si y cosas así
// Cell become infected  
void Cell::infect(int incubation, int duration){
    infected   = true;
    state      = 1;
    incubation = incubation;
    duration   = duration;
}




bool search(int** neighbours, int state, vector<vector<Cell>> &cells){
    int i = 0;
    int x = neighbours[i][0];
    int y = neighbours[i][1];
    bool found = false;
    while (found == false && i < MAX_NEIGH){ 
        if (x != -1){
            if(cells[x][y].state == state && (duration - cells[x][y].duration) >= daysToInfect){
                found = true;
            }
        }
        x = neighbours[i][0];
        y = neighbours[i][1];
        i++;
    }


    return found;
}

int sum_quarantined(int** neighbours, vector<vector<Cell>> &cells){
    int i = 0;
    int x = neighbours[i][0];
    int y = neighbours[i][1];
    int sum = 0;
    while (i < MAX_NEIGH){ 
        if(x != -1 && cells[x][y].quarantined){
            sum++;
        }

        x = neighbours[i][0];
        y = neighbours[i][1];
        i++;
    }
    return sum;
}


void evaluation(vector<vector<Cell>> &cells, int currentDay){

    // vector<vector<Cell>> cells(N, vector<Cell>(N));
    // for (int i = 0; i < N; i++){
    //     for (int j = 0; j < N; j++){ 
    //         cells[i][j] = c[i][j];
    //     }
    // } 

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){   
            // CAMBIO DE ESTADO DEPENDIENDO DE VECINOS  
            int** c_neighbours;
            c_neighbours = (int**)malloc(MAX_NEIGH*sizeof(int *));
            for (int i = 0; i<MAX_NEIGH; i++){
                c_neighbours[i] = (int *)malloc(2*sizeof(int));
            }
            for (int i = 0; i<MAX_NEIGH; i++){
                for (int j = 0; j<2; j++){
                    c_neighbours[i][j] = -1;
                }
            }
            searchNeighbours(c_neighbours, N, i, j, neighType);

            //LAS REGLAS SE EMPIEZAN A COLOCAR AQUI
            if (cells[i][j].state == NO_CHANGE && search(c_neighbours, INFECTED, cells)){ //The cell has never been infected
                double num = (rand() % (1001))/1000.0;
                if (num < probability){
                    cells[i][j].state      = NO_INFECTIOUS; //Yellow
                    cells[i][j].infected   = true;
                    cells[i][j].incubation = incubation;
                    cells[i][j].duration   = duration;
                }
                continue;

            }

            if (cells[i][j].state == RECOVER && search(c_neighbours, INFECTED, cells)){
                
                double num = (rand() % (1001))/1000.0;
                if (num > cells[i][j].inmunity){
                    cells[i][j].state       = NO_INFECTIOUS;
                    cells[i][j].infected    = true;
                    cells[i][j].incubation  = incubation;
                    cells[i][j].duration    = duration;
                }
                continue;
            }

            if (cells[i][j].state == INFECTED && sum_quarantined(c_neighbours, cells) > 2){
                cells[i][j].state         = QUARANTINE; //Blue
                cells[i][j].quarantined   = true;
                cells[i][j].quaratineDays = quaratineDays;
                continue;
            }

            if (cells[i][j].state != INFECTED && cells[i][j].state != DIE && cells[i][j].state != RECOVER && search(c_neighbours, INFECTED, cells) && quaratineInit < currentDay){
                cells[i][j].state         = QUARANTINE; //Blue
                cells[i][j].quarantined   = true;
                cells[i][j].quaratineDays = quaratineDays;
                continue;
            }
            //LAS REGLAS TERMINAN DE COLOCARSE AQUI 
            
            //CAMBIO DE ESTADO DEPENDIENDO DE VARIABLES
            if(cells[i][j].state == QUARANTINE){
                if(cells[i][j].quaratineDays > 0){
                    cells[i][j].quaratineDays--;
                    if(cells[i][j].infected){
                        if(cells[i][j].incubation > 0){
                            cells[i][j].incubation--;
                        }else{
                            if(cells[i][j].duration > 0){
                                cells[i][j].duration--;
                            }else {
                                
                                double num = (rand() % (1001))/1000.0;
                                if(num < deadliness){
                                    cells[i][j].state         = DIE;
                                    cells[i][j].alive         = false;
                                    cells[i][j].infected      = false;
                                    cells[i][j].quarantined   = false;
                                    cells[i][j].quaratineDays = -1;
                                    cells[i][j].duration      = -1;
                                    cells[i][j].incubation    = -1;

                                }else {
                                    cells[i][j].infected   = false;
                                    cells[i][j].incubation = -1;
                                    cells[i][j].duration   = -1;
                                    if(cells[i][j].inmunity == -1){
                                        cells[i][j].inmunity = inmunity;
                                    } else{
                                        cells[i][j].inmunity *= 1.1;
                                    }
                                }
                            }
                        }
                    }
                } else{
                    if(cells[i][j].infected){
                        cells[i][j].quaratineDays = 2;
                    } else{
                        cells[i][j].state         = RECOVER;
                        cells[i][j].quarantined   = false;
                        cells[i][j].quaratineDays = -1;
                    }
                }
            } else if (cells[i][j].state == NO_INFECTIOUS) {
                if(cells[i][j].incubation > 0){
                    cells[i][j].incubation--;
                } else{
                    cells[i][j].state = INFECTED;
                    cells[i][j].duration--;
                }
            } else if (cells[i][j].state == INFECTED) {
                if(cells[i][j].duration > 0) {
                    cells[i][j].duration--;
                } else{
                    
                    double num = (rand() % (1001))/1000.0;
                    if(num < deadliness) {
                        cells[i][j].state         = DIE;
                        cells[i][j].alive         = false;
                        cells[i][j].infected      = false;
                        cells[i][j].duration      = -1;
                        cells[i][j].incubation    = -1;

                    } else{
                        cells[i][j].state      = RECOVER;
                        cells[i][j].infected   = false;
                        cells[i][j].incubation = -1;
                        cells[i][j].duration   = -1;
                        if(cells[i][j].inmunity == -1){
                            cells[i][j].inmunity = inmunity;
                        } else{
                            cells[i][j].inmunity *= 1.1;
                        }
                    }
                }
            }

        }
    }

    // return cells;
}

/*FUNCION DRAWCELL*/
void drawCell(vector<vector<Cell>> &cells){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){   
            switch (cells[i][j].state){
            case NO_CHANGE:
                glColor3f(1.0, 1.0, 1.0); //white
                break;
            case NO_INFECTIOUS:
                glColor3f(0.9804, 0.7765, 0.0); //yellow
                break;
            case INFECTED:
                glColor3f(0.8431, 0.0353, 0.1149); //red
                break;
            case RECOVER:
                glColor3f(0.0941, 0.5529, 0.251); //green
                break;
            case QUARANTINE:
                glColor3f(0.2039, 0.7333, 0.8549); //blue
                break;
            case DIE:
                glColor3f(0.0, 0.0, 0.0); //black
                break;
            }
            glRectd(i, j, i+1, j+1);
        }
    }
}