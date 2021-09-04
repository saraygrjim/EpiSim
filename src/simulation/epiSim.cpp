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
  
 #define MAX_NEIGH  12 
 #define NO_CHANGE 0

#define N 100
#define DIE 1
#define RECOVER 2
#define NO_INFECTIOUS 3
#define INFECT 4


ofstream initial_strain("Data/DataStrain_initial_strain.csv");
ofstream second_strain("Data/DataStrain_second_strain.csv");

int nStates = 5;
int neighType = NEUMANN;
 int days = 500;
 int nStrain  = 2;
 
 int virus1incubation = 4;
 int virus2incubation = 4;
 int desease1duration = 10;
 int desease2duration = 15;
 double initialinmunity = 0.5;
 double deadliness1 = 0.1;
 double deadliness2 = 0.1;
 int counter = 0;
 

class Cell{ 
 public: 
bool virus2;
bool virus1;
double cellinmunity2;
double cellinmunity1;
int timesinfected;
int celldeseaseduration;
int cellvirusincub;
bool infected;
bool alive;
int state;
 Cell(); 
 void infect(); 
 }; 
Cell::Cell (){
 
virus2 = false;
virus1 = false;
cellinmunity2 = -1.0;
cellinmunity1 = -1.0;
timesinfected = 0;
celldeseaseduration = -1;
cellvirusincub = -1;
infected = false;
alive = true;
state = 0;
}
  
  void Cell::infect(){ 
	infected = true; 
 
state = INFECT;  
 virus1 = true;  
 celldeseaseduration = desease1duration;  
   
 
 
 }
