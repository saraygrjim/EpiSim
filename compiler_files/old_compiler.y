%{                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()
#include <pthread.h>
#include "lista.h"            // linked list

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
char* temp;
temp = (char*)malloc (2048);
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
int foundType(int type);
void clean();

%}

%union {                      // El tipo de la pila tiene caracter dual
      int valor ;             // - valor numerico de un NUMBER
      char *cadena ;          // - para pasar los nombres de IDENTIFES
}


%token <cadena> BOOL  //nombres de variables
%token <cadena> CELLS
%token <cadena> CONDITION
%token <cadena> COUNT
%token <cadena> CURRENTTICK
%token <cadena> CONTINUE
%token <cadena> DOUBLE
%token <cadena> EXTENDED
%token <cadena> EFFECT
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
%type  <cadena> code
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
              general   cell  strains  init { sprintf(temp, "%s", $2);
                                              generateCellClass();
                                              generateFoundFunction();
                                              char aux[2048];
                                              sprintf(aux, "\n");
                                              // for(int j=0; j<numStrains; j++){
                                              //   char file[100];
                                              //   sprintf(file, "ofstream MyFile(\"DataStrain%d.csv\");\n", j); //cambiar para poner nombre de la cepa
                                              //   strcat(aux, file);
                                              // }

                                              nodeList *p = List; //Pointer
                                              while(p->next != NULL){
                                                  if(STRAIN_T == p->type2){
                                                      char file[100];
                                                      sprintf(file, "ofstream %s(\"DataStrain%s.csv\");\n", p->name, p->name); 
                                                      strcat(aux, file);
                                                  }
                                                  p = p->next;
                                              }

                                              printf ("%s\n%s\n%s\nint nStates = %d;\n%s\n%s\n%s\n%s\n ", includes, define, aux, (counter+1), temp, construct, foundFunction, countFunction); 
                                              // sprintf(temp, "%s", $4);
                                              

                                              char line[2048];
                                              sprintf(aux, "\n");
                                              sprintf(line, "\n");
                                              nodeList *t = List; //Pointer
                                              while(t->next != NULL){
                                                   if( STATE_T == t->type2){
                                                      sprintf(aux, "%s", line);
                                                      sprintf(line, ";%s", toUpper(t->name));
                                                      strcat(line, aux);
                                                   }
                                                   t = t->next;
                                              }
                                              sprintf(aux, "%s", line);
                                              sprintf(line, "currentTick");
                                              strcat(line, aux);

                                              printf("%s\n %s } \n %s", beginEvaluation, $4, drawCell);
                                              // fprintf (stderr, "%s\n", line);
                                            }
                                  
                ;

/*------------------ propiedades globales ------------------*/
general:        header   properties         { sprintf(temp, "%s \n %s \n", $1, $2);
                                              $$ = generateString(temp);
                                            } 
                ;

/*------------------ header ------------------*/
header:         nCells neighbourhood  time nStrains {  sprintf(temp, "%s %s %s", $2, $3, $4);
                                                        $$ = generateString(temp); }
                ;

neighbourhood:   /*lambda*/                 {   sprintf (temp, "int neighType  = NEUMANN;\n");
                                                //printf ("%s", temp); 
                                                $$ = generateString(temp);
                                            }

                | NGH NEUMANN               { sprintf(temp, "%s", $2);
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              $$ = generateString(temp);
                                              neighborhoodType = NEUMANN_T; 
                                            }

                | NGH MOORE                 { sprintf(temp, "%s", $2);
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              $$ = generateString(temp);
                                              neighborhoodType = MOORE_T; 
                                            }

                | NGH EXTENDED              { sprintf(temp, "%s", $2);
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              $$ = generateString(temp);
                                              // printf ("%s", temp); 
                                              neighborhoodType = EXTENDED_T; 
                                            }
                ;

