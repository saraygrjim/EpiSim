/*1-Saray Garcia de la Rosa Jimenez - Enrique Lozano Cebriano - 31*/
/*2-100383435@alumnos.uc3m.es - 100383437@alumnos.uc3m.es*/
%{                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()
#include <pthread.h>


int memoria [26] ;   	// Se define una zona de memoria para las variables 
char temp [2048] ;

#define FF fflush(stdout);    // para forzar la impresion inmediata

int yylex();
int yyerror();
int yyparse();
char *genera_cadena();

%}

%token <valor>  NUMERO         // Todos los token tienen un tipo para la pila
%token <cadena> INTEGER       // identifica la definicion de un entero
%token <cadena> STRING
%token <cadena> DOUBLE
%token <cadena> NGH
%token <cadena> CELLS
%token <cadena> TICKS

%type  <cadena>  programa
%type  <cadena>  header
%type  <cadena>  neighbourhood
%type  <cadena>  n_cells
%type  <cadena>  time

// %right '='                // es la ultima operacion que se debe realizar
// %left OR                  // menor orden de precedencia
// %left AND                 // orden de precedencia intermedio
// %left EQ NEQ              // orden de precedencia intermedio
// %left '<' '>' LE GE       // orden de precedencia intermedio
// %left '+' '-'             // orden de precedencia intermedio
// %left '*' '/' '%'         // orden de precedencia intermedio
// %left SIGNO_UNARIO        // mayor orden de precedencia

%%
// Seccion 3 Gramatica - Semantico
/*--------Estructura de un programa--------*/
programa:       header                     { sprintf(temp, "%s fin", $1);
                                                 printf("%s\n", temp);} 
                // cell_properties         { } 
                // cell_states             { }
                // simulation_variables    { }   
                // rules                   { }                
                ; 

header:         neighbourhood  n_cells time       { sprintf(temp, "%s %s %s", $1, $2, $3);
                                                 printf("%s\n", temp);}
                
                ;

//Cambiar a palabras reservadas y cosas asi
neighbourhood:  /*lambda*/                {sprintf (temp, "ngh NEUMANN\n");
                                            $$ = genera_cadena (temp);  } //MOORE default
                | NGH 'NEUMANN'           {sprintf (temp, "%s %s\n", $1, $2);
                                           $$ = genera_csadena (temp);  }
                | NGH 'MOORE'             {sprintf (temp, "%s %s\n", $1, $2);
                                           $$ = genera_csadena (temp); }
                | NGH 'EXTENDED'          { sprintf (temp, "%s %s\n", $1, $2);
                                           $$ = genera_csadena (temp);}
                ;

n_cells:        /*lambda*/              { sprintf (temp, "cells 500\n");
                                        $$ = genera_cadena (temp);  } //500 default
                | CELLS NUMERO          { sprintf (temp, "%s %d\n", $1, $2);
                                        $$ = genera_cadena (temp); }
                ;

time:           /*lambda*/              { sprintf (temp, "ticks 500\n");
                                        $$ = genera_cadena (temp); } 
                | TICKS NUMERO          { sprintf (temp, "%s %d\n", $1, $2);
                                        $$ = genera_cadena (temp); }
                ;
%% 
                            // SECCION 4    Codigo en C
int n_linea = 1 ;

int yyerror (mensaje)
char *mensaje ;
{
    fprintf (stderr, "%s en la linea %d\n", mensaje, n_linea);
    printf ( "\n");	// bye
}

char *mi_malloc (int nbytes)       // reserva n bytes de memoria dinamica
{
    char *p ;
    static long int nb = 0;        // sirven para contabilizar la memoria
    static int nv = 0 ;            // solicitada en total

    p = malloc (nbytes);
    if (p == NULL) {
         fprintf (stderr, "No queda memoria para %d bytes mas\n", nbytes);
         fprintf (stderr, "Reservados %ld bytes en %d llamadas\n", nb, nv);
         exit (0);
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
    "int",         INTEGER,        // y los token asociados
    "double",      DOUBLE,
    "ngh",         NGH,
    "cells",       CELLS,
    "ticks",       TICKS,
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
                 return &(sim [i]);
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
      p = (char *) mi_malloc (l);
      strcpy (p, nombre);

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
    	c = getchar ();

		// if (c == '#') {	// Ignora las lineas que empiezan por #  (#define, #include)
		// 	do {		//	OJO que puede funcionar mal si una linea contiene #
		// 	 c = getchar ();	
		// 	} while (c != '\n');
		// }
		
		// if (c == '/') {	// Si la linea contiene un / puede ser inicio de comentario
		// 	cc = getchar ();
		// 	if (cc != '/') {   // Si el siguiente char es /  es un comentario, pero...
		// 		ungetc (cc, stdin);
		//  } else {
		//      c = getchar ();	// ...
		//      if (c == '@') {	// Si es la secuencia //@  ==> transcribimos la linea
		//           do {		// Se trata de codigo inline (Codigo embebido en C)
		//               c = getchar ();
		//               putchar (c);
		//           } while (c != '\n');
		//      } else {		// ==> comentario, ignorar la linea
		//           while (c != '\n') {
		//               c = getchar ();
		//           }
		//      }
		//  }
		}
		
		if (c == '\n')
		 n_linea++ ;
		
    } while (c == ' ' || c == '\n' || c == 10 || c == 13 || c == '\t');

    if (c == '\"') {
         i = 0 ;
         do {
             c = getchar ();
             cadena [i++] = c ;
         } while (c != '\"' && i < 255);
         if (i == 256) {
              printf ("AVISO: string con mas de 255 caracteres en linea %d\n", n_linea);
         }		 	// habria que leer hasta el siguiente " , pero, y si falta?
         cadena [--i] = '\0' ;
         yylval.cadena = genera_cadena (cadena);
         return (STRING);
    }

    if (c == '.' || (c >= '0' && c <= '9')) {
         ungetc (c, stdin);
         scanf ("%d", &yylval.valor);
//         printf ("\nDEV: NUMERO %d\n", yylval.valor);        // PARA DEPURAR
         return NUMERO ;
    }

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
         i = 0 ;
         while (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                 (c >= '0' && c <= '9') || c == '_') && i < 255) {
             cadena [i++] = tolower (c);
             c = getchar ();
         }
         cadena [i] = '\0' ;
         ungetc (c, stdin);

         yylval.cadena = genera_cadena (cadena);
         simbolo = busca_pal_reservada (yylval.cadena);
         if (simbolo == NULL) {    // no es palabra reservada -> identificador 
//               printf ("\nDEV: IDENTIF %s\n", yylval.cadena);    // PARA DEPURAR
               return (IDENTIF);
         } else {
//               printf ("\nDEV: OTRO %s\n", yylval.cadena);       // PARA DEPURAR
               return (simbolo->token);
         }
    }

    if (strchr (ops_expandibles, c) != NULL) { // busca c en ops_expandibles
         cc = getchar ();
         sprintf (cadena, "%c%c", (char) c, (char) cc);
         simbolo = busca_pal_reservada (cadena);
         if (simbolo == NULL) {
              ungetc (cc, stdin);
              yylval.cadena = NULL ;
              return (c);
         } else {
              yylval.cadena = genera_cadena (cadena); // aunque no se use
              return (simbolo->token);
         }
    }

//    printf ("\nDEV: LITERAL %d #%c#\n", (int) c, c);      // PARA DEPURAR
    if (c == EOF || c == 255 || c == 26) {
//         printf ("tEOF ");                                // PARA DEPURAR
         return (0);
    }

    return c ;
}


int main ()
{
    yyparse ();
}

