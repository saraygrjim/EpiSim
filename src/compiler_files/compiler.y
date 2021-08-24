%{                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()
#include <pthread.h>
#include "src/compiler_files/lista.h"            // linked list

// Types of neighborhood
#define MOORE_T         0
#define NEUMANN_T       1
#define EXTENDED_T      2

// Types of sections
#define GLOBAL_T        0
#define CELL_T          1
#define STATE_T         2
#define INIT_T          3
#define STRAIN_T        4

// Type of variables
#define NO_TYPE           0
#define BOOLEAN_T         1
#define INTEGER_T         2
#define DOUBLE_T          3

int  memoria [26];         	// Se define una zona de memoria para las variables 
char identif[2048];
char define[2048];
char drawCell[2048];
char construct[2048];
char foundFunction[2048];
int typeExpression[100];
int i = 0;
int hasState = 0;
int numStrains = 1;

int  counter = 1;
nodeList *List;              // Lista enlazada para almacenar variables
int neighborhoodType = NEUMANN_T;
int section = GLOBAL_T;

char beginEvaluation [] = "void evaluation(vector<vector<Cell>> &cells, int currentTick){ \n int results[nStates]; \n for (int i=0; i<nStates; i++){ \n     results[i] = 0; \n } \n";   
char beginStrain [] = "for (int i = 0; i < N; i++){ \n\tfor (int j = 0; j < N; j++){\n  \n\t\tint** c_neighbours; \n\t\tc_neighbours = (int**)malloc(MAX_NEIGH*sizeof(int *)); \n\t\tfor (int i = 0; i<MAX_NEIGH; i++){ \n\t\t\tc_neighbours[i] = (int *)malloc(2*sizeof(int)); \n\t\t} \n\t\tfor (int i = 0; i<MAX_NEIGH; i++){ \n \t\t\tfor (int j = 0; j<2; j++){ \n\t\t\t\tc_neighbours[i][j] = -1; \n\t\t\t} \n \t\t} \n\t\tsearchNeighbours(c_neighbours, N, i, j, neighType); \n  \n";
char countFunction [] = "int count(int** neighbours, string variable, string value, vector<vector<Cell>> &cells){ \n     int i = 0; \n     int x = neighbours[i][0]; \n     int y = neighbours[i][1]; \n     int found = 0; \n     while (found == false && i < MAX_NEIGH){  \n         if (x != -1){ \n             if(foundVariable(cells[x][y], variable).compare(value) == 0){ \n                 found ++; \n             } \n         } \n         x = neighbours[i][0]; \n         y = neighbours[i][1]; \n         i++; \n     } \n     return found; \n } \n";
char includes [] = "#include <GL/gl.h> \n #include <GL/glut.h> \n #include <stdio.h> \n #include <cstdlib> \n #include <stdlib.h> \n #include <time.h> \n #include <string.h> \n #include <iostream> \n #include <fstream> \n #include \"sim.h\" \n #include \"grid.h\" \n #include <vector> \n  \n using namespace std; \n using std::vector; \n  \n #define MAX_NEIGH  12 \n #define NO_CHANGE 0\n";
char infectFunction [] = "void Cell::infect(){ \n\tinfected = true; \n \n";

#define FF fflush(stdout);    // para forzar la impresion inmediata

int  yylex();
int  yyerror();
int  yywarning();
int  yyparse();
char *generateString();
char * toUpper(char aux[]);
void generateCellClass();
void generateFoundFunction();
char * generateFirstLine();
int foundType(int type);
void clean();

%}

%union {                      // El tipo de la pila tiene caracter dual
      int valor ;             // - valor numerico de un NUMBER
      char *cadena ;          // - para pasar los nombres de IDENTIFES
}


%token <cadena> BOOL  //nombres de variables
%token <cadena> CELLS
%token <cadena> COUNT
%token <cadena> CURRENTTICK
%token <cadena> CONTINUE
%token <cadena> DOUBLE
%token <cadena> EXTENDED
%token <cadena> FALSE
%token <cadena> GLOB
%token <cadena> IDENTIF        // Identificador=variable
%token <cadena> INT
%token <cadena> MOORE
%token <cadena> NEUMANN
%token <cadena> NGH
%token <valor>  NUMBER         // Todos los token tienen un tipo para la pila
%token <cadena> PROP
%token <cadena> RANDOM
%token <cadena> IF
%token <cadena> INIT
%token <cadena> ELSE
%token <cadena> CELL
%token <cadena> STRING
%token <cadena> TICKS
%token <cadena> TRUE
%token <cadena> AND
%token <cadena> OR
%token <cadena> EQ
%token <cadena> NEQ
%token <cadena> LE
%token <cadena> GE
%token <cadena> NORTH
%token <cadena> SOUTH
%token <cadena> WEST
%token <cadena> EAST
%token <cadena> NORTHEAST
%token <cadena> NORTHWEST
%token <cadena> SOUTHEAST
%token <cadena> SOUTHWEST
%token <cadena> NORTHP
%token <cadena> SOUTHP
%token <cadena> WESTP
%token <cadena> EASTP
%token <cadena> STRAIN
%token <cadena> NUM_STRAINS


%type  <cadena> program
%type  <cadena> header
%type  <cadena> neighbourhood
%type  <cadena> properties
%type  <cadena> declaration
%type  <cadena> boolValue 
%type  <cadena> intValue 
%type  <cadena> init 
%type  <cadena> doubleValue   
%type  <cadena> cellProperties
%type  <cadena> states
%type  <cadena> state
%type  <cadena> color
%type  <cadena> codeColor
%type  <cadena> rules
%type  <cadena> assignment 
%type  <cadena> initialAssigments 
%type  <cadena> expression
%type  <cadena> termino
%type  <cadena> operand 
%type  <cadena> position 
%type  <cadena> beginIf 
%type  <cadena> bodyIf 
%type  <cadena> codeIf
%type  <cadena> general
%type  <cadena> time
%type  <cadena> nCells
%type  <cadena> cell
%type  <cadena> nStrains
%type  <cadena> strains


%right '='                    // es la ultima operacion que se debe realizar
%left '+' '-'                 // menor orden de precedencia
%left '*' '/'                 // orden de precedencia intermedio
%left SIGNO_UNARIO            // mayor orden de precedencia

%%
                                          
