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
// Types of variables
#define GLOBAL_T        0
#define CELL_T          1
#define STATE_T         2
 
int  memoria [26];         	// Se define una zona de memoria para las variables 
char temp [2048];
char identif[2048];
int  counter = 0;
nodeList *List;              // Lista enlazada para almacenar variables
int neighborhood_type = NEUMANN_T;
int section = GLOBAL_T;

#define FF fflush(stdout);    // para forzar la impresion inmediata

int  yylex();
int  yyerror();
int  yyparse();
char *generate_string();
char * toUpper(char aux[]);

%}

%union {                      // El tipo de la pila tiene caracter dual
      int valor ;             // - valor numerico de un NUMBER
      char *cadena ;          // - para pasar los nombres de IDENTIFES
}


%token <cadena> BOOL  //nombres de variables
%token <cadena> CELLS
%token <cadena> CONDITION
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
%token <cadena> RULE
%token <cadena> STATE
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


%type  <cadena> program
%type  <cadena> header
%type  <cadena> neighbourhood
%type  <cadena> properties
%type  <cadena> variable
%type  <cadena> bool_value
%type  <cadena> int_value
%type  <cadena> double_value  
%type  <cadena> cell_properties
%type  <cadena> states
%type  <cadena> color
%type  <cadena> state
%type  <cadena> code
%type  <cadena> rule
%type  <cadena> rules
%type  <cadena> conditions
%type  <cadena> effects
%type  <cadena> expresion
%type  <cadena> termino
%type  <cadena> operando 
%type  <cadena> position 

%right '='                    // es la ultima operacion que se debe realizar
%left '+' '-'                 // menor orden de precedencia
%left '*' '/'                 // orden de precedencia intermedio
%left SIGNO_UNARIO            // mayor orden de precedencia

%%
                                          
program:                        { section = GLOBAL_T;  
                                  printf ("/*GLOBAL_PROPERTIES*/\n\n"); 
                                }
                general         { printf ("\n/*CELL_PROPERTIES*/\n\n"); }
                cell            { printf ("\n/*RULES*/\n\n"); }
                rules           { }
                ;

/*------------------ propiedades globales ------------------*/
general:        header   properties         { } 
                ;

/*------------------ header ------------------*/
header:         n_cells neighbourhood  time { }
                ;

neighbourhood:   /*lambda*/                 {   sprintf (temp, "int neighType  = NEUMANN;\n");
                                                printf ("%s", temp); }

                | NGH NEUMANN               { sprintf(temp, "%s", $2);
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              printf ("%s", temp); 
                                              neighborhood_type = NEUMANN_T; }

                | NGH MOORE                 { sprintf(temp, "%s", $2);
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              printf ("%s", temp); 
                                              neighborhood_type = MOORE_T; }

                | NGH EXTENDED              { sprintf(temp, "%s", $2);
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              printf ("%s", temp); 
                                              neighborhood_type = EXTENDED_T; }
                ;

n_cells:         /*lambda*/                 { sprintf (temp, "int n = 100;\n");
                                              printf ("%s", temp); } 

                | CELLS NUMBER              { sprintf (temp, "int n = %d;\n", $2);
                                              printf ("%s", temp); }
                ;

time:            /*lambda*/                 { sprintf (temp, "int days = 500;\n");
                                              printf ("%s", temp); } 

                | TICKS NUMBER              { sprintf (temp, "int days = %d;\n", $2);
                                              printf ("%s", temp); }
                ;

/*------------------ properties ------------------*/

properties:     GLOB  variable                    { }
                | GLOB  variable  properties      { }
                ;

/*------------------ cell atributes ------------------*/ 

cell:                                   { section = CELL_T; }
                cell_properties         { section = STATE_T; } 
                states                  { }    
                ;

/*------------------ cell_properties ------------------*/

cell_properties:      PROP  variable                       { }
                    | PROP  variable  cell_properties      { }
                    ;

/*------------------ states ------------------*/
// tengo que guardar los identificadores para introducirlos luego 

states:         STATE IDENTIF color state               { if(Get($2) == NULL) { Add($2, "none", section); }
                                                          else { yyerror("ERROR: Variable duplicada"); exit(1);}
                                                          sprintf(temp, "%s", $2);
                                                          char aux[1024];
                                                          sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                          strcat(identif, aux);
                                                          printf ("%s", identif);
                                                          sprintf(temp, "void drawCell(Cell cells[N][N]){ \n for (int i = 0; i < N; i++){ \n for (int j = 0; j < N; j++){ \n switch (cells[i][j].state){ \n case %s:\n glColor3f%s; \n break;\n %s } \n glRectd(i, j, i+1, j+1); \n }\n }\n  }\n ", toUpper(temp), $3, $4); 
                                                          printf ("%s", temp); }
                ;