nCells:         /*lambda*/                  { sprintf (temp, "#define N 100\n");
                                              strcat ( define, temp); 
                                              // sprintf (temp, "");
                                              // $$ = generateString(temp);
                                            } 

                | CELLS NUMBER              { sprintf (temp, "#define N %d\n", $2);
                                              strcat ( define, temp); 
                                              // sprintf (temp, "");
                                              // $$ = generateString(temp);
                                            }
                ;

nStrains:         /*lambda*/                { sprintf (temp, "int nStrain  = 1;\n");
                                              $$ = generateString(temp);
                                            } 

                | NUM_STRAINS NUMBER        { sprintf (temp, "int nStrain  = %d;\n", $2);
                                              numStrains = $2;
                                              $$ = generateString(temp);
                                            }
                ;

time:            /*lambda*/                 { sprintf (temp, "int days = 500;\n");
                                              // printf ("%s", temp); 
                                              $$ = generateString(temp);
                                            } 

                | TICKS NUMBER              { sprintf (temp, "int days = %d;\n", $2);
                                              // printf ("%s", temp);
                                              $$ = generateString(temp);
                                            }
                ;

/*------------------ properties ------------------*/

properties:       GLOB  declaration ';'              {  sprintf (temp, "%s", $2);
                                                        $$ = generateString(temp);
                                                      }
                | GLOB  declaration ';' properties      {  sprintf (temp, "%s %s", $2, $4);
                                                        $$ = generateString(temp);
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
                                                  sprintf(temp, "%s", $2);
                                                  char aux[1024];
                                                  sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                  strcat(define, aux);
                                                  // printf ("%s", define);
                                                  sprintf(drawCell, "void drawCell(vector<vector<Cell>> &cells){ \n for (int i = 0; i < N; i++){ \n for (int j = 0; j < N; j++){ \n switch (cells[i][j].state){ \n case NO_CHANGE: \n glColor3f(1.000000, 1.000000, 1.000000); \n break; \n case %s:\n glColor3f%s; \n break;\n %s } \n glRectd(i, j, i+1, j+1); \n }\n }\n  }\n ", toUpper(temp), $3, $4); 
                                                  
                                                }
                                                else { yyerror("ERROR: Duplicate state"); exit(0);}
                                              }
                ;

state:          /*lambda*/                              { //sprintf(define, "\n"); 
                                                          sprintf(temp, " "); 
                                                          $$ = generateString(temp); }

                | IDENTIF IDENTIF color  state          { if(strcmp($1, "state") != 0) {
                                                              yyerror();
                                                          }
                                                          if(Get($2) == NULL) { 
                                                            Add($2, "int", section, "0", "0"); 
                                                            sprintf(temp, "%s", $2);
                                                            char aux[1024];
                                                            sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                            strcat(define, aux);
                                                            counter++;
                                                            sprintf (temp, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(temp), $3, $4);
                                                            $$ = generateString(temp); 
                                                          }
                                                          else { yyerror("ERROR: duplicate variable"); exit(0);}
                                                       }
                ;

color:           '(' code ',' code ',' code ')'         { sprintf(temp, "(%s,%s,%s)", $2, $4, $6);
                                                          $$ = generateString(temp); }
                ;

code:        NUMBER '.' NUMBER                          { char *eptr;
                                                          sprintf(temp, " %d.%d", $1, $3);
                                                          double number = strtod(temp, &eptr);
                                                          if (number > 1.0) { sprintf(temp, "1.0");}
                                                          else if (number < 0.0) { sprintf(temp, "0.0");}
                                                          else { sprintf(temp, "%f", number); }
                                                          $$ = generateString(temp); }

            | NUMBER                                    { if($1 > 1) { sprintf(temp, "1"); } 
                                                          else if ($1 < 0) { sprintf(temp, "0");}
                                                          else { sprintf(temp, "%d", $1); }
                                                          $$ = generateString(temp); }

/*----------------- Declaration of variables --------------*/

