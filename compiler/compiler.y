%{                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()

int memoria [26] ;   	// Se define una zona de memoria para las variables 
char temp [2048] ;
char identif[2048] ;
int counter = 0;


#define FF fflush(stdout);    // para forzar la impresion inmediata

int yylex();
int yyerror();
int yyparse();
char *genera_cadena();
char * toUpper(char aux[]);
%}

%union {                      // El tipo de la pila tiene caracter dual
      int valor ;             // - valor numerico de un NUMERO
      char *cadena ;          // - para pasar los nombres de IDENTIFES
}


%token <cadena> BOOL  //nombres de variables
%token <cadena> CELLS
%token <cadena> DOUBLE
%token <cadena> EXTENDED
%token <cadena> FALSE
%token <cadena> GLOB
%token <cadena> IDENTIF        // Identificador=variable
%token <cadena> INT
%token <cadena> MOORE
%token <cadena> NEUMANN
%token <cadena> NGH
%token <valor>  NUMERO         // Todos los token tienen un tipo para la pila
%token <cadena> PROP
%token <cadena> STATE
%token <cadena> STRING
%token <cadena> TICKS
%token <cadena> TRUE


%type  <cadena> program header neighbourhood properties variable bool_value int_value double_value  cell_properties states color state code rules

%right '='                    // es la ultima operacion que se debe realizar
%left '+' '-'                 // menor orden de precedencia
%left '*' '/'                 // orden de precedencia intermedio
%left SIGNO_UNARIO            // mayor orden de precedencia

%%
                                          
program:                        { printf ("/*GLOBAL_PROPERTIES*/\n\n"); }
                general         { printf ("\n/*CELL_PROPERTIES*/\n\n"); }
                cell            { printf ("\n/*RULES*/\n\n"); }
                rules           { }
                ;

/*------------------ propiedades globales ------------------*/
general:        header   properties         { } 
                ;

/*------------------ header ------------------*/
header:         neighbourhood n_cells time { }
                ;

neighbourhood:   /*lambda*/                 {   sprintf (temp, "int neighType  = NEUMANN;\n");
                                                printf ("%s", temp); }
                | NGH NEUMANN               {   sprintf(temp, "%s", $2);
                                                sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                                printf ("%s", temp); }
                | NGH MOORE                 {   sprintf(temp, "%s", $2);
                                                sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                                printf ("%s", temp); }
                | NGH EXTENDED              {   sprintf(temp, "%s", $2);
                                                sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                                printf ("%s", temp); }
                ;
n_cells:         /*lambda*/                 {   sprintf (temp, "int n = 100;\n");
                                                printf ("%s", temp);  } 
                | CELLS NUMERO              {   sprintf (temp, "int n = %d;\n", $2);
                                                printf ("%s", temp);  }
                ;

time:            /*lambda*/                 {   sprintf (temp, "int days = 500;\n");
                                                printf ("%s", temp);} 
                | TICKS NUMERO              {   sprintf (temp, "int days = %d;\n", $2);
                                                printf ("%s", temp); }
                ;

/*------------------ properties ------------------*/

properties:     GLOB  variable                    { }
                | GLOB  variable  properties      { }
                ;

/*------------------ cell atributes ------------------*/ 

cell:           cell_properties         { } 
                states                  { }    
                ;

/*------------------ cell_properties ------------------*/

cell_properties:      PROP  variable                       { }
                    | PROP  variable  cell_properties      { }
                    ;

/*------------------ states ------------------*/
// tengo que guardar los identificadores para introducirlos luego 

states:         STATE IDENTIF color state            {      sprintf(temp, "%s", $2);
                                                            char aux[1024];
                                                            sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                            strcat(identif, aux);
                                                            printf ("%s", identif);
                                                            sprintf(temp, "void drawCell(Cell cells[N][N]){ \n for (int i = 0; i < N; i++){ \n for (int j = 0; j < N; j++){ \n switch (cells[i][j].state){ \n case %s:\n glColor3f%s; \n break;\n %s } \n glRectd(i, j, i+1, j+1); \n }\n }\n  }\n ", toUpper(temp), $3, $4); 
                                                            printf ("%s", temp);
                                                        }
                ;