state:          /*lambda*/                              { sprintf(identif, "\n"); 
                                                          sprintf(temp, " "); 
                                                          $$ = generate_string(temp); }

                | STATE IDENTIF color  state            { if(Get($2) == NULL) { Add($2, "none", section); }
                                                          else { yyerror("ERROR: Variable duplicada"); exit(1);}
                                                          sprintf(temp, "%s", $2);
                                                          char aux[1024];
                                                          sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                          strcat(identif, aux);
                                                          counter++;
                                                          sprintf (temp, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(temp), $3, $4);
                                                          $$ = generate_string(temp);  }
                ;

color:           '(' code ',' code ',' code ')'         { sprintf(temp, "(%s,%s,%s)", $2, $4, $6);
                                                          $$ = generate_string(temp); }
                ;

code:        NUMBER '.' NUMBER                          { char *eptr;
                                                          sprintf(temp, " %d.%d", $1, $3);
                                                          double number = strtod(temp, &eptr);
                                                          if (number > 255.0) { sprintf(temp, "255");}
                                                          else { sprintf(temp, "%f", number); }
                                                          $$ = generate_string(temp); }

            | NUMBER                                    { if($1 > 255) { sprintf(temp, "255"); } 
                                                          else { sprintf(temp, "%d", $1); }
                                                          $$ = generate_string(temp); }

/*----------------- variables --------------*/

variable:         BOOL IDENTIF '=' bool_value       { if(Get($2) == NULL) { Add($2, "bool", section); }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1);}
                                                      sprintf (temp, "%s %s = %s;\n", $1, $2, $4);
                                                      printf ("%s", temp); }

                | INT IDENTIF '=' int_value         { if(Get($2) == NULL) { Add($2, "bool", section); }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1); }
                                                      sprintf (temp, "%s %s = %s;\n", $1, $2, $4);
                                                      printf ("%s", temp); }

                | DOUBLE IDENTIF '=' double_value   { if(Get($2) == NULL) { Add($2, "bool", section); }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1); }
                                                      sprintf (temp, "%s %s = %s;\n", $1, $2, $4);
                                                      printf ("%s", temp); }
                ;

bool_value:      /*lambda*/                     {  sprintf (temp, "false");
                                                   $$ = generate_string(temp); } 

                | TRUE                          {  sprintf (temp, "%s", $1);
                                                   $$ = generate_string(temp); }

                | FALSE                         {  sprintf (temp, "%s", $1);
                                                   $$ = generate_string(temp); }
                ;

int_value:       /*lambda*/                     {  sprintf (temp, "-1");
                                                   $$ = generate_string(temp); } // -1 default 

                | NUMBER                        {  sprintf (temp, "%d", $1);
                                                   $$ = generate_string(temp); } 
                ;

double_value:    /*lambda*/                     {  sprintf (temp, "0.0");
                                                   $$ = generate_string(temp); } // 0.0 default

                | NUMBER '.' NUMBER             {  sprintf (temp, "%d.%d", $1, $3);
                                                   $$ = generate_string(temp); }

                | NUMBER                        {  sprintf (temp, "%d.0", $1);
                                                   $$ = generate_string(temp); }
                ;
rules:            rule                          { sprintf(temp, "%s \n", $1);
                                                printf ("%s", temp); }
                                                
                | rule rules                    { sprintf(temp, "%s \n %s", $1, $2);
                                                  printf ("%s", temp); }
                ;

rule:             RULE '{' CONDITION ':' conditions EFFECT ':'  effects '}'   { sprintf(temp, "\nif( %s ){ \n %s \n continue; \n }\n", $5, $8);
                                                                                $$ = generate_string(temp);
                                                                               }
                ;

conditions:       expresion                   { sprintf(temp, "%s", $1);
                                                $$ = generate_string(temp); }

                | expresion ';' conditions    { sprintf(temp, "%s && %s", $1, $3);
                                                $$ = generate_string(temp); }
                ;

effects:          IDENTIF '=' expresion                   { nodeList *p = Get($1);
                                                            if(p == NULL) { 
                                                              sprintf(temp, "ERROR: Variable %s doesn't exist", $1);          
                                                              yyerror(temp);
                                                              exit(1);
                                                            } else {
                                                              if(p->type2 == CELL_T){
                                                                sprintf(temp, "cells[i][j].%s = %s; ", $1, $3);
                                                                $$ = generate_string(temp); 
                                                              } else if(p->type2 == GLOBAL_T) {
                                                                sprintf(temp, "%s = %s; ", $1, $3);
                                                                $$ = generate_string(temp); 
                                                              }
                                                            }
                                                          }
                | IDENTIF '=' expresion ';' effects       { nodeList *p = Get($1);
                                                            if(p == NULL) { 
                                                              sprintf(temp, "ERROR: Variable %s doesn't exist", $1);          
                                                              yyerror(temp);
                                                              exit(1);
                                                            } else {
                                                              if(p->type2 == CELL_T){
                                                                sprintf(temp, "cells[i][j].%s = %s; \n %s", $1, $3, $5);
                                                                $$ = generate_string(temp); 
                                                              } else if(p->type2 == GLOBAL_T) {
                                                                sprintf(temp, "%s = %s; \n %s", $1, $3, $5);
                                                                $$ = generate_string(temp); 
                                                              }
                                                            }
                                                          }
                ;

