/*1-Saray Garcia de la Rosa Jimenez - Enrique Lozano Cebriano - 31*/
/*2-100383435@alumnos.uc3m.es - 100383437@alumnos.uc3m.es*/
%{                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()

int memoria [26] ;   	// Se define una zona de memoria para las variables 
char temp [2048] ;

#define FF fflush(stdout);    // para forzar la impresion inmediata

int yylex();
int yyerror();
int yyparse();
char *genera_cadena();

%}

%union {                      // El tipo de la pila tiene caracter dual
      int valor ;             // - valor numerico de un NUMERO
      char *cadena ;          // - para pasar los nombres de IDENTIFES
}

%token <valor>  NUMERO         // Todos los token tienen un tipo para la pila
%token <cadena> IDENTIF       // Identificador=variable
%token <cadena> INTEGER       // identifica la definicion de un entero
%token <cadena> STRING
%token <cadena> MAIN          // identifica el comienzo del proc. main
%token <cadena> WHILE         // identifica el bucle main
%token <cadena> PUTS           //identifica la palabra puts
%token <cadena> PRINTF          //identifica la palabra printf
%token <cadena> AND
%token <cadena> OR
%token <cadena> EQ
%token <cadena> NEQ
%token <cadena> LE
%token <cadena> GE
%token <cadena> IF
%token <cadena> ELSE

%type  <cadena> dec_var programa codigo operando expresion termino fun_main

%right '='                    // es la ultima operacion que se debe realizar
%left OR                    // menor orden de precedencia
%left AND                    // orden de precedencia intermedio
%left EQ NEQ               // orden de precedencia intermedio
%left '<' '>' LE GE       // orden de precedencia intermedio
%left '+' '-'                 // orden de precedencia intermedio
%left '*' '/'                 // orden de precedencia intermedio
%left SIGNO_UNARIO            // mayor orden de precedencia

%%
                                          // Seccion 3 Gramatica - Semantico
/*--------ESTRUCTURA DE UN PROGRAMA--------*/
programa:       dec_var funcion fun_main      {}                                                
;

/*--------DECLARACION DE VARIABLES FUERA DE LAS FUNCIONES--------*/
dec_var:    /* lambda */                    {printf ("\n");} 
            |c_dec_var  dec_var             {} 
;

/*---------DECLARACION DE VARIABLES---------*/
c_dec_var:  INTEGER IDENTIF                 {strcpy (temp, "");
                                            sprintf (temp, "(setq %s ", $2);
                                            printf ("%s", temp);}
            asig multidec ';'               {printf ("\n");}
;

asig:       /* lambda */                    {strcpy (temp, "");
                                            sprintf (temp, "0)");
                                            printf ("%s", temp);}
            |'=' NUMERO                     {strcpy (temp, "");
                                            sprintf (temp, "%d)", $2);
                                            printf ("%s", temp);}
;

multidec:    /* lambda */                   {}
            |',' IDENTIF                    {strcpy (temp, "");
                                            sprintf (temp, " (setq %s ", $2);
                                            printf ("%s", temp);}
            asig multidec                   
;


/*--------FUNCION MAIN--------*/
fun_main:       MAIN '(' ')' '{'            {strcpy (temp, ""); 
                                            sprintf (temp, "(defun main () \n" );
                                            printf ("%s\n", temp);}

                codigo '}'                  {strcpy (temp, "");
                                            sprintf (temp, ")\n" );
                                            printf ("%s\n", temp);}
                | MAIN '(' ')' '{'   '}'    {strcpy (temp, ""); 
                                            sprintf (temp, "(defun main () )\n" );
                                            printf ("%s\n", temp);}                                              
;

/*--------ESTRCTURA DE UNA FUNCION--------*/
funcion:      /* lambda */                {}
                | IDENTIF '(' ')' '{'       {strcpy (temp, ""); 
                                            sprintf (temp, "(defun " );
                                            strcat  (temp, $1);
                                            strcat  (temp, " ()\n");
                                            printf  ("%s\n", temp);}

                codigo '}'                  {strcpy (temp, "");
                                            sprintf (temp, ")\n" );
                                            printf  ("%s\n", temp);}
                funcion
                | IDENTIF '(' ')' '{'   '}' {strcpy (temp, ""); 
                                            sprintf (temp, "(defun " );
                                            strcat  (temp, $1);
                                            strcat  (temp, " () )\n");
                                            printf  ("%s\n", temp);} 
                funcion
;

/*--------CODIGO DENTRO DE UNA FUNCION--------*/
codigo:      print       r_codigo               {}
            |asignacion  r_codigo               {}
            |c_dec_var   r_codigo               {}
            |est_while   r_codigo               {}
            |est_if      r_codigo               {}
;

r_codigo:         /* lambda */                  {}
                | codigo                        {}
            ;

/*--------ESTRCTURA PRINT--------*/
print:   PRINTF '('  imp ')' ';'        {printf ("\n");}
                                       
        | PUTS '(' STRING ')' ';'       {strcpy (temp, ""); 
                                        strcat (temp, "(print \"");
                                        strcat (temp, $3);
                                        strcat (temp, "\")");
                                        printf ("%s\n", temp);}