state:          /*lambda*/                              {   sprintf(identif, "\n"); 
                                                            sprintf(temp, " "); 
                                                            $$ = genera_cadena (temp); }
                | STATE IDENTIF color  state            {   sprintf(temp, "%s", $2);
                                                            char aux[1024];
                                                            sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                            strcat(identif, aux);
                                                            counter++;
                                                            sprintf (temp, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(temp), $3, $4);
                                                            $$ = genera_cadena (temp);  }
                ;

color:           '(' code ',' code ',' code ')'   {     sprintf(temp, "(%s,%s,%s)", $2, $4, $6);
                                                        $$ = genera_cadena(temp);
                                                        }
                ;

code:        NUMERO '.' NUMERO                  {   char *eptr;
                                                    sprintf(temp, " %d.%d", $1, $3);
                                                    double number = strtod(temp, &eptr);
                                                    if (number > 255.0) { sprintf(temp, "255");}
                                                    else { sprintf(temp, "%f", number); }
                                                    $$ = genera_cadena (temp);
                                                }
            | NUMERO                            {   if($1 > 255) { sprintf(temp, "255"); } 
                                                    else { sprintf(temp, "%d", $1); }
                                                    $$ = genera_cadena (temp);
                                                }

/*----------------- variables --------------*/

variable:         BOOL IDENTIF bool_value       {  sprintf (temp, "%s %s %s\n", $1, $2, $3);
                                                   printf ("%s", temp);}
                | INT IDENTIF int_value         {  sprintf (temp, "%s %s %s\n", $1, $2, $3);
                                                   printf ("%s", temp); }
                | DOUBLE IDENTIF double_value   {  sprintf (temp, "%s %s %s\n", $1, $2, $3);
                                                   printf ("%s", temp); }
                ;

bool_value:      /*lambda*/                     {  sprintf (temp, "= false;");
                                                   $$ = genera_cadena (temp);} 
                | '=' TRUE                      {  sprintf (temp, "= %s;", $2);
                                                   $$ = genera_cadena (temp);}
                | '=' FALSE                     {  sprintf (temp, "= %s;", $2);
                                                   $$ = genera_cadena (temp);}
                ;

int_value:       /*lambda*/                     {  sprintf (temp, "= -1;");
                                                   $$ = genera_cadena (temp);} // -1 default 
                | '=' NUMERO                    {  sprintf (temp, "= %d;", $2);
                                                   $$ = genera_cadena (temp);} 
                ;

double_value:    /*lambda*/                     {  sprintf (temp, "= 0.0;");
                                                   $$ = genera_cadena (temp);} // 0.0 default 
                | '=' NUMERO '.' NUMERO         {  sprintf (temp, "= %d.%d;", $2, $4);
                                                   $$ = genera_cadena (temp);}
                | '=' NUMERO                    {  sprintf (temp, "= %d.0;", $2);
                                                   $$ = genera_cadena (temp);}
                ;
rules:          ;

%%
                            // SECCION 4    Codigo en C
int n_linea = 1 ;

int yyerror (mensaje)
char *mensaje ;
{
    fprintf (stderr, "%s en la linea %d\n", mensaje, n_linea) ;
    printf ( "\n") ;	// bye
}

