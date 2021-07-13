#include <pthread.h>

#define MAXSIZE 20


// Nodo utilizado para la lista enlazada

typedef struct node {
    char name[MAXSIZE];
    char type[MAXSIZE];  // This atribute determine if the variable is an int, boolean, double or string
    int  type2; // This atribute determine if the variable is global or is an atribute of the cells
    char defValue[MAXSIZE];
    char actualValue[MAXSIZE];
    struct node *next;
} nodeList;

//Funciones
int Add(char *name, char *type, int type2, char *defValue, char *actualValue );
nodeList* Get(char *name);
int Destroy(char *name, char *type, int type2);