program:                                    { Add("state", "int", CELL_T, "0", "0");
                                              Add("alive", "bool", CELL_T, "true", "true");
                                              Add("infected", "bool", CELL_T, "false", "false");
                                              Add("no_change", "none", STATE_T, " ", " "); 
                                            }
              general   cell  strains  init { size_t needed = snprintf(NULL, 0, "%s", $2) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "%s", $2);
                                              generateCellClass();
                                              generateFoundFunction();
                                              char aux[2048];
                                              sprintf(aux, "\n");

                                              nodeList *p = List; //Pointer
                                              while(p->next != NULL){
                                                  if(STRAIN_T == p->section){
                                                      char file[100];
                                                      sprintf(file, "ofstream %s(\"Data/DataStrain_%s.csv\");\n", p->name, p->name); 
                                                      strcat(aux, file);
                                                  }
                                                  p = p->next;
                                              }

                                              printf ("%s\n%s\n%s\nint nStates = %d;\n%s\n%s\n%s\n%s\n ", includes, define, aux, (counter+1), buffer, construct, foundFunction, countFunction); 
                                              
                                              printf("%s\n %s \n%s } \n %s", beginEvaluation, generateFirstLine(), $4, drawCell);
                                              
                                              free(buffer);
                                            }
                                  
                ;

/*------------------ propiedades globales ------------------*/
general:        header   properties         { size_t needed = snprintf(NULL, 0, "%s \n %s \n", $1, $2) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "%s \n %s \n", $1, $2);
                                              $$ = generateString(buffer);
                                              free(buffer);
                                            } 
                ;

/*------------------ header ------------------*/
header:         nCells neighbourhood  time nStrains {  size_t needed = snprintf(NULL, 0, "%s %s %s", $2, $3, $4) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf(buffer, "%s %s %s", $2, $3, $4);
                                                        $$ = generateString(buffer); 
                                                        free(buffer);
                                                    }
                ;

neighbourhood:   /*lambda*/                 {   size_t needed = snprintf(NULL, 0, "int neighType  = NEUMANN;\n") + 1;
                                                char  *buffer = malloc(needed);
                                                sprintf(buffer, "int neighType  = NEUMANN;\n");
                                                $$ = generateString(buffer);
                                                free(buffer);

                                            }

                | NGH NEUMANN               { neighborhoodType = NEUMANN_T; 
                                              size_t needed = snprintf(NULL, 0, "int neighType = %s;\n", toUpper($2)) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int neighType = %s;\n", toUpper($2));
                                              $$ = generateString(buffer);
                                              free(buffer);
                                            }

                | NGH MOORE                 { neighborhoodType = MOORE_T; 
                                              size_t needed = snprintf(NULL, 0, "int neighType = %s;\n", toUpper($2)) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int neighType = %s;\n", toUpper($2));
                                              $$ = generateString(buffer);
                                              free(buffer);
                                            }

                | NGH EXTENDED              { neighborhoodType = EXTENDED_T; 
                                              size_t needed = snprintf(NULL, 0, "int neighType = %s;\n", toUpper($2)) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int neighType = %s;\n", toUpper($2));
                                              $$ = generateString(buffer);
                                              free(buffer);
                                            }
                ;

nCells:         /*lambda*/                  { size_t needed = snprintf(NULL, 0,  "#define N 100\n") + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer,  "#define N 100\n");
                                              strcat ( define, buffer); 
                                              free(buffer);
                                            } 

                | CELLS NUMBER              { size_t needed = snprintf(NULL, 0,  "#define N %d\n", $2) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer,  "#define N %d\n", $2);
                                              strcat ( define, buffer); 
                                              free(buffer);
                                            }
                ;

nStrains:         /*lambda*/                { size_t needed = snprintf(NULL, 0, "int nStrain  = 1;\n") + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int nStrain  = 1;\n");
                                              $$ = generateString(buffer);
                                              free(buffer);
                                            } 

                | NUM_STRAINS NUMBER        { numStrains = $2;
                                              size_t needed = snprintf(NULL, 0, "int nStrain  = %d;\n", $2) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int nStrain  = %d;\n", $2);
                                              $$ = generateString(buffer);
                                              free(buffer);
                                            }
                ;

time:            /*lambda*/                 { size_t needed = snprintf(NULL, 0, "int days = 500;\n") + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int days = 500;\n");
                                              $$ = generateString(buffer);
                                              free(buffer);
                                            } 

                | TICKS NUMBER              { size_t needed = snprintf(NULL, 0, "int days = %d;\n", $2) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int days = %d;\n", $2);
                                              $$ = generateString(buffer);
                                              free(buffer);
                                            }
                ;

/*------------------ properties ------------------*/

properties:       GLOB  declaration ';'              {  size_t needed = snprintf(NULL, 0, "%s", $2) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf(buffer, "%s", $2);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                      }
                | GLOB  declaration ';' properties      { size_t needed = snprintf(NULL, 0, "%s %s", $2, $4) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf(buffer, "%s %s", $2, $4);
                                                          $$ = generateString(buffer);
                                                          free(buffer);
                                                        }
                ;

/*------------------ cell atributes ------------------*/ 

cell:           CELL   '(' ')' '{'       { section = CELL_T; }
                cellProperties          { section = STATE_T; }
                states '}'              {  }    
                ;

/*------------------ cellProperties ------------------*/

cellProperties:       declaration ';'                      { }
                    | declaration ';' cellProperties       { }
                    ;

/*------------------ states ------------------*/
// tengo que guardar los identificadores para introducirlos luego 


// comproacion de que el primer identif sea state
states:         IDENTIF IDENTIF color state   { if(strcmp($1, "state") != 0) {
                                                  yyerror();
                                                }
                                                if(Get($2) == NULL) { 
                                                  Add($2, "none", section, " ", " "); 
                                                  size_t needed = snprintf(NULL, 0, "%s", $2) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf(buffer, "%s", $2);
                                                  char aux[1024];
                                                  sprintf(aux, "#define %s %d\n", toUpper(buffer), counter);
                                                  strcat(define, aux);
                                                  // printf ("%s", define);
                                                  sprintf(drawCell, "void drawCell(vector<vector<Cell>> &cells){ \n for (int i = 0; i < N; i++){ \n for (int j = 0; j < N; j++){ \n switch (cells[i][j].state){ \n case NO_CHANGE: \n glColor3f(1.000000, 1.000000, 1.000000); \n break; \n case %s:\n glColor3f%s; \n break;\n %s } \n glRectd(i, j, i+1, j+1); \n }\n }\n  }\n ", toUpper(buffer), $3, $4); 
                                                  free(buffer);
                                                }
                                                else { yyerror("ERROR: Duplicate state"); exit(1);}
                                              }
                ;

