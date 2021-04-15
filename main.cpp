#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sim.cpp"
#include "grid.cpp"

// #define COLUMNS 40
// #define ROWS    40
#define FPS        10


extern short sDirection;




//int state[N][N];


void timerCallback(int);
void displayCallback();
void reshapeCallback(int, int);
// void keyboardCallback(int,int,int);
void newPopulation();
void infectOneCell();
bool search(int**, int);
int  sum_quarantined(int**);
void simulation();


// For the simulation
// int width  = 700;  // Size of the grid
// int height = 800;  // Size of the grid
// int n      = 50;
// int sizeX  = width/N;  // Size of cell
// int sizeY  = height/N; // Size of cell 
int days   = 700;  // Days to simulate
int currentDay = 0;
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
Cell cells[50][50];

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
    // cerr << "hola" << endl;
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
    // cerr << cells[i][j].infected << endl;
}
 
bool search(int** neighbours, int state){
    int i = 0;
    int x = neighbours[i][0];
    int y = neighbours[i][1];
    bool found = false;
    while (found == false && i < 8){ 
        if (x != -1){
            if(cells[x][y].state == state){
                found = true;
            }
        }
        x = neighbours[i][0];
        y = neighbours[i][1];
        i++;
    }

    return found;
}

int sum_quarantined(int** neighbours){
    int i = 0;
    int x = neighbours[i][0];
    int y = neighbours[i][1];
    int sum = 0;
    while (i < 8){ 
        if(x != -1 && cells[x][y].quarantined){
            sum++;
        }

        x = neighbours[i][0];
        y = neighbours[i][1];
        i++;
    }
    return sum;
}

void simulation(){
    srand(time(NULL));
    if (currentDay > days){
        exit(0);
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){   

            // CAMBIO DE ESTADO DEPENDIENDO DE VECINOS  
            int** c_neighbours;
            c_neighbours = (int**)malloc(8*sizeof(int *));
            for (int i = 0; i<8; i++){
                c_neighbours[i] = (int *)malloc(2*sizeof(int));
            }
            for (int i = 0; i<8; i++){
                for (int j = 0; j<2; j++){
                    c_neighbours[i][j] = -1;
                }
            }
            searchNeighbours(c_neighbours, N, i, j);
            // cout << "hola";
            if (cells[i][j].state == NO_CHANGE && search(c_neighbours, INFECTED)){ //The cell has never been infected
                cells[i][j].state      = NO_INFECTIOUS; //Yellow
                cells[i][j].infected   = true;
                cells[i][j].incubation = incubation;
                cells[i][j].duration   = duration;
            
                continue;
            }
            // cout << "adios";
            if (cells[i][j].state == RECOVER && search(c_neighbours, INFECTED)){
                
                double num = (rand() % (1001))/1000.0;
                if (num > cells[i][j].inmunity){
                    cells[i][j].state       = NO_INFECTIOUS;
                    cells[i][j].infected    = true;
                    cells[i][j].incubation  = incubation;
                    cells[i][j].duration    = duration;
                }
                continue;
            }

            if (cells[i][j].state == INFECTED && sum_quarantined(c_neighbours) > 2){
                cells[i][j].state         = QUARANTINE; //Blue
                cells[i][j].quarantined   = true;
                cells[i][j].quaratineDays = 10;
                continue;
            }

            if (cells[i][j].state != INFECTED && cells[i][j].state != DIE && cells[i][j].state != RECOVER && search(c_neighbours, INFECTED) && quarentDay < currentDay){
                cells[i][j].state         = QUARANTINE; //Blue
                cells[i][j].quarantined   = true;
                cells[i][j].quaratineDays = 10;
                continue;
            }

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
}