declaration:      BOOL IDENTIF '=' boolValue        { if(Get($2) == NULL) { 
                                                        Add($2, "bool", section, $4, $4); 
                                                        sprintf (temp, "%s %s = %s;\n", $1, $2, $4);
                                                        $$ = generateString(temp);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp($1, "state") == 0 || strcmp($1, "alive") == 0 || strcmp($1, "infected") == 0){
                                                          yyerror("ERROR: %s is a reserved variable", $1); exit(0);
                                                        } else {
                                                          yyerror("ERROR: duplicate variable"); exit(0);
                                                        }
                                                      }
                                                      
                                                    }

                | INT IDENTIF '=' intValue          { if(Get($2) == NULL) { 
                                                        Add($2, "int", section, $4, $4); 
                                                        sprintf (temp, "%s %s = %s;\n", $1, $2, $4);
                                                        $$ = generateString(temp);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp($1, "state") == 0 || strcmp($1, "alive") == 0 || strcmp($1, "infected") == 0){
                                                          yyerror("ERROR: %s is a reserved variable", $1); exit(0);
                                                        } else {
                                                          yyerror("ERROR:%s is a duplicate variable", $1); exit(0);
                                                        }
                                                      }
                                                    }

                | DOUBLE IDENTIF '=' doubleValue    { if(Get($2) == NULL) { 
                                                        Add($2, "double", section, $4, $4); 
                                                        sprintf (temp, "%s %s = %s;\n", $1, $2, $4);
                                                        $$ = generateString(temp);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp($1, "state") == 0 || strcmp($1, "alive") == 0 || strcmp($1, "infected") == 0){
                                                          yyerror("ERROR: %s is a reserved variable", $1); exit(0);
                                                        } else {
                                                          yyerror("ERROR:%s is a duplicate variable", $1); exit(0);
                                                        }
                                                      }
                                                    }
                ;