char *mi_malloc (int nbytes)       // reserva n bytes de memoria dinamica
{
    char *p ;
    static long int nb = 0;        // sirven para contabilizar la memoria
    static int nv = 0 ;            // solicitada en total

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
/********************** Seccion de Palabras Reservadas *********************/
/***************************************************************************/

typedef struct s_pal_reservadas { // para las palabras reservadas de C
    char *nombre ;
    int token ;
} t_reservada ;

t_reservada pal_reservadas [] = { // define las palabras reservadas y los 
    "bool",         BOOL,
    "cells",        CELLS,
    "double",       DOUBLE,
    "extended",     EXTENDED,
    "false",        FALSE,
    "global",       GLOB,
    "int",          INT,
    "moore",        MOORE,
    "neumann",      NEUMANN,
    "ngh",          NGH,
    "prop",         PROP,
    "state",        STATE,
    "ticks",        TICKS,
    "true",         TRUE,
     NULL,          0               // para marcar el fin de la tabla
} ;

t_reservada *busca_pal_reservada (char *nombre_simbolo)
{                                  // Busca n_s en la tabla de pal. res.
                                   // y devuelve puntero a registro (simbolo)
    int i ;
    t_reservada *sim ;

    i = 0 ;
    sim = pal_reservadas ;
    while (sim [i].nombre != NULL) {
           if (strcmp (sim [i].nombre, nombre_simbolo) == 0) {
                                         // strcmp(a, b) devuelve == 0 si a==b
                 return &(sim [i]) ;
             }
           i++ ;
    }

    return NULL ;
}

 
/***************************************************************************/
/******************* Seccion del Analizador Lexicografico ******************/
/***************************************************************************/

char *genera_cadena (char *nombre)     // copia el argumento a un
{                                      // string en memoria dinamica
      char *p ;
      int l ;

      l = strlen (nombre)+1 ;
      p = (char *) mi_malloc (l) ;
      strcpy (p, nombre) ;

      return p ;
}


int yylex ()
{
    int i ;
    unsigned char c ;
    unsigned char cc ;
    char ops_expandibles [] = "!<=>|%&+-/*" ;
    char cadena [256] ;
    t_reservada *simbolo ;

    do {
    	c = getchar () ;

		if (c == '#') {	// Ignora las lineas que empiezan por #  (#define, #include)
			do {		//	OJO que puede funcionar mal si una linea contiene #
			 c = getchar () ;	
			} while (c != '\n') ;
		}
		
		if (c == '/') {	// Si la linea contiene un / puede ser inicio de comentario
			cc = getchar () ;
			if (cc != '/') {   // Si el siguiente char es /  es un comentario, pero...
				ungetc (cc, stdin) ;
		 } else {
		     c = getchar () ;	// ...
		     if (c == '@') {	// Si es la secuencia //@  ==> transcribimos la linea
		          do {		// Se trata de codigo inline (Codigo embebido en C)
		              c = getchar () ;
		              putchar (c) ;
		          } while (c != '\n') ;
		     } else {		// ==> comentario, ignorar la linea
		          while (c != '\n') {
		              c = getchar () ;
		          }
		     }
		 }
		}
		
		if (c == '\n')
		 n_linea++ ;
		
    } while (c == ' ' || c == '\n' || c == 10 || c == 13 || c == '\t') ;

    if (c == '\"') {
         i = 0 ;
         do {
             c = getchar () ;
             cadena [i++] = c ;
         } while (c != '\"' && i < 255) ;
         if (i == 256) {
              printf ("AVISO: string con mas de 255 caracteres en linea %d\n", n_linea) ;
         }		 	// habria que leer hasta el siguiente " , pero, y si falta?
         cadena [--i] = '\0' ;
         yylval.cadena = genera_cadena (cadena) ;
         return (STRING) ;
    }

    if ((c >= '0' && c <= '9')) {
         ungetc (c, stdin) ;
         scanf ("%d", &yylval.valor) ;
//         printf ("\nDEV: NUMERO %d\n", yylval.valor) ;        // PARA DEPURAR
         return NUMERO ;
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

         yylval.cadena = genera_cadena (cadena) ;
         simbolo = busca_pal_reservada (yylval.cadena) ;
         if (simbolo == NULL) {    // no es palabra reservada -> identificador 
//               printf ("\nDEV: IDENTIF %s\n", yylval.cadena) ;    // PARA DEPURAR
               return (IDENTIF) ;
         } else {
//               printf ("\nDEV: OTRO %s\n", yylval.cadena) ;       // PARA DEPURAR
               return (simbolo->token) ;
         }
    }

    if (strchr (ops_expandibles, c) != NULL) { // busca c en ops_expandibles
         cc = getchar () ;
         sprintf (cadena, "%c%c", (char) c, (char) cc) ;
         simbolo = busca_pal_reservada (cadena) ;
         if (simbolo == NULL) {
              ungetc (cc, stdin) ;
              yylval.cadena = NULL ;
              return (c) ;
         } else {
              yylval.cadena = genera_cadena (cadena) ; // aunque no se use
              return (simbolo->token) ;
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
    word = genera_cadena(aux);
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

int main ()
{
    yyparse () ;
}

