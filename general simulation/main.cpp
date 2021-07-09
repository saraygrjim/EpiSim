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
#include "cell.h"

using namespace std;

#define FPS        10
#define MAX_NEIGH  12

void timerCallback(int);
void displayCallback();
void reshapeCallback(int, int);
void newPopulation();
void infectOneCell();
int search(int**, int);
int  sum_quarantined(int**);
void simulation();
int currentDay = 0;

/*AQUÍ - GLOBAL_PROPERTIES*/

// For the simulation
int n          = 50;
int days       = 150;  // Days to simulate
int neighType  = NEUMANN;

// // Simulation parameters
// double probability  = 0.6;   // Probability that infections happens
// int    daysToInfect = 4;     // Days to become infect
// int    incubation   = 3;     // Days of incubation before the cell is infectious
// int    duration     = 10;    // How man days to finish and recover or to get worse
// double deadliness   = 0.02;  // How deadly is the disease
// double inmunity     = 0.5;   // How inmune the cell is to infection after recovery

// // Measures
// // int    medDay          = 150;   // Day when the cell take the medicine
// // double medEfficacy     = 0.5;   // Efficacy of the medicine
// int    quaratineInit       = 100;   // Day when the cell start quarentine
// int    quaratineDays       = 7;
// // double quarentEfficacy = 0.3;   // Efficacy of the quarentine
// // double quarentProb     = 0.7;

/* HASTA AQUÍ */
Cell cells[N][N];
Cell newcells[N][N];

void init(){
    glClearColor(1.0,1.0,1.0,1.0); //Color de fondo
    initGrid(N, N);
}

int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Epidemic Simulation");
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutTimerFunc(0, timerCallback, 0);
    // glutSpecialFunc(keyboardCallback);

    //ESTO SOLO SE HACE UNA VEZ
    newPopulation();
    infectOneCell();

    init();
    glutMainLoop();
    return 1;
}
void displayCallback(){

    //prueba a poner aqui la ejecución
    // simulation();
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawCell(cells);
    glutSwapBuffers();
}

void reshapeCallback(int w, int h){
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, N, 0.0, N, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timerCallback(int){
    cerr << currentDay << endl;
    simulation();
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timerCallback, 0);
    currentDay++;
}

void newPopulation(){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            Cell cell;
            cells[i][j] = cell;
        } 
    }
}

// Infect the middle cell
void infectOneCell(){
    cells[25][22].state = NO_CHANGE;
    cells[25][22].alive = true;
    cells[25][23].state = NO_CHANGE;
    cells[25][23].alive = true;
    cells[25][24].state = NO_CHANGE;
    cells[25][24].alive = true;
    cells[25][25].state = NO_CHANGE;
    cells[25][25].alive = true;
    cells[25][26].state = NO_CHANGE;
    cells[25][26].alive = true;
}

// void seed(){
//     int i = N/2;
//     int j = N/2;
//     cells[25][25].state = DIE;
//     cells[25][26].state = DIE;
//     cells[25][24].state = DIE;
//     cells[24][23].state = DIE;
//     cells[25][23].state = DIE;
// }
 
int search(int** neighbours, int state){
    int i = 0;
    int x = neighbours[i][0];
    int y = neighbours[i][1];
    int found = 0;
    while (i < MAX_NEIGH){ 
        if (x != -1){
            if(cells[x][y].state == state){
                found ++;
            }
        }
        x = neighbours[i][0];
        y = neighbours[i][1];
        i++;
    }


    return found;
}

// int sum_quarantined(int** neighbours){
//     int i = 0;
//     int x = neighbours[i][0];
//     int y = neighbours[i][1];
//     int sum = 0;
//     while (i < MAX_NEIGH){ 
//         if(x != -1 && cells[x][y].quarantined){
//             sum++;
//         }

//         x = neighbours[i][0];
//         y = neighbours[i][1];
//         i++;
//     }
//     return sum;
// }