state:          /*lambda*/                              { 
                                                          char  *buffer = malloc(2);
                                                          sprintf(buffer, " "); 
                                                          $$ = generateString(buffer); 
                                                          free(buffer);
                                                        }

                | IDENTIF IDENTIF color  state          { if(strcmp($1, "state") != 0) {
                                                              yyerror();
                                                          }
                                                          if(Get($2) == NULL) { 
                                                            Add($2, "int", section, "0", "0"); 

                                                            size_t needed = snprintf(NULL, 0, "%s", $2) + 1;
                                                            char  *aux1 = malloc(needed);
                                                            sprintf(aux1, "%s", $2);
                                                            
                                                            needed = snprintf(NULL, 0, "#define %s %d\n", toUpper(aux1), counter) + 1;
                                                            char  *aux2 = malloc(needed);
                                                            sprintf(aux2, "#define %s %d\n", toUpper(aux1), counter);
                                                            strcat(define, aux2);
                                                            counter++;

                                                            needed = snprintf(NULL, 0, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(aux1), $3, $4) + 1;
                                                            char  *buffer = malloc(needed);
                                                            sprintf(buffer, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(aux1), $3, $4);
                                                            $$ = generateString(buffer);
                                                            free(buffer);
                                                            free(aux1);
                                                            free(aux2);
                                                          }
                                                          else { yyerror("ERROR: duplicate variable"); exit(1);}
                                                       }
                ;

color:           '(' codeColor ',' codeColor ',' codeColor ')'         { size_t needed = snprintf(NULL, 0, "(%s,%s,%s)", $2, $4, $6) + 1;
                                                                          char  *buffer = malloc(needed);
                                                                          sprintf(buffer, "(%s,%s,%s)", $2, $4, $6);
                                                                          $$ = generateString(buffer);
                                                                          free(buffer);
                                                                        }
                ;

codeColor:       doubleValue                          { char *eptr;
                                                          size_t needed = snprintf(NULL, 0, "%s", $1) + 1;
                                                          char  *aux = malloc(needed);
                                                          sprintf(aux, " %s", $1);
                                                          double number = strtod(aux, &eptr);
                                                          free(aux);
                                                          needed = snprintf(NULL, 0, "%f", number) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf(buffer, "%f", number); 
                                                          if (number > 1.0) { 
                                                            yywarning("WARNING: rgb color component must be between 0 and 1. By default the value will be 1.0");
                                                            sprintf(buffer, "1.0");
                                                            $$ = generateString(buffer); 
                                                          }
                                                          else if (number < 0.0) { 
                                                            yywarning("WARNING: rgb color component must be between 0 and 1. By default the value will be 0.0");
                                                            sprintf(buffer, "0.0");
                                                            $$ = generateString(buffer); 
                                                          }
                                                          $$ = generateString(buffer); 
                                                          free(buffer);
                                                        }

/*----------------- Declaration of variables --------------*/

declaration:      BOOL IDENTIF '=' boolValue          { if(Get($2) == NULL) { //No existe una variable llamda con el valo que lleva IDENTIF
                                                          //Se añade la variable a la lista de variables identificando si es global o atributo de célula
                                                          Add($2, "bool", section, $4, $4);
                                                          size_t needed = snprintf(NULL, 0,  "%s %s = %s;\n", $1, $2, $4) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf (buffer, "%s %s = %s;\n", $1, $2, $4); //Traducción a C: bool identif = valor;
                                                          $$ = generateString(buffer);
                                                          free(buffer);
                                                          clean();
                                                        }
                                                        else { //Existe una variable on ese nombre
                                                          if(strcmp($2, "state") == 0 || strcmp($2, "alive") == 0 || strcmp($2, "infected") == 0){
                                                            yyerror("ERROR: it is not allowed to use a variable"); exit(1);
                                                          } else {
                                                            yyerror("ERROR: duplicate variable"); exit(1);
                                                          }
                                                        }
                                                        
                                                      }
                  | BOOL IDENTIF                     { if(Get($2) == NULL) { 
                                                        Add($2, "bool", section, "false", "false"); 
                                                        size_t needed = snprintf(NULL, 0,  "%s %s = false;\n", $1, $2) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "%s %s = false;\n", $1, $2);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp($2, "state") == 0 || strcmp($2, "alive") == 0 || strcmp($2, "infected") == 0){
                                                          yyerror("ERROR: it is not allowed to use a reserved variable"); exit(1);
                                                        } else {
                                                          yyerror("ERROR: duplicate variable"); exit(1);
                                                        }
                                                      }
                                                      
                                                    }

                | INT IDENTIF '=' intValue          { if(Get($2) == NULL) { 
                                                        Add($2, "int", section, $4, $4); 
                                                        size_t needed = snprintf(NULL, 0,   "%s %s = %s;\n", $1, $2, $4) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer,  "%s %s = %s;\n", $1, $2, $4);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp($2, "state") == 0 || strcmp($2, "alive") == 0 || strcmp($2, "infected") == 0){
                                                          yyerror("ERROR: it is not allowed to use a reserved variable"); exit(1);
                                                        } else {
                                                          yyerror("ERROR: duplicate variable"); exit(1);
                                                        }
                                                      }
                                                    }
                | INT IDENTIF                       { if(Get($2) == NULL) { 
                                                        Add($2, "int", section, "0", "0"); 
                                                        size_t needed = snprintf(NULL, 0,   "%s %s = 0;\n", $1, $2) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer,  "%s %s = 0;\n", $1, $2);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp($2, "state") == 0 || strcmp($2, "alive") == 0 || strcmp($2, "infected") == 0){
                                                          yyerror("ERROR: it is not allowed to use a reserved variable"); exit(1);
                                                        } else {
                                                          yyerror("ERROR: duplicate variable"); exit(1);
                                                        }
                                                      }
                                                    }

                | DOUBLE IDENTIF '=' doubleValue    { if(Get($2) == NULL) { 
                                                        Add($2, "double", section, $4, $4); 
                                                        size_t needed = snprintf(NULL, 0,   "%s %s = %s;\n", $1, $2, $4) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer,  "%s %s = %s;\n", $1, $2, $4);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp($2, "state") == 0 || strcmp($2, "alive") == 0 || strcmp($2, "infected") == 0){
                                                          yyerror("ERROR: it is not allowed to use a reserved variable"); exit(1);
                                                        } else {
                                                          yyerror("ERROR: duplicate variable"); exit(1);
                                                        }
                                                      }
                                                    }
                | DOUBLE IDENTIF                    { if(Get($2) == NULL) { 
                                                        Add($2, "double", section, "0.0", "0.0"); 
                                                        size_t needed = snprintf(NULL, 0,   "%s %s = 0.0;\n", $1, $2) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer,  "%s %s = 0.0;\n", $1, $2);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp($2, "state") == 0 || strcmp($2, "alive") == 0 || strcmp($2, "infected") == 0){
                                                          yyerror("ERROR: it is not allowed to use a reserved variable"); exit(1);
                                                        } else {
                                                          yyerror("ERROR: duplicate variable"); exit(1);
                                                        }
                                                      }
                                                    }                      
                ;

