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

#define N 50

// Types of cell states
#define NO_CHANGE     0
#define NO_INFECTIOUS 1
#define INFECTED      2
#define RECOVER       3
#define QUARANTINE    4
#define DIE           5

// For the simulation
int days       = 10;  // Days to simulate
int neighType  = MOORE;
int nStrain   = 2;

// Simulation parameters
double probability  = 0.6;   // Probability that infections happens
int    daysToInfect = 4;     // Days to become infect
int    gincubation   = 3;     // Days of incubation before the cell is infectious
int    gduration     = 10;    // How man days to finish and recover or to get worse
double deadliness   = 0.02;  // How deadly is the disease
double inmunity     = 0.5;   // How inmune the cell is to infection after recovery

// Measures
int    medDay          = 150;   // Day when the cell take the medicine
double medEfficacy     = 0.5;   // Efficacy of the medicine
int    quaratineInit       = 100;   // Day when the cell start quarentine
int    quaratineDays       = 7;
double quarentEfficacy = 0.3;   // Efficacy of the quarentine
double quarentProb     = 0.7;


class Cell{
   public:
    bool alive;
    int  state;
    bool infected;            // If the cell is infected or not
    
    int incubation;           // Days of incubation before the cell is infectious
    int duration;             // How many days to finish and recover or to get worse
    int inmunity;             // How inmune the cell is to infection after recovery or not
    bool medication;          // If the cell has taken its medication or not
    bool quarantined;         // If the cell is in quarantine
    int quaratineDays; 

    Cell();
    void infect();

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
void Cell::infect(){
    infected   = true;
    state      = 1;
    incubation = gincubation;
    duration   = gduration;
}

string foundVariable(Cell c, string variable) {
    char aux[100];
    string ret = "";

    if (variable.compare("alive")==0) {
        sprintf(aux, "%d", c.alive);
    } else if ( variable.compare("state")==0) {
        sprintf(aux, "%d", c.state);
    } else if ( variable.compare("infected")==0) {
        sprintf(aux, "%d", c.infected);
    } else if ( variable.compare("incubation")==0) {
        sprintf(aux, "%d", c.incubation);
    } else if ( variable.compare("duration")==0) {
        sprintf(aux, "%d", c.duration);
    } else if ( variable.compare("inmunity")==0) {
        sprintf(aux, "%d", c.inmunity);
    } else if ( variable.compare("medication")==0) {
        sprintf(aux, "%d", c.medication);
    } else if ( variable.compare("quarantined")==0) {
        sprintf(aux, "%d", c.quarantined);
    } else if ( variable.compare("quaratineDays")==0) {
        sprintf(aux, "%d", c.quaratineDays);
    }   
    ret = aux;
    return ret;

}


int count(int** neighbours, string variable, string value, vector<vector<Cell>> &cells){
    int i = 0;
    int x = neighbours[i][0];
    int y = neighbours[i][1];
    int found = 0;
    while (found == false && i < MAX_NEIGH){ 
        if (x != -1){
            if(foundVariable(cells[x][y], variable).compare(value) == 0){
                found ++;
            }
        }
        x = neighbours[i][0];
        y = neighbours[i][1];
        i++;
    }
    return found;
}



void evaluation(vector<vector<Cell>> &cells, int currentTick){
    int results[nStrain][2];
    for (int i = 0; i < nStrain; i++){
        for (int j = 0; j < 2; j++){   
            results[i][j] = 0;
        }
    }
    if (currentTick >= 0) {	
        // Cepa 1 
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
                if (cells[i][j].state == NO_CHANGE && count(c_neighbours, string("state"), std::to_string(INFECTED), cells) > 1){ //The cell has never been infected
                    double num = (rand() % (1001))/1000.0;
                    if (num < probability){
                        cells[i][j].state      = NO_INFECTIOUS; //Yellow
                        cells[i][j].infected   = true;
                        cells[i][j].incubation = gincubation;
                        cells[i][j].duration   = gduration;
                    }
                    continue;

                }

                if (cells[i][j].state == RECOVER && count(c_neighbours, string("state"), std::to_string(INFECTED), cells) > 1){
                    
                    double num = (rand() % (1001))/1000.0;
                    if (num > cells[i][j].inmunity){
                        cells[i][j].state       = NO_INFECTIOUS;
                        cells[i][j].infected    = true;
                        cells[i][j].incubation  = gincubation;
                        cells[i][j].duration    = gduration;
                    }
                    continue;
                }

                if (cells[i][j].state == INFECTED && count(c_neighbours, string("quarantined"), std::to_string(true), cells) > 2){
                    cells[i][j].state         = QUARANTINE; //Blue
                    cells[i][j].quarantined   = true;
                    cells[i][j].quaratineDays = quaratineDays;
                    continue;
                }

                if (cells[i][j].state != INFECTED && cells[i][j].state != DIE && cells[i][j].state != RECOVER && count(c_neighbours, string("state"), std::to_string(INFECTED), cells) > 1 && quaratineInit < currentTick){
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

        for (int i = 0; i < nStrain; i++){
            for (int j = 0; j < 2; j++){   
                if (cells[i][j].alive == false) {
                    results[0][1] ++;
                }else if (cells[i][j].infected == false) {
                    results[0][0] ++;
                }
            }
        }
	
    }
    // Cepa 2
    if(currentTick >= 5000) {
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


                if (cells[i][j].state == NO_INFECTIOUS && count(c_neighbours, string("state"), std::to_string(INFECTED), cells) > 1){ //The cell has never been infected
                    // double num = (rand() % (1001))/1000.0;
                    cells[i][j].state      = INFECTED; //Yellow
                    cells[i][j].infected   = true;
                    cells[i][j].incubation = gincubation;
                    cells[i][j].duration   = gduration;
                    // continue;
                }
            }
        }
		
        for (int i = 0; i < nStrain; i++){
            for (int j = 0; j < 2; j++){   
                if (cells[i][j].alive == false) {
                    results[1][1] ++;
                }else if (cells[i][j].infected == false) {
                    results[1][0] ++;
                }
            }
        }

    // return cells;
    }

	printf("%d;", currentTick);
	for (int i = 0; i < nStrain; i++){
		for (int j = 0; j < 2; j++){  
			printf("%d;", results[i][j]);
		}
	}
	printf("\n\n\n");
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