void simulation(){
    srand(time(NULL));
    if (currentDay > days){
        exit(0);
    }
    if (currentDay > 10){
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

            // Rule 1: Una celula muerta con exactamente 3 vecinas vivas, revive
            if( cells[i][j].alive == false && search(c_neighbours, NO_CHANGE) == 3 ){
                newcells[i][j].alive = true;
                newcells[i][j].state = NO_CHANGE;
                continue;
            }

            // Rule 2: Una ceula viva con menos de 2 o mas de 3 vecinas vivas muere (por soledad o por superpoblacion)
            if(cells[i][j].alive == true && (search(c_neighbours, NO_CHANGE) < 2 || search(c_neighbours, NO_CHANGE) > 3 )){
                newcells[i][j].alive = false;
                newcells[i][j].state = DIE;
                continue;
            }

            //LAS REGLAS TERMINAN DE COLOCARSE AQUI 
            
            //CAMBIO DE ESTADO DEPENDIENDO DE VARIABLES
            // if(cells[i][j].state == QUARANTINE){
            //     if(cells[i][j].quaratineDays > 0){
            //         cells[i][j].quaratineDays--;
            //         if(cells[i][j].infected){
            //             if(cells[i][j].incubation > 0){
            //                 cells[i][j].incubation--;
            //             }else{
            //                 if(cells[i][j].duration > 0){
            //                     cells[i][j].duration--;
            //                 }else {
                                
            //                     double num = (rand() % (1001))/1000.0;
            //                     if(num < deadliness){
            //                         cells[i][j].state         = DIE;
            //                         cells[i][j].alive         = false;
            //                         cells[i][j].infected      = false;
            //                         cells[i][j].quarantined   = false;
            //                         cells[i][j].quaratineDays = -1;
            //                         cells[i][j].duration      = -1;
            //                         cells[i][j].incubation    = -1;

            //                     }else {
            //                         cells[i][j].infected   = false;
            //                         cells[i][j].incubation = -1;
            //                         cells[i][j].duration   = -1;
            //                         if(cells[i][j].inmunity == -1){
            //                             cells[i][j].inmunity = inmunity;
            //                         } else{
            //                             cells[i][j].inmunity *= 1.1;
            //                         }
            //                     }
            //                 }
            //             }
            //         }
            //     } else{
            //         if(cells[i][j].infected){
            //             cells[i][j].quaratineDays = 2;
            //         } else{
            //             cells[i][j].state         = RECOVER;
            //             cells[i][j].quarantined   = false;
            //             cells[i][j].quaratineDays = -1;
            //         }
            //     }
            // } else if (cells[i][j].state == NO_INFECTIOUS) {
            //     if(cells[i][j].incubation > 0){
            //         cells[i][j].incubation--;
            //     } else{
            //         cells[i][j].state = INFECTED;
            //         cells[i][j].duration--;
            //     }
            // } else if (cells[i][j].state == INFECTED) {
            //     if(cells[i][j].duration > 0) {
            //         cells[i][j].duration--;
            //     } else{
                    
            //         double num = (rand() % (1001))/1000.0;
            //         if(num < deadliness) {
            //             cells[i][j].state         = DIE;
            //             cells[i][j].alive         = false;
            //             cells[i][j].infected      = false;
            //             cells[i][j].duration      = -1;
            //             cells[i][j].incubation    = -1;

            //         } else{
            //             cells[i][j].state      = RECOVER;
            //             cells[i][j].infected   = false;
            //             cells[i][j].incubation = -1;
            //             cells[i][j].duration   = -1;
            //             if(cells[i][j].inmunity == -1){
            //                 cells[i][j].inmunity = inmunity;
            //             } else{
            //                 cells[i][j].inmunity *= 1.1;
            //             }
            //         }
            //     }
            // }

        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){   
            cells[i][j] = newcells[i][j];
        }
    }
    }
}