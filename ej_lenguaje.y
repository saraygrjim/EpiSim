/*1-Saray Garcia de la Rosa Jimenez - Enrique Lozano Cebriano - 31*/
/*2-100383435@alumnos.uc3m.es - 100383437@alumnos.uc3m.es*/
%{                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()
#include <pthread.h>
#include "lista.h"

#define TRUE 1
#define FALSE 2


int memoria [26] ;   	// Se define una zona de memoria para las variables 
char temp [2048] ;

int i = 0;
int condicional = FALSE;            //Determina si una expresion es condicional o no
int contador= 1;                    //Para inicializar matrices a int a = {1, 2, 3}
int hayError = FALSE;               //Determina si hay errores 
int asignacion = TRUE;              //Determina si estamos tratando una asignación para conversion de logica a aritmetica

char pila [40][200];                //Array pila para conversion de aritmetica a logica    
char aux [200];                     //Array auxiliar para pasar datos a la pila

nodeList *Lista;                    //Lista enlazada para almacenar variables
char tipo_aux[MAXSIZE] = "global";  //Determina en que funcion estamos

/*-----------Funciones par array-pila-----------*/
//Insertamos al final de la pila
void insertarFinal(char *exp){
    strcpy(pila[i], exp);
    i++;
}

//Obtenemos el ultimo elemento de la pila
char * obtenerFinal(){
    char *ret=malloc(20);
    strcpy(ret, pila[i-1]);
    strcpy(pila[i-1], "");
    i--;
    return ret;
}


/*-----------Funciones par lista enlazada----------*/
//Función que añade nodos a la lista enlazada
int Add(char *nombre, char *tipo)
{
    nodeList *p = Lista;    //Puntero para recorrer la lista y comprobar si ya hay un nodo con el mismo nombre

    //Primero comprobamos si ese vector ya existe
    while(p != NULL){
        if(strcmp(nombre, p->name)==0 && strcmp(tipo, p->tipo)==0){
            return 0; //Nodo ya existente
        }
        p = p->next;
    }

    //Insertamos nodo al principio de la lista dandole el espacio necesario
    nodeList *nuevoNodo = (nodeList *)malloc(sizeof(nodeList));
    strcpy(nuevoNodo->name, nombre);
    strcpy(nuevoNodo->tipo, tipo);
    nuevoNodo->next = Lista;    
    Lista = nuevoNodo;
    return 1;  
}

//Funcion para comprobar si existe un elemento en la lista enlazada
int Get(char *nombre, char* tipo)
{
    nodeList *p = Lista;
    
    //Recorre la lista buscando dicho vector
    while(p != NULL){
        if(strcmp(nombre, p->name)==0 && strcmp(tipo, p->tipo)==0){
            return 0;  
        }
        p = p->next;
    }
    return -1;  //No se ha encontrado el vector
}

//Elimina un nodo de la lista enlazada con ese tipo
int Destroy(char *tipo) {

    if(Lista == NULL) return -1;    //La lista esta vacia

    if(strcmp(Lista->tipo, tipo) == 0){   //Si el primer elemento es el que buscamos lo borramos
        nodeList *aux = Lista;
        Lista = Lista->next;
        aux->next = NULL;
        free(aux);
        return 1;
    }

    nodeList *p = Lista;

    //Recorremos la lista hasta encontrar el vector a eliminar
    while(p->next != NULL){
        if(strcmp(tipo, p->next->tipo) == 0){
            nodeList *aux=p->next;
            p->next=p->next->next;
            aux->next= NULL;
            free(aux);
            return 1;
        }
        p = p->next;
    }
    return -1;  //No se ha encontrado el vector
}



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
%token <cadena> RETORNO
%token <cadena> FOR

%type  <cadena>  programa
%type  <cadena>  codigo
%type  <cadena>  operando
%type  <cadena>  expresion
%type  <cadena>  termino
%type  <cadena>  fun_main
%type  <cadena>  llam_funcion
%type  <cadena>  arg_llamada
%type  <cadena>  print imp
%type  <cadena>  asignacion
%type  <cadena>  declaracion
%type  <cadena>  asig
%type  <cadena>  multidec
%type  <cadena>  est_while
%type  <cadena>  est_if
%type  <cadena>  r_if
%type  <cadena>  funcion
%type  <cadena>  retorno
%type  <cadena>  arg_declaracion
%type  <cadena>  est_for
%type  <cadena>  vector
%type  <cadena>  tipo
%type  <cadena>  variable
%type  <cadena>  asig_v
%type  <cadena>  dimension
%type  <cadena>  dim_asig



%right '='                // es la ultima operacion que se debe realizar
%left OR                  // menor orden de precedencia
%left AND                 // orden de precedencia intermedio
%left EQ NEQ              // orden de precedencia intermedio
%left '<' '>' LE GE       // orden de precedencia intermedio
%left '+' '-'             // orden de precedencia intermedio
%left '*' '/' '%'         // orden de precedencia intermedio
%left SIGNO_UNARIO        // mayor orden de precedencia

%%
                                          // Seccion 3 Gramatica - Semantico
/*--------Estructura de un programa--------*/
programa:       declaracion                         {   if(hayError==FALSE){
                                                            sprintf(temp, "%s", $1);
                                                            printf("%s\n", temp);
                                                        }
                                                    } 
                funcion fun_main                    {   int a = 0;
                                                        while (a!=-1){
                                                            a = Destroy(tipo_aux);
                                                        }
                                                        if(hayError==TRUE){
                                                            printf("(quit)");
                                                            return -1;
                                                        }
                                                        
                                                    }                    
                ;

/*---------Declaracion de variables y vectores---------*/
declaracion:   /* lambda */                                     {strcpy(temp, "");
                                                                $$ = genera_cadena (temp);} 
               | INTEGER tipo multidec  ';' declaracion         {sprintf (temp, "%s%s\n%s", $2, $3, $5);
                                                                $$ = genera_cadena (temp);}
                ;

tipo:   variable                    {sprintf (temp, "%s", $1);
                                    $$ = genera_cadena (temp);}
        |vector                     {sprintf (temp, "%s", $1);
                                    $$ = genera_cadena (temp);}
        ;

             /*---------Variable---------*/
variable:   IDENTIF asig            {   if(Get($1, tipo_aux)==-1){
                                        Add($1, tipo_aux);
                                        }else{
                                            yyerror("Variable duplicada");
                                            hayError = TRUE;
                                        }
                                            sprintf (temp, "(setq %s %s)", $1, $2);
                                            $$ = genera_cadena (temp);
                                    }
            ;
            /*---------Vector---------*/
vector:     IDENTIF dimension  asig        {    if(Get($1, tipo_aux)==-1){
                                                    Add($1, tipo_aux);
                                                }else{
                                                    yyerror("Variable duplicada");
                                                    hayError = TRUE;
                                                }
                                                sprintf (temp, "(setq %s (make-array '(%s) :initial-element %s))", $1, $2, $3);
                                                    $$ = genera_cadena (temp);
                                            } 

            | IDENTIF '[' ']'  '=' '{' NUMERO asig_v '}'        {   if(Get($1, tipo_aux)==-1){
                                                                        Add($1, tipo_aux);
                                                                    }else{
                                                                        yyerror("Variable duplicada");
                                                                        hayError = TRUE;
                                                                    }
                                                                    sprintf (temp, "(setq %s (make-array '(%d) :initial-contents '(%d %s)))", $1, contador, $6, $7);
                                                                    $$ = genera_cadena (temp);
                                                                }
            ;  

            /*---------Dimesiones del vector---------*/
dimension: '[' NUMERO ']' dimension         {sprintf (temp, "%d %s", $2, $4);
                                            $$ = genera_cadena (temp);}
            | '[' NUMERO ']'                {sprintf (temp, "%d", $2);
                                               $$ = genera_cadena (temp);}
            ;                   

            /*---------inicializacion de los vectores de tipo a[]={1, 2, 3}---------*/
asig_v:     /* lambda */                    {sprintf (temp, "");
                                            $$ = genera_cadena (temp);}
            | ',' NUMERO asig_v             {sprintf (temp, " %d %s", $2, $3);
                                            $$ = genera_cadena (temp);
                                            contador++;}
            ;

            /*---------Asignación de valor a las variables---------*/
asig:       /* lambda */                    {sprintf (temp, "0");
                                            $$ = genera_cadena (temp);}
            |'=' '-' NUMERO                 {sprintf (temp, "-%d", $3);
                                            $$ = genera_cadena (temp);}
            |'=' '+' NUMERO                 {sprintf (temp, "+%d", $3);
                                            $$ = genera_cadena (temp);}
            |'='  NUMERO                    {sprintf (temp, "%d", $2);
                                            $$ = genera_cadena (temp);}
            ;

            /*---------Posible multideclaración---------*/
multidec:   /* lambda */                    {strcpy (temp, "");
                                            $$ = genera_cadena (temp);}
            |',' tipo multidec              {sprintf (temp, " %s %s", $2, $3);
                                            $$ = genera_cadena (temp);}
            ;

/*--------Declaración de la funcion main--------*/
fun_main:       MAIN                                    {strcpy(tipo_aux, "main");}
                '(' ')' '{' declaracion codigo'}'       {   sprintf (temp, "(defun main () \n%s%s)\n", $6, $7);
                                                            int a = 0;
                                                            while (a!=-1){
                                                                a = Destroy(tipo_aux);
                                                            }
                                                            strcpy(tipo_aux, "global");  
                                                            if(hayError==FALSE){
                                                                printf("%s\n", temp);
                                                            }
                                                        }                                 
                ;

/*--------Return de una funcion cualquiera--------*/
retorno:        RETORNO expresion ';'                   {   sprintf  (temp, "(return-from %s %s)\n", tipo_aux, $2);
                                                            $$ = genera_cadena (temp);
                                                        }
                ;

/*--------Declaración de una funcion cualquiera--------*/
funcion:          /* lambda */                                      {strcpy (temp, "");
                                                                    $$ = genera_cadena (temp);}
                | IDENTIF                                           {strcpy(tipo_aux, $1);}
                '(' arg_declaracion ')' '{' declaracion codigo'}'   {   sprintf (temp, "(defun %s (%s)\n%s%s)\n\n",  $1, $4, $7, $8);
                                                                        int a = 0;
                                                                        while (a!=-1){
                                                                            a = Destroy(tipo_aux);
                                                                        }
                                                                        strcpy(tipo_aux, "global");
                                                                        if(hayError==FALSE){
                                                                            printf("%s\n", temp);
                                                                        }
                                                                    }
                 funcion                                            { ; }
                ;
/*--------Argumentos de la declaración de una función--------*/
arg_declaracion:      /* lambda */                      {strcpy (temp, "");
                                                        $$ = genera_cadena (temp);}
                | INTEGER IDENTIF   arg_declaracion     {   if(Get($2, tipo_aux)==-1){
                                                                Add($2, tipo_aux);
                                                            }else{
                                                                yyerror("Variable duplicada");
                                                                hayError = TRUE;
                                                            }
                                                            sprintf  (temp, "%s %s" ,$2, $3);
                                                            $$ = genera_cadena (temp);
                                                        }
                |',' INTEGER IDENTIF  arg_declaracion   {   if(Get($3, tipo_aux)==-1){
                                                                Add($3, tipo_aux);
                                                            }else{
                                                                yyerror("Variable duplicada");
                                                                hayError = TRUE;
                                                            }
                                                            sprintf (temp, " %s %s", $3, $4);
                                                            $$ = genera_cadena (temp); 
                                                        }                                                      
                ;
/*--------Llamada a una función--------*/
llam_funcion:       IDENTIF '(' expresion arg_llamada ')'   {sprintf (temp, "(%s %s %s)", $1, $3, $4 );
                                                            $$ = genera_cadena (temp);}
                |   IDENTIF '('   ')'                       {sprintf (temp, "(%s )", $1 );
                                                            $$ = genera_cadena (temp);}
                ;

/*--------Argumentos para la llamada de una funcion--------*/
arg_llamada:      /* lambda */                      {strcpy (temp, ""); 
                                                    $$ = genera_cadena (temp);}
                |',' expresion arg_llamada          {sprintf (temp, "%s %s ", $2, $3);
                                                    $$ = genera_cadena (temp);}         
                ;

/*--------Codigo incluido dentro de una funcion o estructuras definidas como if, while o for--------*/
codigo:      /* lambda */                           {strcpy(temp, "");
                                                    $$ = genera_cadena (temp);}
            |print      ';'    codigo               {sprintf(temp, "\t%s\n%s", $1, $3);
                                                    $$ = genera_cadena (temp);} 
            |asignacion ';'     codigo              {sprintf(temp, "\t%s\n%s", $1, $3);
                                                    $$ = genera_cadena (temp);} 
            |est_while  codigo                      {sprintf(temp, "\t%s\n%s", $1, $2);
                                                    $$ = genera_cadena (temp);} 
            |est_if     codigo                      {sprintf(temp, "\t%s\n%s", $1, $2);
                                                    $$ = genera_cadena (temp);} 
            |est_for     codigo                     {sprintf(temp, "\t%s\n%s", $1, $2);
                                                    $$ = genera_cadena (temp);} 
            |llam_funcion   ';'   codigo            {sprintf(temp, "\t%s\n%s", $1, $3);
                                                    $$ = genera_cadena (temp);}  
            |retorno  codigo                        {sprintf(temp, "\t%s\n%s", $1, $2);
                                                    $$ = genera_cadena (temp);} 
            ;

/*--------Impresión de variables, vectores o cadenas de caracteres--------*/
print:   PRINTF '('  imp ')'            {sprintf (temp, "%s" ,$3);
                                        $$ = genera_cadena (temp);}
                                       
        | PUTS '(' STRING ')'           {sprintf (temp, "(print \"%s\")", $3);
                                        $$ = genera_cadena (temp);}
        ;

imp:      expresion                         {sprintf (temp, "(print %s)", $1);
                                            $$ = genera_cadena (temp);}
        | expresion ','   imp               {sprintf (temp, "(print %s) %s", $1, $3);
                                            $$ = genera_cadena (temp);}                            
        | STRING                            {strcpy (temp, ""); 
                                            $$ = genera_cadena (temp);}
        | STRING    ',' imp                 {sprintf (temp, "%s" ,$3);
                                            $$ = genera_cadena (temp);}
        ;

/*--------Asignación de valores--------*/
asignacion:  IDENTIF '='                                {   asignacion=TRUE; }
             expresion                                  {   if(Get($1, tipo_aux)==-1 && Get($1, "global")==-1){
                                                                yyerror("Uso de variable que no existe");
                                                                hayError = TRUE;
                                                            }
                                                            sprintf (temp, "(setq %s %s)", $1, $4);
                                                            $$ = genera_cadena (temp);
                                                            asignacion=FALSE;
                                                        }
                                                        
            | IDENTIF  dim_asig  '='                    {   asignacion=TRUE; }
              expresion                                 {   if(Get($1, tipo_aux)==-1 && Get($1, "global")==-1){
                                                                yyerror("Uso de variable que no existe");
                                                                hayError = TRUE;
                                                            }
                                                            sprintf (temp, "(setf (aref %s %s) %s )", $1, $2, $5);
                                                            $$ = genera_cadena (temp);
                                                            asignacion=FALSE;
                                                        }
            ;

dim_asig:  '[' expresion ']' dim_asig           {sprintf (temp, "%s %s", $2, $4);
                                                $$ = genera_cadena (temp);}
            |  '[' expresion ']'                {sprintf (temp, "%s", $2);
                                                $$ = genera_cadena (temp);}
            ;

/*--------Estructura while--------*/    
est_while:     WHILE '(' expresion ')' '{'              {   if(condicional==TRUE){
                                                                sprintf(aux, "%s", $3);
                                                                insertarFinal(aux);
                                                                condicional = FALSE;
                                                            }else{
                                                                sprintf(aux, "(/= 0 %s)", $3);
                                                                insertarFinal(aux);
                                                            }
                                                        }
                codigo '}'                              { sprintf (temp, "(loop while %s  do\n %s \n\t)", obtenerFinal(), $7);
                                                            $$ = genera_cadena (temp);
                                                        }
                ;

/*--------Estructura if--------*/
est_if:     IF '(' expresion ')' '{'                {   if(condicional==TRUE){
                                                            sprintf(aux, "%s", $3);
                                                            insertarFinal(aux);
                                                            condicional = FALSE;
                                                        }else{
                                                            sprintf(aux, "(/= 0 %s)", $3);
                                                            insertarFinal(aux);
                                                        }
                                                    }
            r_if                                    {   sprintf (temp, "(if %s \n %s", obtenerFinal(), $7);
                                                        $$ = genera_cadena (temp);
                                                    } 
            ;

r_if:       codigo '}'                          {   sprintf(temp, "%s \t)\n",$1);
                                                    $$ = genera_cadena (temp);
                                                }  
            |codigo '}'  ELSE '{'  codigo  '}'  {   sprintf(temp, "\t(progn \n %s \t)\n \t(progn \n %s \t)\n)", $1, $5);
                                                    $$ = genera_cadena (temp);
                                                } 
            ;

/*--------Estructura for--------*/
est_for:    FOR '(' asignacion ';' expresion ';'    {   if(condicional==TRUE){
                                                            sprintf(aux, "%s", $5);
                                                            insertarFinal(aux);
                                                            condicional = FALSE;
                                                        }else{
                                                            sprintf(aux, "(/= 0 %s)", $5);
                                                            insertarFinal(aux);
                                                        }
                                                    }
            asignacion ')' '{' codigo '}'           {  sprintf(temp, "%s\n\t(loop while %s do\n %s \t%s\n\t)", $3, obtenerFinal(), $11, $8);
                                                        $$ = genera_cadena (temp);
                                                    }                      
            ;

/*--------Operaciones--------*/

expresion:    termino                       { ; } 
            | expresion '+' expresion       {sprintf (temp, "(+ %s %s)", $1, $3);
                                            $$ = genera_cadena (temp);
                                            condicional=FALSE;}

            | expresion '-' expresion       {sprintf (temp, "(- %s %s)", $1, $3);
                                            $$ = genera_cadena (temp);
                                            condicional=FALSE;}

            | expresion '*' expresion       {sprintf (temp, "(* %s %s)", $1, $3);
                                            $$ = genera_cadena (temp);
                                            condicional=FALSE;}

            | expresion '/' expresion       {sprintf (temp, "(/ %s %s)",  $1, $3);
                                            $$ = genera_cadena (temp);
                                            condicional=FALSE;}

            | expresion '%' expresion       {sprintf (temp, "(mod %s %s)", $1, $3);
                                            $$ = genera_cadena (temp);
                                            condicional=FALSE;}

            | expresion   AND               {   if(condicional==TRUE){
                                                    sprintf(aux, "%s", $1);
                                                    insertarFinal(aux);
                                                    condicional = FALSE;
                                                }else{
                                                    sprintf(aux, "(/= 0 %s)", $1);
                                                    insertarFinal(aux);
                                                }
                                            }
              expresion                     {   if(condicional==TRUE){
                                                    if(asignacion==TRUE){
                                                        sprintf (temp, "(if (and %s %s) 1 0)", obtenerFinal(), $4);             
                                                    }
                                                    else{
                                                        sprintf (temp, "(and %s %s)", obtenerFinal(), $4);             
                                                    }  
                                                }else{
                                                    if(asignacion==TRUE){
                                                        sprintf (temp, "(if (and %s (/= 0 %s)) 1 0)", obtenerFinal(), $4);             
                                                    }
                                                    else{
                                                        sprintf (temp, "(and %s (/= 0 %s))", obtenerFinal(), $4);  
                                                    }  
                                                    condicional=FALSE;
                                                }
                                                $$ = genera_cadena (temp);
                                            }
            | expresion  OR                 {   if(condicional==TRUE){
                                                    sprintf(aux, "%s", $1);
                                                    insertarFinal(aux);
                                                    condicional = FALSE;
                                                }else{
                                                    sprintf(aux, "(/= 0 %s)", $1);
                                                    insertarFinal(aux);
                                                }
                                            }
            
             expresion                      {   if(condicional==TRUE){
                                                    if(asignacion==TRUE){
                                                        sprintf (temp, "(if (or %s %s) 1 0)", obtenerFinal(), $4);             
                                                    }
                                                    else{
                                                        sprintf (temp, "(or %s %s)", obtenerFinal(), $4);             
                                                    }  
                                                }else{
                                                    if(asignacion==TRUE){
                                                        sprintf (temp, "(if (or %s (/= 0 %s)) 1 0)", obtenerFinal(), $4);             
                                                    }
                                                    else{
                                                        sprintf (temp, "(or %s (/= 0 %s))", obtenerFinal(), $4);  
                                                    }  
                                                    condicional=FALSE;
                                                }
                                                $$ = genera_cadena (temp);
                                            }
            | expresion NEQ expresion       {   if(asignacion==TRUE){
                                                    sprintf (temp, "(if (/= %s %s) 1 0)", $1, $3);
                                                }else{
                                                    sprintf (temp, "(/= %s %s)", $1, $3);
                                                    condicional=TRUE;
                                                } 
                                                $$ = genera_cadena (temp);

                                            }
                                            
            | expresion EQ expresion        {if(asignacion==TRUE){
                                                    sprintf (temp, "(if (= %s %s) 1 0)", $1, $3);
                                                }else{
                                                    sprintf (temp, "(= %s %s)", $1, $3);
                                                    condicional=TRUE;
                                                } 
                                                $$ = genera_cadena (temp);
                                            }
            | expresion '<' expresion       {if(asignacion==TRUE){
                                                    sprintf (temp, "(if (< %s %s) 1 0)", $1, $3);
                                                }else{
                                                    sprintf (temp, "(< %s %s)", $1, $3);
                                                    condicional=TRUE;
                                                } 
                                                $$ = genera_cadena (temp);
                                            }
            | expresion LE expresion         {if(asignacion==TRUE){
                                                    sprintf (temp, "(if (<= %s %s) 1 0)", $1, $3);
                                                }else{
                                                    sprintf (temp, "(<= %s %s)", $1, $3);
                                                    condicional=TRUE;
                                                } 
                                                $$ = genera_cadena (temp);
                                            }
            | expresion '>' expresion        {if(asignacion==TRUE){
                                                    sprintf (temp, "(if (> %s %s) 1 0)", $1, $3);
                                                }else{
                                                    sprintf (temp, "(> %s %s)", $1, $3);
                                                    condicional=TRUE;
                                                } 
                                                $$ = genera_cadena (temp);
                                            }
            | expresion GE expresion         {if(asignacion==TRUE){
                                                    sprintf (temp, "(if (>= %s %s) 1 0)", $1, $3);
                                                }else{
                                                    sprintf (temp, "(>= %s %s)", $1, $3);
                                                    condicional=TRUE;
                                                } 
                                                $$ = genera_cadena (temp);
                                            }
            ; 

termino:      operando                          { ; }
            | '+' NUMERO %prec SIGNO_UNARIO     {sprintf (temp, " +%d", $2);
                                                $$ = genera_cadena (temp);}

            | '-' NUMERO %prec SIGNO_UNARIO     {sprintf (temp, " -%d", $2);
                                                $$ = genera_cadena (temp);}
            ;

operando:    IDENTIF                    {   if(Get($1, tipo_aux)==-1 && Get($1, "global")==-1){
                                                yyerror("Uso de variable que no existe");
                                                hayError = TRUE;
                                            }
                                            sprintf (temp, " %s", $1);
                                            $$ = genera_cadena (temp);
                                            condicional=FALSE;
                                        }

            | NUMERO                    {sprintf (temp, " %d", $1);
                                        $$ = genera_cadena (temp);
                                        condicional=FALSE;}

            | '(' expresion ')'         {sprintf (temp, "%s",$2);
                                        $$ = genera_cadena (temp);}
            |  llam_funcion             {sprintf (temp, "%s" ,$1);
                                        $$ = genera_cadena (temp);
                                        condicional=FALSE;}  
            | IDENTIF dim_asig          {   if(Get($1, tipo_aux)==-1 && Get($1, "global")==-1){
                                                yyerror("Uso de variable que no existe");
                                                hayError = TRUE;
                                            }
                                            sprintf (temp, "(aref %s %s)", $1, $2);
                                            $$ = genera_cadena (temp);
                                            condicional=FALSE;    
                                        }
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
    "return",      RETORNO,
    "for",         FOR,
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