string foundVariable(Cell c, string variable) { 
     char aux[100]; 
     string ret = ""; 
 if (variable.compare("virus2")==0) { 
sprintf(aux, "%d", c.virus2);
} if (variable.compare("virus1")==0) { 
sprintf(aux, "%d", c.virus1);
} if (variable.compare("cellinmunity2")==0) { 
sprintf(aux, "%f", c.cellinmunity2);
} if (variable.compare("cellinmunity1")==0) { 
sprintf(aux, "%f", c.cellinmunity1);
} if (variable.compare("timesinfected")==0) { 
sprintf(aux, "%d", c.timesinfected);
} if (variable.compare("celldeseaseduration")==0) { 
sprintf(aux, "%d", c.celldeseaseduration);
} if (variable.compare("cellvirusincub")==0) { 
sprintf(aux, "%d", c.cellvirusincub);
} if (variable.compare("infected")==0) { 
sprintf(aux, "%d", c.infected);
} if (variable.compare("alive")==0) { 
sprintf(aux, "%d", c.alive);
} if (variable.compare("state")==0) { 
sprintf(aux, "%d", c.state);
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
 int results[nStates]; 
 for (int i=0; i<nStates; i++){ 
     results[i] = 0; 
 } 

 if (currentTick == 0){ 
initial_strain << "currentTick,NO_CHANGE,DIE,RECOVER,NO_INFECTIOUS,INFECT \n";
second_strain << "currentTick,NO_CHANGE,DIE,RECOVER,NO_INFECTIOUS,INFECT \n";
}
 
if(currentTick >= 0) {
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
  
 if( cells[i][j].state == NO_CHANGE && count(c_neighbours, string("virus1"), std::to_string(true), cells) > 0 ) {
 cells[i][j].state = NO_INFECTIOUS;  
 cells[i][j].infected = true;  
 cells[i][j].cellvirusincub = virus1incubation;  
 cells[i][j].timesinfected = cells[i][j].timesinfected + 1;  
 cells[i][j].cellinmunity1 = initialinmunity;  
 continue; 
}
  
 if( cells[i][j].state == RECOVER ) {
 if( count(c_neighbours, string("virus1"), std::to_string(true), cells) > 0 && ((rand() % (1001))/1000.0) > cells[i][j].cellinmunity1 ) {
 cells[i][j].state = NO_INFECTIOUS;  
 cells[i][j].infected = true;  
 cells[i][j].cellvirusincub = virus1incubation;  
 cells[i][j].timesinfected = cells[i][j].timesinfected + 1;  
 cells[i][j].cellinmunity1 = cells[i][j].cellinmunity1 + ( cells[i][j].timesinfected * 0.1 );  
 continue; 
}
  
   
}
  
 if( cells[i][j].infected ) {
 if( cells[i][j].cellvirusincub > 0 ) {
 cells[i][j].cellvirusincub = cells[i][j].cellvirusincub - 1;  
 if( cells[i][j].cellvirusincub == 0 ) {
 cells[i][j].state = INFECT;  
 cells[i][j].virus1 = true;  
 cells[i][j].celldeseaseduration = desease1duration;  
   
}
  
   
}
  
 if( cells[i][j].celldeseaseduration > 0 ) {
 cells[i][j].celldeseaseduration = cells[i][j].celldeseaseduration - 1;  
 if( cells[i][j].celldeseaseduration == 0 ) {
 if( ((rand() % (1001))/1000.0) < deadliness1 ) {
 cells[i][j].state = DIE;  
 cells[i][j].alive = false;  
 cells[i][j].infected = false;  
 cells[i][j].virus1 = false;  
 cells[i][j].celldeseaseduration = - 1;  
 cells[i][j].cellvirusincub = - 1;  
   
} else {
 cells[i][j].state = RECOVER;  
 cells[i][j].infected = false;  
 cells[i][j].virus1 = false;  
 cells[i][j].celldeseaseduration = - 1;  
 cells[i][j].cellvirusincub = - 1;  
   
}  
   
}
  
   
}
  
   
}
  
 } 
 } for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
        results[cells[i][j].state]++;
    }
}
initial_strain << currentTick ;
for(int i=0; i<nStates;i++){
    initial_strain <<  "," << results[i];
}
initial_strain << "\n";
 
 } 
 if(currentTick >= 350) {
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
  
 if( ((rand() % (1001))/1000.0) < 0.1 && counter < 100 ) {
 counter = counter + 1;  
 cells[i][j].state = NO_INFECTIOUS;  
 cells[i][j].infected = true;  
 cells[i][j].cellvirusincub = virus2incubation;  
 cells[i][j].timesinfected = cells[i][j].timesinfected + 1;  
 cells[i][j].cellinmunity2 = initialinmunity;  
 continue; 
}
  
 if( cells[i][j].state == NO_CHANGE && count(c_neighbours, string("virus2"), std::to_string(true), cells) > 0 ) {
 cells[i][j].state = NO_INFECTIOUS;  
 cells[i][j].infected = true;  
 cells[i][j].cellvirusincub = virus2incubation;  
 cells[i][j].timesinfected = cells[i][j].timesinfected + 1;  
 cells[i][j].cellinmunity2 = initialinmunity;  
 continue; 
}
  
 if( cells[i][j].state == RECOVER ) {
 if( count(c_neighbours, string("virus2"), std::to_string(true), cells) > 0 && ((rand() % (1001))/1000.0) > cells[i][j].cellinmunity2 ) {
 cells[i][j].state = NO_INFECTIOUS;  
 cells[i][j].infected = true;  
 cells[i][j].cellvirusincub = virus2incubation;  
 cells[i][j].timesinfected = cells[i][j].timesinfected + 1;  
 cells[i][j].cellinmunity2 = cells[i][j].cellinmunity2 + ( cells[i][j].timesinfected * 0.1 );  
 continue; 
}
  
   
}
  
 if( cells[i][j].infected ) {
 if( cells[i][j].cellvirusincub > 0 ) {
 cells[i][j].cellvirusincub = cells[i][j].cellvirusincub - 1;  
 if( cells[i][j].cellvirusincub == 0 ) {
 cells[i][j].state = INFECT;  
 cells[i][j].virus2 = true;  
 cells[i][j].celldeseaseduration = desease2duration;  
   
}
  
   
}
  
 if( cells[i][j].celldeseaseduration > 0 ) {
 cells[i][j].celldeseaseduration = cells[i][j].celldeseaseduration - 1;  
 if( cells[i][j].celldeseaseduration == 0 ) {
 if( ((rand() % (1001))/1000.0) < deadliness2 ) {
 cells[i][j].state = DIE;  
 cells[i][j].alive = false;  
 cells[i][j].infected = false;  
 cells[i][j].virus2 = false;  
 cells[i][j].celldeseaseduration = - 1;  
 cells[i][j].cellvirusincub = - 1;  
   
} else {
 cells[i][j].state = RECOVER;  
 cells[i][j].infected = false;  
 cells[i][j].virus2 = false;  
 cells[i][j].celldeseaseduration = - 1;  
 cells[i][j].cellvirusincub = - 1;  
   
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
second_strain << currentTick ;
for(int i=0; i<nStates;i++){
    second_strain <<  "," << results[i];
}
second_strain << "\n";
 } 
   } 
 void drawCell(vector<vector<Cell>> &cells){ 
 for (int i = 0; i < N; i++){ 
 for (int j = 0; j < N; j++){ 
 switch (cells[i][j].state){ 
 case NO_CHANGE: 
 glColor3f(1.000000, 1.000000, 1.000000); 
 break; 
 case INFECT:
 glColor3f(1.000000,0.000000,0.000000); 
 break;
 case NO_INFECTIOUS:
 glColor3f(1.000000,0.800000,0.600000); 
 break;
 case RECOVER:
 glColor3f(0.000000,1.000000,0.000000); 
 break;
 case DIE:
 glColor3f(0.000000,0.000000,0.000000); 
 break;
   } 
 glRectd(i, j, i+1, j+1); 
 }
 }
  }
 