;

imp:      expresion                     {strcpy (temp, ""); 
                                        strcat (temp, "(print ");
                                        strcat (temp, $1);
                                        strcat (temp, ") ");
                                        printf ("%s", temp);}
        | expresion ','                 {strcpy (temp, ""); 
                                        strcat (temp, "(print ");
                                        strcat (temp, $1);
                                        strcat (temp, ") ");
                                        printf ("%s", temp);}
          imp 
        | STRING                        {}
        | STRING    ',' imp             {}
;

/*--------ASIGNACION DE VALORES--------*/
asignacion:  IDENTIF '=' expresion  ';'     {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "setq ");
                                            strcat (temp, $1);
                                            strcat (temp, $3);
                                            strcat (temp, ")\n");
                                            printf("%s", temp);}
;

/*--------ESTRUCTURA WHILE--------*/
est_while:     WHILE '(' expresion ')' '{' {strcpy (temp, ""); 
                                            strcat (temp, "(loop while ");
                                            strcat (temp, $3);
                                            strcat(temp, " do\n");
                                            printf ("%s ", temp);}     

                codigo '}'                  {strcpy (temp, "");
                                            sprintf (temp, ")\n" ); 
                                            printf ("%s\n", temp);}
;

/*--------ESTRUCTURA IF--------*/
est_if:         IF '(' expresion ')' '{'    {strcpy (temp, ""); 
                                            strcat (temp, "(if ");
                                            strcat (temp, $3);
                                            strcat(temp, "\n");
                                            printf ("%s ", temp);}
                codigo      r_if            {strcpy (temp, "");
                                            sprintf (temp, "\n" ); 
                                            printf ("%s", temp);}
;

r_if:        '}'                            {strcpy (temp, ""); 
                                            sprintf (temp, ")\n"); 
                                            printf ("%s", temp);}  
            |'}'                            {strcpy (temp, ""); 
                                            printf ("%s", temp);}  
             ELSE '{'                       {strcpy (temp, ""); 
                                            strcat (temp, " ");
                                            strcat(temp, "");
                                            printf ("%s ", temp);}
             codigo  '}'                    {strcpy (temp, "");
                                            sprintf (temp, ")\n"); 
                                            printf ("%s", temp);}

 ;

/*--------OPERACIONES--------*/
expresion:    termino                       {}

            | expresion '+' expresion       {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "+");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}

            | expresion '-' expresion       {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "-");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}

            | expresion '*' expresion       {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "*");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}

            | expresion '/' expresion       {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "/");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            | expresion AND  expresion      {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "and");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            | expresion OR expresion        {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "or");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            | expresion NEQ expresion       {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "/=");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            | expresion EQ expresion        {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "=");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            | expresion '<' expresion       {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "<");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            | expresion LE expresion        {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, "<=");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            | expresion '>' expresion       {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, ">");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            | expresion GE expresion        {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                            strcat (temp, "(");
                                            strcat (temp, ">=");
                                            strcat (temp, $3);
                                            strcat (temp, $1);
                                            strcat (temp, ")");
                                            $$ = genera_cadena (temp);}
            ; 

termino:      operando                          {}
            | '+' NUMERO %prec SIGNO_UNARIO     {sprintf (temp, " +%d", $2);
                                                $$ = genera_cadena (temp);}

            | '-' NUMERO %prec SIGNO_UNARIO     {sprintf (temp, " -%d", $2);
                                                $$ = genera_cadena (temp);}
            ;

operando:     IDENTIF                   {sprintf (temp, " %s", $1);
                                        $$ = genera_cadena (temp);}

            | NUMERO                    {sprintf (temp, " %d", $1);
                                        $$ = genera_cadena (temp);}

            | '(' expresion ')'         {strcpy (temp, ""); // (+ expresion expresion ) 1+1 (+11)
                                        strcat (temp, $2);
                                        $$ = genera_cadena (temp);}
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
    "main",        MAIN,           // y los token asociados
    "int",         INTEGER,
    "puts",        PUTS,
    "printf",      PRINTF,
    "while",       WHILE,
    "&&",          AND,
    "||",          OR,
    "==",          EQ,
    "!=",          NEQ,
    "<=",          LE,
    ">=",          GE,
    "if",          IF,
    "else",        ELSE,
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

		if (c == '#') {	// Ignora las lineas que empiezan por #  (#define, #include)
			do {		//	OJO que puede funcionar mal si una linea contiene #
			 c = getchar ();	
			} while (c != '\n');
		}
		
		if (c == '/') {	// Si la linea contiene un / puede ser inicio de comentario
			cc = getchar ();
			if (cc != '/') {   // Si el siguiente char es /  es un comentario, pero...
				ungetc (cc, stdin);
		 } else {
		     c = getchar ();	// ...
		     if (c == '@') {	// Si es la secuencia //@  ==> transcribimos la linea
		          do {		// Se trata de codigo inline (Codigo embebido en C)
		              c = getchar ();
		              putchar (c);
		          } while (c != '\n');
		     } else {		// ==> comentario, ignorar la linea
		          while (c != '\n') {
		              c = getchar ();
		          }
		     }
		 }
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

