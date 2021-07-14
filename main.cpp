#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "sim.h"
#include "grid.h"
#include "todojunto.cpp"

using namespace std;
using std::vector;

#define FPS        10

void timerCallback(int);
void displayCallback();
void reshapeCallback(int, int);
void newPopulation();
void infectOneCell();
bool search(int**, int);
int  sum_quarantined(int**);
void simulation();
int currentDay = 0;


vector<vector<Cell>> cells(N, vector<Cell>(N));

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
    int i = N/2;
    int j = N/2;
    cells[i][j].infect(incubation, duration);
}

void simulation(){
    srand(time(NULL));
    if (currentDay > days){
        exit(0);
    }
    evaluation(cells, currentDay);
}