/*-------- Rules  --------*/ 
strains:            STRAIN IDENTIF '(' NUMBER ')' '{' rules '}'            {  size_t needed = snprintf(NULL, 0, "if(currentTick >= %d) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n ", $4, beginStrain, $7, $2, $2, $2) + 1;
                                                                              char  *buffer = malloc(needed);
                                                                              sprintf (buffer,  "if(currentTick >= %d) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n ", $4, beginStrain, $7, $2, $2, $2);
                                                                              $$ = generateString(buffer);
                                                                              free(buffer);
                                                                              if(Get($2) == NULL) { 
                                                                                Add($2, "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
                  | STRAIN IDENTIF '(' NUMBER ')' '{' rules '}'  strains   {  size_t needed = snprintf(NULL, 0, "if(currentTick >= %d) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n %s ", $4, beginStrain, $7, $2, $2, $2, $9) + 1;
                                                                              char  *buffer = malloc(needed);
                                                                              sprintf (buffer,  "if(currentTick >= %d) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n  } \n %s ", $4, beginStrain, $7, $2, $2, $2, $9);
                                                                              $$ = generateString(buffer);
                                                                              free(buffer);
                                                                              if(Get($2) == NULL) { 
                                                                                Add($2, "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
                  | STRAIN IDENTIF '('  ')' '{' rules '}'                  {  size_t needed = snprintf(NULL, 0, "if(currentTick >= 0) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n ", beginStrain, $6, $2, $2, $2) + 1;
                                                                              char  *buffer = malloc(needed);
                                                                              sprintf (buffer,  "if(currentTick >= 0) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n ", beginStrain, $6, $2, $2, $2);
                                                                              $$ = generateString(buffer);
                                                                              free(buffer);
                                                                              if(Get($2) == NULL) { 
                                                                                Add($2, "null", STRAIN_T, " ", " "); 
                                                                              } 
                                                                            }
                  | STRAIN IDENTIF '('  ')' '{' rules '}'  strains         {  size_t needed = snprintf(NULL, 0, "if(currentTick >= 0) {\n %s %s \n } for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n \n } \n %s ", beginStrain, $6, $2, $2, $2, $8) + 1;
                                                                              char  *buffer = malloc(needed);
                                                                              sprintf (buffer,  "if(currentTick >= 0) {\n %s %s \n } for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n \n } \n %s ", beginStrain, $6, $2, $2, $2, $8);
                                                                              $$ = generateString(buffer);
                                                                              free(buffer);
                                                                              if(Get($2) == NULL) { 
                                                                                Add($2, "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
                  ;


rules:            beginIf                       { size_t needed = snprintf(NULL, 0, "%s \n }", $1) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer,  "%s \n }", $1);
                                                  $$ = generateString(buffer);
                                                  free(buffer);
                                                }
                                                
                | beginIf rules                 { size_t needed = snprintf(NULL, 0, "%s \n %s", $1, $2) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer,  "%s \n %s", $1, $2);
                                                  $$ = generateString(buffer);
                                                  free(buffer);
                                                  }
                ;


beginIf:     IF '(' expression ')' '{' bodyIf                     { size_t needed = snprintf(NULL, 0, "if( %s ) {\n %s ", $3, $6) + 1;
                                                                    char  *buffer = malloc(needed);
                                                                    sprintf (buffer,  "if( %s ) {\n %s ", $3, $6);
                                                                    $$ = generateString(buffer);
                                                                    free(buffer);
                                                                    clean();
                                                                  } 
            ;

bodyIf:       codeIf '}'                                            { size_t needed = snprintf(NULL, 0, "%s \n}\n",$1) + 1;
                                                                      char  *buffer = malloc(needed);
                                                                      sprintf (buffer,  "%s \n}\n",$1);
                                                                      $$ = generateString(buffer);
                                                                      free(buffer);
                                                                      clean();
                                                                    }  

            | codeIf '}'  ELSE IF '(' expression ')' '{'  bodyIf     {  size_t needed = snprintf(NULL, 0, "%s \n} else if ( %s ) {\n %s", $1, $6, $9) + 1;
                                                                        char  *buffer = malloc(needed);
                                                                        sprintf (buffer,  "%s \n} else if ( %s ) {\n %s", $1, $6, $9);
                                                                        $$ = generateString(buffer);
                                                                        free(buffer);
                                                                        clean();
                                                                      } 
            
            | codeIf '}'  ELSE '{'  codeIf  '}'                       { size_t needed = snprintf(NULL, 0, "%s \n} else {\n %s \n}", $1, $5) + 1;
                                                                        char  *buffer = malloc(needed);
                                                                        sprintf (buffer,  "%s \n} else {\n %s \n}", $1, $5);
                                                                        $$ = generateString(buffer);
                                                                        free(buffer);
                                                                        clean();
                                                                      } 
            ;


            

codeIf:        /* lambda */                           {  $$ = generateString(" "); }

            | assignment codeIf                       { size_t needed = snprintf(NULL, 0, "%s \n %s", $1, $2) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "%s \n %s", $1, $2);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                      } 

            | beginIf codeIf                          { size_t needed = snprintf(NULL, 0, "%s \n %s", $1, $2) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "%s \n %s", $1, $2);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                      } 
            | CONTINUE ';'                            { $$ = generateString("continue;"); }
            ;

/*-------- Initial state -------*/
init:                                                 { section = INIT_T; 
                                                        hasState = 0;
                                                        clean();
                                                     }
            INIT '(' ')' '{' initialAssigments '}'    { if (hasState == 0) {
                                                          yyerror("ERROR: Init funcion doesn't have an assigment to the variable \"state\"");
                                                          exit(1);
                                                        } else {
                                                          size_t needed = snprintf(NULL, 0, "%s }", $6) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf (buffer, "%s }", $6);
                                                          strcat(infectFunction, buffer);
                                                          free(buffer);
                                                        }
                                                      }
            ;


initialAssigments:    /*lambda*/                      { $$ = generateString(" "); }

                    | assignment initialAssigments    { size_t needed = snprintf(NULL, 0, "%s \n %s \n", $1, $2) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "%s \n %s \n", $1, $2);
                                                        $$ = generateString(buffer);
                                                        free(buffer);
                                                      }
                    ;
/*-------- Assigning values ​​to variables --------*/
assignment:                                                  { clean(); }
                  IDENTIF '=' expression ';'                 { nodeList *p = Get($2);
                                                              if(p == NULL) { 
                                                                yyerror("ERROR: Variable  doesn't exist");
                                                                exit(1);
                                                              } else {
                                                                if(strcmp($2, "state")==0) { 
                                                                  hasState = 1; 
                                                                }
                                                                if (strcmp(p->type,"int") == 0 && foundType(INTEGER_T) == 1){
                                                                  yywarning("WARNING: Maybe you're assigning a wrong type to variable");
                                                                } else if (strcmp(p->type,"bool") == 0 && foundType(BOOLEAN_T == 1)){
                                                                  yywarning("WARNING: Maybe you're assigning a wrong type to variable");
                                                                } else if (strcmp(p->type,"double") && foundType(DOUBLE_T == 1)) {
                                                                  yywarning("WARNING: Maybe you're assigning a wrong type to variable");
                                                                } 
                                                                clean();
                                                                size_t needed = snprintf(NULL, 0, "cells[i][j].%s = %s; ", $2, $4) + 1;
                                                                char  *buffer = malloc(needed);
                                                                if(p->section == CELL_T){
                                                                  if (section != INIT_T ) {
                                                                    sprintf(buffer, "cells[i][j].%s = %s; ", $2, $4);
                                                                  } else {
                                                                    sprintf(buffer, "%s = %s; ", $2, $4);
                                                                  }
                                                                  $$ = generateString(buffer); 
                                                                } else if(p->section == GLOBAL_T) {
                                                                  // strcpy(p->actualValue, $4);
                                                                  sprintf(buffer, "%s = %s; ", $2, $4);
                                                                  $$ = generateString(buffer); 
                                                                }
                                                                free(buffer);
                                                              }
                                                            }
                ;

/*-------- Math expressions --------*/
expression:        operand                        {  } 
                | expression '+' expression       { size_t needed = snprintf(NULL, 0, "%s + %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s + %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer);
                                                  }

                | expression '-' expression       { size_t needed = snprintf(NULL, 0, "%s - %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s - %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer);
                                                  }

                | expression '*' expression       { size_t needed = snprintf(NULL, 0, "%s * %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s * %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression '/' expression       { size_t needed = snprintf(NULL, 0, "%s / %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s / %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression '%' expression       { size_t needed = snprintf(NULL, 0, "%s %% %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s %% %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression AND expression       { size_t needed = snprintf(NULL, 0, "%s && %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s && %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression OR  expression       { size_t needed = snprintf(NULL, 0, "%s || %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s || %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression NEQ expression       { size_t needed = snprintf(NULL, 0, "%s != %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s != %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression EQ expression        { size_t needed = snprintf(NULL, 0, "%s == %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s == %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression '<' expression       { size_t needed = snprintf(NULL, 0, "%s < %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s < %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression LE expression        { size_t needed = snprintf(NULL, 0, "%s <= %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s <= %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression '>' expression       { size_t needed = snprintf(NULL, 0, "%s > %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s > %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | expression GE expression        { size_t needed = snprintf(NULL, 0, "%s >= %s", $1, $3) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s >= %s", $1, $3);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | '-' expression                  { size_t needed = snprintf(NULL, 0, "- %s", $2) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "- %s",$2);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                | '+' expression                  { size_t needed = snprintf(NULL, 0, "%s",$2) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s",$2);
                                                    $$ = generateString(buffer);
                                                    free(buffer); }

                ;
    
/*-------- Atomic operators --------*/
operand:        IDENTIF                             { nodeList *p = Get($1);
                                                      if(p == NULL) { 
                                                        if (strcmp($1, "currenttick") == 0) {
                                                          typeExpression[i] = INTEGER_T;
                                                          i++;
                                                          $$ = generateString("currentTick");
                                                        } else {
                                                          yyerror("ERROR: Variable  doesn't exist");
                                                          exit(1);
                                                        }
                                                      } else {
                                                        
                                                        if (strcmp(p->type, "int") == 0) {
                                                          typeExpression[i] = INTEGER_T;
                                                          i++;
                                                        } else if (strcmp(p->type, "bool") == 0) {
                                                          
                                                          typeExpression[i] = BOOLEAN_T;
                                                          i++;
                                                        } else if (strcmp(p->type, "double") == 0) {
                                                          typeExpression[i] = DOUBLE_T;
                                                          i++;
                                                        }
                                                        size_t needed = snprintf(NULL, 0, "cells[i][j].%s", $1) + 1;
                                                        char  *buffer = malloc(needed);
                                                        if(p->section == CELL_T){
                                                          sprintf(buffer, "cells[i][j].%s", $1);
                                                        } else if (p->section == GLOBAL_T){
                                                          sprintf(buffer, "%s", $1);
                                                        } else if (p->section == STATE_T){
                                                          sprintf(buffer, "%s", toUpper($1));
                                                        }
                                                        $$ = generateString(buffer);
                                                        free(buffer); 
                                                      }
                                                    }

                | RANDOM                            { typeExpression[i] = DOUBLE_T;
                                                      i++;
                                                      $$ = generateString("((rand() % (1001))/1000.0)"); }
                                                    
                | intValue                          { typeExpression[i] = INTEGER_T;
                                                      i++;
                                                      size_t needed = snprintf(NULL, 0, "%s", $1) + 1;
                                                      char  *buffer = malloc(needed);
                                                      sprintf (buffer, "%s", $1);
                                                      $$ = generateString(buffer);
                                                      free(buffer); }

                | doubleValue                       { typeExpression[i] = DOUBLE_T;
                                                      i++;
                                                      size_t needed = snprintf(NULL, 0, "%s", $1) + 1;
                                                      char  *buffer = malloc(needed);
                                                      sprintf (buffer, "%s", $1);
                                                      $$ = generateString(buffer);
                                                      free(buffer);  }

                | boolValue                         { typeExpression[i] = BOOLEAN_T;
                                                      i++;
                                                      size_t needed = snprintf(NULL, 0, "%s", $1) + 1;
                                                      char  *buffer = malloc(needed);
                                                      sprintf (buffer, "%s", $1);
                                                      $$ = generateString(buffer);
                                                      free(buffer);  }
                                                      
                // | NGH '.' IDENTIF                   { }

                | COUNT '(' IDENTIF ',' termino ')'     { if( Get($3)->section == CELL_T ) {
                                                            size_t needed = snprintf(NULL, 0, "count(c_neighbours, string(\"%s\"), std::to_string(%s), cells)", $3, $5) + 1;
                                                            char  *buffer = malloc(needed);
                                                            sprintf (buffer, "count(c_neighbours, string(\"%s\"), std::to_string(%s), cells)", $3, $5);
                                                            $$ = generateString(buffer);
                                                            free(buffer);  
                                                          } else {
                                                            yyerror("ERROR: Variable \"%s\" isn't an atribute of a cell type", $3);
                                                            exit(1);
                                                          }
                                                        }

                | NGH '(' position ')' '.' IDENTIF  { nodeList *p = Get($6);
                                                      if(p == NULL) { 
                                                       yyerror("ERROR: Variable  doesn't exist");
                                                        exit(1);
                                                      } else {
                                                        if(p->section == CELL_T){
                                                          if (strcmp(p->type, "int") == 0) {
                                                            typeExpression[i] = INTEGER_T;
                                                            i++;
                                                          } else if (strcmp(p->type, "bool") == 0) {
                                                            typeExpression[i] = BOOLEAN_T;
                                                            i++;
                                                          } else if (strcmp(p->type, "double") == 0) {
                                                            typeExpression[i] = DOUBLE_T;
                                                            i++;
                                                          }
                                                          size_t needed = snprintf(NULL, 0, "cells%s.%s", $3, $6) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf (buffer, "cells%s.%s", $3, $6);
                                                          $$ = generateString(buffer);
                                                          free(buffer);  
                                                        } else {
                                                          yyerror("ERROR: \"%s\" not a cell variable", $6);
                                                          exit(1);
                                                        }
                                                      } 
                                                    } // Añadir tambien lo de que al menos uno haga algo????
    
                | '(' expression ')'                 {  size_t needed = snprintf(NULL, 0, "( %s )", $2) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "( %s )", $2);
                                                        $$ = generateString(buffer);
                                                        free(buffer); }
                ;

/*-------- Values depend on the type of variable --------*/
boolValue:        TRUE                          { size_t needed = snprintf(NULL, 0, "%s", $1) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%s", $1);
                                                  $$ = generateString(buffer);
                                                  free(buffer); 
                                                }

                | FALSE                         { size_t needed = snprintf(NULL, 0, "%s", $1) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%s", $1);
                                                  $$ = generateString(buffer);
                                                  free(buffer); 
                                                }
                ;

intValue:         NUMBER                        { size_t needed = snprintf(NULL, 0, "%d", $1) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%d", $1);
                                                  $$ = generateString(buffer);
                                                  free(buffer); 
                                                } 
                  | '-' NUMBER                  { size_t needed = snprintf(NULL, 0, "-%d", $2) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "-%d", $2);
                                                  $$ = generateString(buffer);
                                                  free(buffer); 
                                                } 
                ;

doubleValue:    NUMBER '.' NUMBER             { size_t needed = snprintf(NULL, 0, "%d.%d", $1, $3) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%d.%d", $1, $3);
                                                  $$ = generateString(buffer);
                                                  free(buffer);  
                                                }

                | NUMBER                        { size_t needed = snprintf(NULL, 0, "%d.0", $1) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%d.0", $1);
                                                  $$ = generateString(buffer);
                                                  free(buffer);
                                                }
                | '-' NUMBER                  { size_t needed = snprintf(NULL, 0, "-%d.0", $2) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "-%d.0", $2);
                                                  $$ = generateString(buffer);
                                                  free(buffer); 
                                                } 
                | '-' NUMBER '.' NUMBER         { size_t needed = snprintf(NULL, 0, "-%d.%d", $2, $4) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "-%d.%d", $2, $4);
                                                  $$ = generateString(buffer);
                                                  free(buffer);  
                                                }
                ;


/*-------- Positions of neighborhood --------*/
position:         NORTH                             { $$ = generateString("[c_neighbours[1][0]][c_neighbours[1][1]]");}
                | SOUTH                             { $$ = generateString("[c_neighbours[5][0]][c_neighbours[5][1]]");}
                | WEST                              { $$ = generateString("[c_neighbours[7][0]][c_neighbours[7][1]]");}
                | EAST                              { $$ = generateString("[c_neighbours[3][0]][c_neighbours[3][1]]");}
                | NORTHEAST                         { if(neighborhoodType != NEUMANN_T) {
                                                        $$ = generateString("[c_neighbours[2][0]][c_neighbours[2][1]]");
                                                      } else {
                                                          yyerror("ERROR: position not allowed in this type of neighborhood");
                                                          exit(1);
                                                      }
                                                    }
                | NORTHWEST                         { if(neighborhoodType != NEUMANN_T) {
                                                        $$ = generateString("[c_neighbours[0][0]][c_neighbours[0][1]]");
                                                      } else {
                                                          yyerror("ERROR: position not allowed in this type of neighborhood");
                                                          exit(1);
                                                      }
                                                    }
                | SOUTHEAST                         { if(neighborhoodType != NEUMANN_T) {
                                                        $$ = generateString("[c_neighbours[4][0]][c_neighbours[4][1]]");
                                                      } else {
                                                          yyerror("ERROR: position not allowed in this type of neighborhood");
                                                          exit(1);
                                                      }
                                                    }
                | SOUTHWEST                         { if(neighborhoodType != NEUMANN_T) {
                                                        $$ = generateString("[c_neighbours[6][0]][c_neighbours[6][1]]");
                                                      } else {
                                                          yyerror("ERROR: position not allowed in this type of neighborhood");
                                                          exit(1);
                                                      }
                                                    }
                | NORTHP                            { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        $$ = generateString("[c_neighbours[8][0]][c_neighbours[8][1]]");
                                                      } else {
                                                          yyerror("ERROR: position not allowed in this type of neighborhood");
                                                          exit(1);
                                                      }
                                                    }
                | SOUTHP                            { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        $$ = generateString("[c_neighbours[10][0]][c_neighbours[10][1]]");
                                                      } else {
                                                          yyerror("ERROR: position not allowed in this type of neighborhood");
                                                          exit(1);
                                                      }
                                                    }
                | WESTP                             { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        $$ = generateString("[c_neighbours[11][0]][c_neighbours[11][1]]");
                                                      } else {
                                                          yyerror("ERROR: position not allowed in this type of neighborhood");
                                                          exit(1);
                                                      }
                                                    }
                | EASTP                             { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        $$ = generateString("[c_neighbours[9][0]][c_neighbours[9][1]]");
                                                      } else {
                                                          yyerror("ERROR: position not allowed in this type of neighborhood");
                                                          exit(1);
                                                      }
                                                    }

    
%%    
                                // SECCION 4    Codigo en C
int n_line = 1 ;

int yyerror (message)
char *message ;
{ 
 
    fprintf (stderr, "\033[1;31m %s in line %d\033[0m\n", message, n_line) ;
    printf ( "\n") ;	// bye
    exit(1);
}

int yywarning (message)
char *message ;
{ 
 
    fprintf (stderr, "\033[1;33m %s in line %d\n\033[0m", message, n_line) ;
    // printf ( "\n") ;	// bye
    
}

char *miMalloc (int nbytes)       // n bytes reserved in dynamic memory
{
    char *p ;
    static long int nb = 0;        // quantify memory
    static int nv = 0 ;            // total memory requested

    p = malloc (nbytes) ;
    if (p == NULL) {
         fprintf (stderr, "No queda memoria para %d bytes mas\n", nbytes) ;
         fprintf (stderr, "Reservados %ld bytes en %d llamadas\n", nb, nv) ;
         exit (0) ;
    }
    nb += (long) nbytes ;
    nv++ ;

    return p ;
}


/***************************************************************************/
/**************************** Stop Words Section ***************************/
/***************************************************************************/

typedef struct sStopWords { // for the stop words of C
    char *name ;
    int token ;
} tStop ;

tStop stopWords [] = { // Stop words
    "bool",         BOOL,
    "cells",        CELLS,
    "count",        COUNT,
    "currentTick",  CURRENTTICK,
    "continue",     CONTINUE,
    "double",       DOUBLE,
    "extended",     EXTENDED,
    "false",        FALSE,
    "global",       GLOB,
    "int",          INT,
    "moore",        MOORE,
    "neumann",      NEUMANN,
    "ngh",          NGH,
    "prop",         PROP,
    "if",           IF,
    "init",         INIT,
    "else",         ELSE,
    "random",       RANDOM,
    "cell",         CELL,
    "strain",       STRAIN,
    "strains",      NUM_STRAINS,
    "ticks",        TICKS,
    "true",         TRUE,
    "&&",           AND,
    "||",           OR,
    "==",           EQ,
    "!=",           NEQ,
    "<=",           LE,
    ">=",           GE,
    "n",            NORTH,
    "s",            SOUTH,
    "w",            WEST,
    "e",            EAST,
    "ne",           NORTHEAST,
    "nw",           NORTHWEST,
    "se",           SOUTHEAST,
    "sw",           SOUTHWEST,
    "np",           NORTHP,
    "sp",           SOUTHP,
    "wp",           WESTP,
    "ep",           EASTP,
     NULL,          0               // End of table
} ;

tStop *searchStopWord (char *symbol_name)
{                                  // Search in the stop word table
    int i ;
    tStop *sim ;

    i = 0 ;
    sim = stopWords ;
    while (sim [i].name != NULL) {
           if (strcmp (sim [i].name, symbol_name) == 0) {
                                         // strcmp(a, b) return == 0 if a==b
                 return &(sim [i]) ;
             }
           i++ ;
    }

    return NULL ;
}

 
/***************************************************************************/
/************************* Lexicographical Analizer ************************/
/***************************************************************************/

char *generateString (char *name)     // copy the argument in a string 
{                                      
      char *p ;
      int l ;

      l = strlen (name)+1 ;
      p = (char *) miMalloc (l) ;
      strcpy (p, name) ;

      return p ;
}


int yylex (){
  int i ;
  unsigned char c ;
  unsigned char cc ;
  char ops_expandibles [] = "!<=>|%&+-/*" ;
  char cadena [256] ;
  tStop *symbol ;

  do {
    c = getchar () ;
  
    if (c == '/') {	// If the line contain / could be a comment 
      cc = getchar () ;
      if (cc != '/') {   // If the next char is / is a comment 
        ungetc (cc, stdin) ;
      } else { // ==> Comment, ignore the line
        c = getchar () ;	// ...
        while (c != '\n') {
            c = getchar () ;
        }
      }
    }
    
    if (c == '\n')
    n_line++ ;
  
  } while (c == ' ' || c == '\n' || c == 10 || c == 13 || c == '\t') ;

  if ((c >= '0' && c <= '9')) {
        ungetc (c, stdin) ;
        scanf ("%d", &yylval.valor) ;
        return NUMBER ;
  }

  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
    i = 0 ;
    while (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '_') && i < 255) {
      cadena [i++] = tolower (c) ;
      c = getchar () ;
    }
    cadena [i] = '\0' ;
    ungetc (c, stdin) ;

    yylval.cadena = generateString (cadena) ;
    symbol = searchStopWord (yylval.cadena) ;
    if (symbol == NULL) {    // isn't an stop word -> identif 
      return (IDENTIF) ;
    } else {
      return (symbol->token) ;
    }
  }

  if (strchr (ops_expandibles, c) != NULL) { // busca c en ops_expandibles
    cc = getchar () ;
    sprintf (cadena, "%c%c", (char) c, (char) cc) ;
    symbol = searchStopWord (cadena) ;
    if (symbol == NULL) {
      ungetc (cc, stdin) ;
      yylval.cadena = NULL ;
      return (c) ;
    } else {
      yylval.cadena = generateString (cadena) ; // aunque no se use
      return (symbol->token) ;
    }
  }

  if (c == EOF || c == 255 || c == 26) {
    return (0) ;
  }

  return c ;
}

char * toUpper(char aux[]){
    char *word;
    word = generateString(aux);
    // counter for the loop
    int i = 0;

    // word to convert to uppercase
    char chr; 

    // Loop
    while (word[i]) { 
        chr = word[i];
        word[i] = toupper(chr); 
        i++; 
    } 
    return word;
}



void generateCellClass(){
  char assignment[2048];
  sprintf(construct, "class Cell{ \n public: \n");
  sprintf(assignment, "Cell::Cell (){\n \n");

  nodeList *p = List; //Pointer
  while(p != NULL){
    if(p->section == CELL_T){
        strcat(construct, p->type);
        strcat(construct, " ");
        strcat(construct, p->name);
        strcat(construct, ";\n");

        strcat(assignment, p->name);
        strcat(assignment, " = ");
        strcat(assignment, p->defValue);
        strcat(assignment, ";\n");




    }
    p = p->next;
  }

  strcat(construct, " Cell(); \n void infect(); \n }; \n");
  strcat(assignment, "}\n  \n  ");


  strcat(construct, assignment);
  strcat(construct, infectFunction);
}

void generateFoundFunction() {
    char aux[1024];
    strcat(foundFunction, "string foundVariable(Cell c, string variable) { \n     char aux[100]; \n     string ret = \"\"; \n");
    
    nodeList *p = List; //Pointer
    while(p != NULL){ 
      if(p->section == CELL_T){
        if (strcmp(p->type, "int") == 0 || strcmp(p->type, "bool") == 0) {
          sprintf(aux, " if (variable.compare(\"%s\")==0) { \nsprintf(aux, \"%%d\", c.%s);\n}", p->name, p->name );
        } else if (strcmp(p->type, "double") == 0) {
          sprintf(aux, " if (variable.compare(\"%s\")==0) { \nsprintf(aux, \"%%f\", c.%s);\n}", p->name, p->name );
        }
        strcat(foundFunction, aux);
      }
      p = p->next;
    } 

    strcat(foundFunction, "\nret = aux; \nreturn ret; \n}");
  
}
// fprintf (stderr, "BBBBBB %s\n", Get("state")->name);

int foundType(int type){
  // int ret = 0;
  for(int j=0; j<100; j++){
    if ( type == INTEGER_T && typeExpression[j] == DOUBLE_T) {
      fprintf (stderr, "AAAAA %d\n", typeExpression[j]);
      return 1;
    } else if ( type == BOOLEAN_T && (typeExpression[j] == DOUBLE_T || typeExpression[j] == INTEGER_T)) {
      return 1;
    } else if ( (type == DOUBLE_T || type == INTEGER_T) && typeExpression[j] == BOOLEAN_T ) {
      return 1;
    }
  }
  return 0;
}

void clean(){
  for(int j=0; j<100; j++){
    typeExpression[j] = 0;
  }
  i = 0;
}


// To write the first line of the output files
char * generateFirstLine(){
  char  *line = malloc(2048);
  sprintf (line, " ");

  char  *aux = malloc(2048);
  sprintf (aux, " ");

  // char line[2048];
  sprintf(aux, " ");
  sprintf(line, " ");
  nodeList *p = List; //Pointer
  while(p->next != NULL){
        if( STATE_T == p->section){
          sprintf(aux, "%s", line);
          sprintf(line, ",%s", toUpper(p->name));
          strcat(line, aux);
        }
        p = p->next;
  }
  sprintf(aux, "%s\\n", line);
  sprintf(line, "currentTick");
  strcat(line, aux);

  size_t needed = snprintf(NULL, 0, "if (currentTick == 0){ \n MyFile << \"%s\";\n}\n", line) + 1;
  char  *writeFirstLine = malloc(needed*numStrains);
  sprintf(writeFirstLine, "if (currentTick == 0){ \n");
  p = List; //Pointer
  while(p->next != NULL){
        if( STRAIN_T == p->section){
          strcat(writeFirstLine, p->name);
          strcat(writeFirstLine, " << \"");
          strcat(writeFirstLine, line);
          strcat(writeFirstLine, "\";\n");
        }
        p = p->next;
  }
  strcat(writeFirstLine, "}\n");


  return writeFirstLine;
}

/*-----------Fuctions for the Linked List----------*/
// Add new nodes to the list
int Add(char *name, char *type, int section, char *defValue, char *actualValue)
{
    nodeList *p = List;    //Pointer

    //We chek if this node exists
    while(p != NULL){
        if(strcmp(name, p->name)==0 && strcmp(type, p->type)==0 && section == p->section){
            return 0; //Node already exists
        }
        p = p->next;
    }

    // Insert one node at the beginning of the list
    nodeList *newNode = (nodeList *)malloc(sizeof(nodeList));
    strcpy(newNode->name, name);
    strcpy(newNode->type, type);
    strcpy(newNode->defValue, defValue);
    strcpy(newNode->actualValue, actualValue);
    newNode->section = section;
    newNode->next = List;    
    List = newNode;
    return 1;  
}


// To check if one element is on the list
nodeList* Get(char *name)
{
    nodeList *p = List; //Pointer
    
    //Go throught the list searching the node
    while(p != NULL){
        if(strcmp(name, p->name)==0){
            return p;  
        }
        p = p->next;
    }
    return NULL;  // Node not found
}

// Delete one node with these atributes
int Destroy(char *name, char *type, int section) {

    if(List == NULL) return -1;    //The list is empty

    if(strcmp(List->type, type) == 0 && List->section == section && strcmp(List->name, name) == 0){   //If the first node is the node we are looking for, deleted
        nodeList *aux = List;
        List = List->next;
        aux->next = NULL;
        free(aux);
        return 1;
    }

    nodeList *p = List; //Pointer

    
    while(p->next != NULL){
        if(strcmp(name, p->name)==0 && strcmp(type, p->type)==0 && section == p->section){
            nodeList *aux=p->next;
            p->next=p->next->next;
            aux->next= NULL;
            free(aux);
            return 1;
        }
        p = p->next;
    }
    return -1;  //Node not found
}

int main ()
{
    yyparse () ;
}

