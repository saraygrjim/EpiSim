#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "cell.cpp"
#include "grid.cpp"

// For the simulation
int width  = 700;  // Size of the grid
int height = 800;  // Size of the grid
int n      = 50;
int sizeX  = width/n;  // Size of cell
int sizeY  = height/n; // Size of cell 
int days   = 700;  // Days to simulate
// string output = ""; // Name of the output file

// Simulation parameters
double probability = 0.15;  // Probability that infections happens
int incubation     = 3;     // Days of incubation before the cell is infectious
int duration       = 10;    // How man days to finish and recover or to get worse
double deadliness  = 0.02;  // How deadly is the disease
double inmunity    = 0.5;   // How inmune the cell is to infection after recovery

// Measures
int medDay             = 150;   // Day when the cell take the medicine
double medEfficacy     = 0.5;   // Efficacy of the medicine
int quarentDay         = 100;   // Day when the cell start quarentine
double quarentEfficacy = 0.3;   // Efficacy of the quarentine
double quarentProb     = 0.7;


int main(){
    int n = 50;
    Cell cells[n][n];
    int state[n][n];
    int currentTime;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; i++){
            if ( !cells[i][j].infected ){
                continue;
            }
            //If the cell is in quarantine we can pass to the next
            if ( cells[i][j].quarantined ){
                int processQResult = cells[i][j].processQuarantine(quarentEfficacy);
                if ( processQResult == 1 ){
                    cells[i][j].recover(inmunity);
                    state[i][j] = cells[i][j].state;
                }
            }

            // If the cell is infected then we have to process 
            int processResult = cells[i][j].process(deadliness);

            if ( processResult == 0 ){  //If the cell is still incubating then we can pass to the next
                continue;
            } else if ( processResult == 1 ) { //If the cell has recovered then we can pass to the next
                cells[i][j].recover(inmunity);
                state[i][j] = cells[i][j].state;
                continue;
            } else if ( processResult == 2 ){ //The cell hasnt recovered so dead
                cells[i][j].die();
                state[i][j] = cells[i][j].state;
            }

            // Medicine aplication when its time
            if ( !cells[i][j].medication && currentTime > medDay ) {
                int medicationResult = cells[i][j].medicate(medEfficacy);
                if ( medicationResult ) { // If medicine is successful then the cell recover and pass to the next
                    cells[i][j].recover(inmunity);
                    state[i][j] = cells[i][j].state;
                    continue;
                }
            }

            srand(time(NULL));
            double num = (rand() % (1001))/1000.0;
            if ( !cells[i][j].quarantined && (currentTime > quarentDay) && num > quarentProb and cells[i][j].alive ) {
                cells[i][j].quarantine();
                state[i][j] = cells[i][j].state;
            }

            // unless quarantined, look for neighbours and infect them
            if ( !cells[i][j].quarantined ){
                // find all the cell's neighbours
                int** neighbours;
                neighbours = searchNeighbours(n, cells[i][j].x, cells[i][j].y);
                int i = 0;
                int x = neighbours[i][0];
                int y = neighbours[i][1];
                while (neighbours[i] != NULL){
                        if (cells[x][y].alive == true){
                            if(cells[x][y].infected == true){
                                continue;
                            }

                            //probability of re-infection
                            srand(time(NULL));
                            num = (rand() % (1001))/1000.0;
                            if (num > cells[x][y].inmunity){
                                // if probability less than infection rate then cell gets infected
                                num = (rand() % (1001))/1000.0;
                                if (num < probability){
                                    cells[x][y].infect(incubation, duration);
                                    state[x][y] = cells[x][y].state;
                                }
                            }
                        }
                    i++;
                    x = neighbours[i][0];
                    y = neighbours[i][1];
                }
            }
            state[i][j] = cells[i][j].state;

        }
    }
    
}