#include <GL/glut.h>
#include <iostream>
#include "cell.cpp"

#define N     100
// Types of cell states
#define NO_CHANGE     0
#define NO_INFECTIOUS 1
#define INFECTED      2
#define RECOVER       3
#define QUARANTINE    4
#define DIE           5

// Types of neighborhood
#define MOORE         0
#define NEUMANN       1
#define EXTENDED      2

using namespace std;


int gridX, gridY;
// short sDirection = RIGHT;

int posX=20, posY=20;

void initGrid(int x, int y){
    gridX = x;
    gridY = y;
}

void unit(int x, int y){
    // if(x==0 || y==0 || x==gridX-1 || y==gridY-1){
    //     glLineWidth(3.0);
    //     glColor3f(1.0,0.0,0.0);
    // }else{
    glLineWidth(2.0);
    glColor3f(0.0,0.0,0.0);
    // }

    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

void drawGrid(){
    for(int x=0; x<gridX; x++){
        for (int y=0; y<gridY; y++){
            unit(x,y);
        }
    }
}

void drawCell(Cell cells[N][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){   
            switch (cells[i][j].state){
            case NO_CHANGE:
                glColor3f(1.0, 1.0, 1.0); //white
                break;
            case NO_INFECTIOUS:
                glColor3f(0.9804, 0.7765, 0.0); //yellow
                break;
            case INFECTED:
                glColor3f(0.8431, 0.0353, 0.1149); //red
                break;
            case RECOVER:
                glColor3f(0.0941, 0.5529, 0.251); //green
                break;
            case QUARANTINE:
                glColor3f(0.2039, 0.7333, 0.8549); //blue
                break;
            case DIE:
                glColor3f(0.0, 0.0, 0.0); //black
                break;
            }
            glRectd(i, j, i+1, j+1);
        }
    }
    // // for (int i=0; i<10; i++){
    //     if(a[i]<5){
    //         glColor3f(0.0, 1.0, 0.0);
    //     } else {
    //         glColor3f(0.0, 0.0, 1.0);
    //     }
    //     glRectd(i+1, 15, i+2, 15+1);
    // }
    // glColor3f(0.0, 1.0, 0.0);
    // glRectd(posX, posY, posX+1, posY+1);

}