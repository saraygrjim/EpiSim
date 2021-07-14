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

 #define N 100
#define PRUEBA 0
#define ADIOS 1
#define HOLA 2

 int neighType = MOORE;
 
 int days = 100;
 
 int nStrain  = 1;
 
 double probability = 0.6;
 int daystoinfect = 4;
 

 class Cell{ 
 public: 
 bool alive; 
 int state; 
 bool infected;  
 bool probability_c;
bool days;
bool alive;
 Cell(); 
 void infect(int, int); 
 }; 
Cell::Cell (){
 alive = true;
 state  = 0;
 infected = false;
 probability_c = 0.7;
days = 1;
alive = true;
}
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
  
 
  if(currentDay >= 0) {
 for (int i = 0; i < N; i++){ 
         for (int j = 0; j < N; j++){    
  
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
  
  if( cells[i][j].alive == true && probability > ((rand() % (1001))/1000.0) ) {
 cells[i][j].days = cells[i][j].days + 1;  
 daystoinfect = daystoinfect + 1;  
 cells[i][j].probability_c = ADIOS;  
   
}
  
 } 
 } 
 } 
  if(currentDay >= 50) {
 for (int i = 0; i < N; i++){ 
         for (int j = 0; j < N; j++){    
  
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
  
  if( cells[i][j].alive == true && probability > ((rand() % (1001))/1000.0) ) {
 cells[i][j].days = cells[i][j].days + 1;  
 daystoinfect = daystoinfect + 1;  
 cells[i][j].probability_c = ADIOS;  
   
}
  
 } 
 } 
 } 
   }