/*-------- Rules  --------*/ 
strains:            STRAIN IDENTIF '(' NUMBER ')' '{' rules '}'            {  sprintf(temp, " if(currentTick >= %d) {\n %s %s \n } \n } \n ", $4, beginStrain, $7);
                                                                              $$ = generateString(temp); 
                                                                              if(Get($2) == NULL) { 
                                                                                Add($2, "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
                  | STRAIN IDENTIF '(' NUMBER ')' '{' rules '}'  strains   {  sprintf(temp, " if(currentTick >= %d) {\n %s %s \n } \n } \n %s ", $4, beginStrain, $7, $9);
                                                                              $$ = generateString(temp); 
                                                                              if(Get($2) == NULL) { 
                                                                                Add($2, "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
                  | STRAIN IDENTIF '('  ')' '{' rules '}'                  { sprintf(temp, " if(currentTick >= 0) {\n %s %s \n } \n } \n ", beginStrain, $6);
                                                                              $$ = generateString(temp);
                                                                              if(Get($2) == NULL) { 
                                                                                Add($2, "null", STRAIN_T, " ", " "); 
                                                                              } 
                                                                            }
                  | STRAIN IDENTIF '('  ')' '{' rules '}'  strains         { sprintf(temp, " if(currentTick >= 0) {\n %s %s \n } \n } \n %s ", beginStrain, $6, $8);
                                                                              $$ = generateString(temp); 
                                                                              if(Get($2) == NULL) { 
                                                                                Add($2, "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
                  ;


rules:            beginIf                       { sprintf(temp, "%s \n }", $1);
                                                  $$ = generateString(temp); }
                                                
                | beginIf rules                 { sprintf(temp, "%s \n %s", $1, $2);
                                                  $$ = generateString(temp); }
                ;


beginIf:     IF '(' expression ')' '{' bodyIf                     { sprintf (temp, "if( %s ) {\n %s ", $3, $6);
                                                                    $$ = generateString(temp);
                                                                    clean();
                                                                  } 
            ;

bodyIf:       codeIf '}'                                            { sprintf(temp, "%s \n}\n",$1);
                                                                      $$ = generateString(temp);
                                                                      clean();
                                                                    }  

            | codeIf '}'  ELSE IF '(' expression ')' '{'  bodyIf     { sprintf(temp, "%s \n} else if ( %s ) {\n %s", $1, $6, $9);
                                                                        $$ = generateString(temp);
                                                                        clean();
                                                                      } 
            
            | codeIf '}'  ELSE '{'  codeIf  '}'                       { sprintf(temp, "%s \n} else {\n %s \n}", $1, $5);
                                                                        $$ = generateString(temp);
                                                                        clean();
                                                                      } 
            ;


            

codeIf:        /* lambda */                           {  sprintf(temp, " ");
                                                         $$ = generateString(temp);
                                                      }
            | assignment codeIf                       {  sprintf(temp, "%s \n %s", $1, $2);
                                                         $$ = generateString(temp);
                                                      } 

            | beginIf codeIf                          {  sprintf(temp, "%s \n %s", $1, $2);
                                                         $$ = generateString(temp);
                                                      } 
            | CONTINUE ';'                            { sprintf(temp, "continue;");
                                                        $$ = generateString(temp);
                                                      }
            ;

/*-------- Initial state -------*/
init:                                                 { section = INIT_T; 
                                                        hasState = 0;
                                                        clean();
                                                     }
            INIT '(' ')' '{' initialAssigments '}'    { if (hasState == 0) {
                                                          sprintf(temp, "ERROR: Init funcion doesn't have an assigment to the variable \"state\""); 
                                                          yyerror(temp);
                                                          exit(0);
                                                        } else {
                                                          sprintf(temp, "%s }", $6); 
                                                          strcat(infectFunction, temp);
                                                        }
                                                      }
            ;
initialAssigments:    /*lambda*/                      { sprintf(temp, " ");
                                                        $$ = generateString(temp);
                                                      }
                    | assignment initialAssigments    { sprintf(temp, "%s \n %s \n", $1, $2);
                                                      }
                    ;
/*-------- Assigning values ​​to variables --------*/
assignment:                                                  { clean(); }
                  IDENTIF '=' expression ';'                 { nodeList *p = Get($2);
                                                              if(p == NULL) { 
                                                                sprintf(temp, "ERROR: Variable \"%s\" doesn't exist", $2);          
                                                                yyerror(temp);
                                                                exit(0);
                                                              } else {
                                                                if(strcmp($2, "state")==0) { 
                                                                  hasState = 1; 
                                                                }
                                                                if (strcmp(p->type,"int") == 0 && foundType(INTEGER_T) == 1){
                                                                  sprintf(temp, "WARNING: Maybe you're assigning a wrong type to variable \"%s\"", $2);          
                                                                  yywarning(temp);
                                                                } else if (strcmp(p->type,"bool") == 0 && foundType(BOOLEAN_T == 1)){
                                                                  sprintf(temp, "WARNING: Maybe you're assigning a wrong type to variable \"%s\"", $2);  
                                                                  yywarning(temp);
                                                                } else if (strcmp(p->type,"double") && foundType(DOUBLE_T == 1)) {
                                                                  sprintf(temp, "WARNING: Maybe you're assigning a wrong type to variable \"%s\"", $2);          
                                                                  yywarning(temp);
                                                                } 
                                                                clean();
                                                                if(p->type2 == CELL_T){
                                                                  // strcpy(p->actualValue, $4);
                                                                  if (section != INIT_T ) {
                                                                    sprintf(temp, "cells[i][j].%s = %s; ", $2, $4);
                                                                  } else {
                                                                    sprintf(temp, "%s = %s; ", $2, $4);
                                                                  }
                                                                  $$ = generateString(temp); 
                                                                } else if(p->type2 == GLOBAL_T) {
                                                                  // strcpy(p->actualValue, $4);
                                                                  sprintf(temp, "%s = %s; ", $2, $4);
                                                                  $$ = generateString(temp); 
                                                                } 
                                                              }
                                                            }
                ;

/*-------- Math expressions --------*/
expression:        termino                        {  } 
                | expression '+' expression       { sprintf(temp, "%s + %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression '-' expression       { sprintf(temp, "%s - %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression '*' expression       { sprintf(temp, "%s * %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression '/' expression       { sprintf(temp, "%s / %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression '%' expression       { sprintf(temp, "%s %% %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression AND expression       { sprintf(temp, "%s && %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression OR  expression       { sprintf(temp, "%s || %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression NEQ expression       { sprintf(temp, "%s != %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression EQ expression        { sprintf(temp, "%s == %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression '<' expression       { sprintf(temp, "%s < %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression LE expression        { sprintf(temp, "%s <= %s", $1, $3);
                                                  $$ = generateString(temp); }

                | expression '>' expression       { sprintf(temp, "%s > %s", $1, $3);
                                                    $$ = generateString(temp); }

                | expression GE expression        { sprintf(temp, "%s >= %s", $1, $3);
                                                    $$ = generateString(temp); }

                | '-' expression                  { sprintf(temp, "- %s", $2);
                                                    $$ = generateString(temp); }

                | '+' expression                  { sprintf(temp, " %s", $2);
                                                    $$ = generateString(temp); }

                ; 

// pendiente
termino:          operand                           {  }
                // | '+' NUMBER                      { sprintf (temp, "+%d", $2);
                //                                      $$ = generateString(temp);
                //                                      typeExpression[i] = INTEGER_T;
                //                                      i++;
                //                                     }
    
                // | '-' NUMBER                      { sprintf (temp, "-%d", $2);
                //                                      $$ = generateString(temp);
                //                                      typeExpression[i] = INTEGER_T;
                //                                      i++;
                //                                     }
                ;
    
/*-------- Atomic operators --------*/
operand:        IDENTIF                             { nodeList *p = Get($1);
                                                      if(p == NULL) { 
                                                        if (strcmp($1, "currenttick") == 0) {
                                                          sprintf(temp, "currentTick");
                                                          typeExpression[i] = INTEGER_T;
                                                          i++;
                                                          $$ = generateString(temp);
                                                        } else {
                                                          sprintf(temp, "ERROR: Variable \"%s\" doesn't exist", $1);          
                                                          yyerror(temp);
                                                          exit(0);
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
                                                        if(p->type2 == CELL_T){
                                                          sprintf(temp, "cells[i][j].%s", $1);
                                                          $$ = generateString(temp); 
                                                        } else if (p->type2 == GLOBAL_T){
                                                          sprintf(temp, "%s", $1);
                                                          $$ = generateString(temp); 
                                                        } else if (p->type2 == STATE_T){
                                                          sprintf(temp, "%s", toUpper($1));
                                                          $$ = generateString(temp);
                                                        }
                                                      }
                                                    }
                | CURRENTTICK                       { sprintf(temp, "currentTick");
                                                      typeExpression[i] = INTEGER_T;
                                                      i++;
                                                      $$ = generateString(temp);
                                                    }

                | RANDOM                            { sprintf(temp, "((rand() %% (1001))/1000.0)");
                                                      typeExpression[i] = DOUBLE_T;
                                                      i++;
                                                      $$ = generateString(temp); }
                                                    
                | intValue                          { sprintf(temp, "%s", $1);
                                                      typeExpression[i] = INTEGER_T;
                                                      i++;
                                                      $$ = generateString(temp); }

                | doubleValue                       { sprintf(temp, "%s", $1);
                                                      typeExpression[i] = DOUBLE_T;
                                                      i++;
                                                      $$ = generateString(temp); }

                | boolValue                         { sprintf(temp, "%s", $1);
                                                      typeExpression[i] = BOOLEAN_T;
                                                      i++;
                                                      $$ = generateString(temp); }
                                                      
                // | NGH '.' IDENTIF                   { }

                | COUNT '(' IDENTIF ',' termino ')'     { if( Get($3)->type2 == CELL_T ) {
                                                            sprintf(temp, "count(c_neighbours, string(\"%s\"), std::to_string(%s), cells)", $3, $5); 
                                                            
                                                            $$ = generateString(temp);
                                                          } else {
                                                            sprintf(temp, "ERROR: Variable \"%s\" isn't an atribute of a cell type", $3);          
                                                            yyerror(temp);
                                                            exit(0);
                                                          }
                                                        }

                | NGH '(' position ')' '.' IDENTIF  { nodeList *p = Get($6);
                                                      if(p == NULL) { 
                                                        sprintf(temp, "ERROR: Variable \"%s\" doesn't exist", $6);          
                                                        yyerror(temp);
                                                        exit(0);
                                                      } else {
                                                        if(p->type2 == CELL_T){
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
                                                          sprintf(temp, "cells%s.%s", $3, $6);
                                                          $$ = generateString(temp); 
                                                        } else {
                                                          sprintf(temp, "ERROR: \"%s\" not a cell variable", $6);          
                                                          yyerror(temp);
                                                          exit(0);
                                                        }
                                                      } 
                                                    } // Añadir tambien lo de que al menos uno haga algo????
    
                | '(' expression ')'                 { sprintf(temp, "( %s )", $2);
                                                      $$ = generateString(temp); }
                ;

/*-------- Values depend on the type of variable --------*/
boolValue:       /*lambda*/                     {  sprintf (temp, "false");
                                                   $$ = generateString(temp); 
                                                } 
                                                  
                | TRUE                          {  sprintf (temp, "%s", $1);
                                                   $$ = generateString(temp); 
                                                }

                | FALSE                         {  sprintf (temp, "%s", $1);
                                                   $$ = generateString(temp); 
                                                }
                ;

intValue:        /*lambda*/                     {  sprintf (temp, "-1");
                                                   $$ = generateString(temp); 
                                                } // -1 default 

                | NUMBER                        {  sprintf (temp, "%d", $1);
                                                   $$ = generateString(temp); 
                                                } 
                ;

doubleValue:     /*lambda*/                     {  sprintf (temp, "0.0");
                                                   $$ = generateString(temp); 
                                                } // 0.0 default

                | NUMBER '.' NUMBER             {  sprintf (temp, "%d.%d", $1, $3);
                                                   $$ = generateString(temp); 
                                                }

                | NUMBER                        {  sprintf (temp, "%d.0", $1);
                                                   $$ = generateString(temp); 
                                                }
                ;


/*-------- Positions of neighborhood --------*/
position:         NORTH                             { sprintf(temp,"[c_neighbours[1][0]][c_neighbours[1][1]]");
                                                      $$ = generateString(temp);}
                | SOUTH                             { sprintf(temp,"[c_neighbours[5][0]][c_neighbours[5][1]]");
                                                      $$ = generateString(temp);}
                | WEST                              { sprintf(temp,"[c_neighbours[7][0]][c_neighbours[7][1]]");
                                                      $$ = generateString(temp);}
                | EAST                              { sprintf(temp,"[c_neighbours[3][0]][c_neighbours[3][1]]");
                                                      $$ = generateString(temp);}
                | NORTHEAST                         { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[2][0]][c_neighbours[2][1]]");
                                                        $$ = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: \"%s\" not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(0);
                                                      }
                                                    }
                | NORTHWEST                         { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[0][0]][c_neighbours[0][1]]");
                                                        $$ = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: \"%s\" not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(0);
                                                      }
                                                    }
                | SOUTHEAST                         { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[4][0]][c_neighbours[4][1]]");
                                                        $$ = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: \"%s\" not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(0);
                                                      }
                                                    }
                | SOUTHWEST                         { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[6][0]][c_neighbours[6][1]]");
                                                        $$ = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: \"%s\" not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(0);
                                                      }
                                                    }
                | NORTHP                            { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[8][0]][c_neighbours[8][1]]");
                                                        $$ = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: \"%s\" not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(0);
                                                      }
                                                    }
                | SOUTHP                            { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[10][0]][c_neighbours[10][1]]");
                                                        $$ = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: \"%s\" not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(0);
                                                      }
                                                    }
                | WESTP                             { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[11][0]][c_neighbours[11][1]]");
                                                        $$ = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: \"%s\" not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(0);
                                                      }
                                                    }
                | EASTP                             { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[9][0]][c_neighbours[9][1]]");
                                                        $$ = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: \"%s\" not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(0);
                                                      }
                                                    }

    
%%    
                                // SECCION 4    Codigo en C
int n_line = 1 ;

int yyerror (message)
char *message ;
{ 
 
    fprintf (stderr, "\033[1;31m %s in line %d\n", message, n_line) ;
    printf ( "\n") ;	// bye
}

int yywarning (message)
char *message ;
{ 
 
    fprintf (stderr, "\033[1;33m %s in line %d\n", message, n_line) ;
    printf ( "\n") ;	// bye
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
    "condition",    CONDITION,
    "count",        COUNT,
    "currentTick",  CURRENTTICK,
    "continue",     CONTINUE,
    "double",       DOUBLE,
    "effect",       EFFECT,
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
    "n+",           NORTHP,
    "s+",           SOUTHP,
    "w+",           WESTP,
    "e+",           EASTP,
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


int yylex ()
{
    int i ;
    unsigned char c ;
    unsigned char cc ;
    char ops_expandibles [] = "!<=>|%&+-/*" ;
    char cadena [256] ;
    tStop *symbol ;

    do {
    	c = getchar () ;

		if (c == '#') {	// Ignore the lines begin in #  (#define, #include)
			do {		//	OJO que puede funcionar mal si una linea contiene #
			 c = getchar () ;	
			} while (c != '\n') ;
		}
		
		if (c == '/') {	// If the line contain / could be a comment 
			cc = getchar () ;
			if (cc != '/') {   // If the next char is / is a comment 
				ungetc (cc, stdin) ;
		 } else {
		     c = getchar () ;	// ...
		     if (c == '@') {	// If is the sequence //@  ==> we transcribe the line
		          do {		// Inline code (Codigo embebido en C)
		              c = getchar () ;
		              putchar (c) ;
		          } while (c != '\n') ;
		     } else {		// ==> Comment, ignore the line
		          while (c != '\n') {
		              c = getchar () ;
		          }
		     }
		 }
		}
		
		if (c == '\n')
		 n_line++ ;
		
    } while (c == ' ' || c == '\n' || c == 10 || c == 13 || c == '\t') ;

    if (c == '\"') {
         i = 0 ;
         do {
             c = getchar () ;
             cadena [i++] = c ;
         } while (c != '\"' && i < 255) ;
         if (i == 256) {
              printf ("AVISO: string con mas de 255 caracteres en linea %d\n", n_line) ;
         }		 	
         cadena [--i] = '\0' ;
         yylval.cadena = generateString (cadena) ;
         return (STRING) ;
    }

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
    if(p->type2 == CELL_T){
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
      if(p->type2 == CELL_T){
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

/*-----------Fuctions for the Linked List----------*/
// Add new nodes to the list
int Add(char *name, char *type, int type2, char *defValue, char *actualValue)
{
    nodeList *p = List;    //Pointer

    //We chek if this node exists
    while(p != NULL){
        if(strcmp(name, p->name)==0 && strcmp(type, p->type)==0 && type2 == p->type2){
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
    newNode->type2 = type2;
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
int Destroy(char *name, char *type, int type2) {

    if(List == NULL) return -1;    //The list is empty

    if(strcmp(List->type, type) == 0 && List->type2 == type2 && strcmp(List->name, name) == 0){   //If the first node is the node we are looking for, deleted
        nodeList *aux = List;
        List = List->next;
        aux->next = NULL;
        free(aux);
        return 1;
    }

    nodeList *p = List; //Pointer

    
    while(p->next != NULL){
        if(strcmp(name, p->name)==0 && strcmp(type, p->type)==0 && type2 == p->type2){
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

