
#include <pthread.h>


//Nodo utilizado para la lista enlazada
typedef struct node {
    int x;
    int y;
    // int *vector;
    // int Nelem;
    struct node *next;
} nodeList;

//Funciones
int Init(int x, int y);