expresion:        termino                       { } 
                | expresion '+' expresion       { sprintf(temp, "%s + %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion '-' expresion       { sprintf(temp, "%s - %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion '*' expresion       { sprintf(temp, "%s * %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion '/' expresion       { sprintf(temp, "%s / %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion '%' expresion       { sprintf(temp, "%s %% %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion AND expresion       { sprintf(temp, "%s && %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion OR  expresion       { sprintf(temp, "%s || %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion NEQ expresion       { sprintf(temp, "%s != %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion EQ expresion        { sprintf(temp, "%s == %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion '<' expresion       { sprintf(temp, "%s < %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion LE expresion        { sprintf(temp, "%s <= %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion '>' expresion       { sprintf(temp, "%s > %s", $1, $3);
                                                  $$ = generate_string(temp); }

                | expresion GE expresion        { sprintf(temp, "%s >= %s", $1, $3);
                                                  $$ = generate_string(temp); }

                ; 

// pendiente
termino:          operando                             { ; }
                // | '+' NUMBER %prec SIGNO_UNARIO     {sprintf (temp, " +%d", $2);
                //                                     $$ = generate_string(temp);}
    
                // | '-' NUMBER %prec SIGNO_UNARIO     {sprintf (temp, " -%d", $2);
                //                                     $$ = generate_string(temp);}
                ;
    
operando:        IDENTIF                            { nodeList *p = Get($1);
                                                      if(p == NULL) { 
                                                        sprintf(temp, "ERROR: Variable %s doesn't exist", $1);          
                                                        yyerror(temp);
                                                        exit(1);
                                                      } else {
                                                        if(p->type2 == CELL_T){
                                                          sprintf(temp, "cells[i][j].%s", $1);
                                                          $$ = generate_string(temp); 
                                                        } else if (p->type2 == GLOBAL_T){
                                                          sprintf(temp, "%s", $1);
                                                          $$ = generate_string(temp); 
                                                        } else if (p->type2 == STATE_T){
                                                          sprintf(temp, "%s", toUpper($1));
                                                          $$ = generate_string(temp);
                                                        }
                                                      }
                                                    }

                | RANDOM                            { sprintf(temp, "((rand() %% (1001))/1000.0)");
                                                      $$ = generate_string(temp); }
                                                    
                | int_value                         { sprintf(temp, "%s", $1);
                                                      $$ = generate_string(temp); }

                | double_value                      { sprintf(temp, "%s", $1);
                                                      $$ = generate_string(temp); }

                | bool_value                        { sprintf(temp, "%s", $1);
                                                      $$ = generate_string(temp); }
                                                      
                // | NGH '.' IDENTIF                   { }

                | NGH '(' position ')' '.' IDENTIF  { nodeList *p = Get($1);
                                                      if(p == NULL) { 
                                                        sprintf(temp, "ERROR: Variable %s doesn't exist", $1);          
                                                        yyerror(temp);
                                                        exit(1);
                                                      } else {
                                                        if(p->type2 == CELL_T){
                                                          sprintf(temp, "cells%s.%s", $3, $6);
                                                          $$ = generate_string(temp); 
                                                        } else {
                                                          sprintf(temp, "ERROR: %s not a cell variable", $6);          
                                                          yyerror(temp);
                                                          exit(1);
                                                        }
                                                      } 
                                                    } // Añadir tambien lo de que al menos uno haga algo????
    
                | '(' expresion ')'                 { sprintf(temp, "( %s )", $2);
                                                      $$ = generate_string(temp); }
                ;

position:         NORTH                             { sprintf(temp,"[c_neighbours[1][0]][c_neighbours[1][1]]");
                                                      $$ = generate_string(temp);}
                | SOUTH                             { sprintf(temp,"[c_neighbours[5][0]][c_neighbours[5][1]]");
                                                      $$ = generate_string(temp);}
                | WEST                              { sprintf(temp,"[c_neighbours[7][0]][c_neighbours[7][1]]");
                                                      $$ = generate_string(temp);}
                | EAST                              { sprintf(temp,"[c_neighbours[3][0]][c_neighbours[3][1]]");
                                                      $$ = generate_string(temp);}
                | NORTHEAST                         { if(neighborhood_type != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[2][0]][c_neighbours[2][1]]");
                                                        $$ = generate_string(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
                | NORTHWEST                         { if(neighborhood_type != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[0][0]][c_neighbours[0][1]]");
                                                        $$ = generate_string(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
                | SOUTHEAST                         { if(neighborhood_type != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[4][0]][c_neighbours[4][1]]");
                                                        $$ = generate_string(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
                | SOUTHWEST                         { if(neighborhood_type != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[6][0]][c_neighbours[6][1]]");
                                                        $$ = generate_string(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
                | NORTHP                            { if(neighborhood_type != NEUMANN_T && neighborhood_type != MOORE) {
                                                        sprintf(temp,"[c_neighbours[8][0]][c_neighbours[8][1]]");
                                                        $$ = generate_string(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
                | SOUTHP                            { if(neighborhood_type != NEUMANN_T && neighborhood_type != MOORE) {
                                                        sprintf(temp,"[c_neighbours[10][0]][c_neighbours[10][1]]");
                                                        $$ = generate_string(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
                | WESTP                             { if(neighborhood_type != NEUMANN_T && neighborhood_type != MOORE) {
                                                        sprintf(temp,"[c_neighbours[11][0]][c_neighbours[11][1]]");
                                                        $$ = generate_string(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
                | EASTP                             { if(neighborhood_type != NEUMANN_T && neighborhood_type != MOORE) {
                                                        sprintf(temp,"[c_neighbours[9][0]][c_neighbours[9][1]]");
                                                        $$ = generate_string(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", $1);          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }

    
%%    
                                // SECCION 4    Codigo en C
int n_line = 1 ;

int yyerror (message)
char *message ;
{ 
 
    fprintf (stderr, "\033[1;31m %s en la linea %d\n", message, n_line) ;
    printf ( "\n") ;	// bye
}

char *mi_malloc (int nbytes)       // n bytes reserved in dynamic memory
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

typedef struct s_stop_words { // for the stop words of C
    char *name ;
    int token ;
} t_stop ;

t_stop stop_words [] = { // Stop words
    "bool",         BOOL,
    "cells",        CELLS,
    "condition",    CONDITION,
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
    "rule",         RULE,
    "random",       RANDOM,
    "state",        STATE,
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

t_stop *search_stop_word (char *symbol_name)
{                                  // Search in the stop word table
    int i ;
    t_stop *sim ;

    i = 0 ;
    sim = stop_words ;
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

char *generate_string (char *name)     // copy the argument in a string 
{                                      
      char *p ;
      int l ;

      l = strlen (name)+1 ;
      p = (char *) mi_malloc (l) ;
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
    t_stop *symbol ;

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
         }		 	// habria que leer hasta el siguiente " , pero, y si falta?
         cadena [--i] = '\0' ;
         yylval.cadena = generate_string (cadena) ;
         return (STRING) ;
    }

    if ((c >= '0' && c <= '9')) {
         ungetc (c, stdin) ;
         scanf ("%d", &yylval.valor) ;
//         printf ("\nDEV: NUMBER %d\n", yylval.valor) ;        // PARA DEPURAR
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

         yylval.cadena = generate_string (cadena) ;
         symbol = search_stop_word (yylval.cadena) ;
         if (symbol == NULL) {    // isn't an stop word -> identif 
//               printf ("\nDEV: IDENTIF %s\n", yylval.cadena) ;    // PARA DEPURAR
               return (IDENTIF) ;
         } else {
//               printf ("\nDEV: OTRO %s\n", yylval.cadena) ;       // PARA DEPURAR
               return (symbol->token) ;
         }
    }

    if (strchr (ops_expandibles, c) != NULL) { // busca c en ops_expandibles
         cc = getchar () ;
         sprintf (cadena, "%c%c", (char) c, (char) cc) ;
         symbol = search_stop_word (cadena) ;
         if (symbol == NULL) {
              ungetc (cc, stdin) ;
              yylval.cadena = NULL ;
              return (c) ;
         } else {
              yylval.cadena = generate_string (cadena) ; // aunque no se use
              return (symbol->token) ;
         }
    }

//    printf ("\nDEV: LITERAL %d #%c#\n", (int) c, c) ;      // PARA DEPURAR
    if (c == EOF || c == 255 || c == 26) {
//         printf ("tEOF ") ;                                // PARA DEPURAR
         return (0) ;
    }

    return c ;
}

char * toUpper(char aux[]){
    char *word;
    word = generate_string(aux);
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

/*-----------Fuctions for the Linked List----------*/
// Add new nodes to the list
int Add(char *name, char *type, int type2)
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



