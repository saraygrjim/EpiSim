/*GLOBAL_PROPERTIES*/

int neighType = MOORE;
int n = 100;
int days = 100;
double probability = 0.6;
int daystoinfect = 4;

int daystoinfect = 4;

/*CELL_PROPERTIES*/

bool alive = true;
int days = 1;
double probability = 0.7;

#define PRUEBA 0
#define ADIOS 1
#define HOLA 2
void drawCell(Cell cells[N][N]){ 
 for (int i = 0; i < N; i++){ 
 for (int j = 0; j < N; j++){ 
 switch (cells[i][j].state){ 
 case HOLA:
 glColor3f(255,5,10); 
 break;
 case ADIOS:
 glColor3f(255,5.600000,10); 
 break;
 case PRUEBA:
 glColor3f(15.876000,2,90); 
 break;
   } 
 glRectd(i, j, i+1, j+1); 
 }
 }
  }
 
/*RULES*/


if( alive == true ){ 
 cells[i][j].days = days + 1;  
 }
 
