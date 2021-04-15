#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>


int* c1(int x, int y){ 
    static int r[2];
    r[0] = x-1;
    r[1] = y-1; 
    return r; 
};

int* c2(int x, int y){ 
    static int r[2];
    r[0] = x;
    r[1] = y-1; 
    return r; 
};

int* c3(int x, int y){ 
    static int r[2];
    r[0] = x+1;
    r[1] = y-1; 
    return r; 
};

int* c4(int x, int y){ 
    static int r[2];
    r[0] = x+1;
    r[1] = y; 
    return r; 
};

int* c5(int x, int y){ 
    static int r[2];
    r[0] = x+1;
    r[1] = y+1; 
    return r; 
};

int* c6(int x, int y){ 
    static int r[2];
    r[0] = x;
    r[1] = y+1; 
    return r; 
};

int* c7(int x, int y){ 
    static int r[2];
    r[0] = x-1;
    r[1] = y+1; 
    return r; 
};

int* c8(int x, int y){ 
    static int r[2];
    r[0] = x-1;
    r[1] = y; 
    return r; 
};



int** searchNeighbours(int** matrix, int n, int x, int y){

    // Case 1: Top left corner
    if (x == 0 && y == 0){
        cerr << "soy yo" << endl;
        // int** matrix = new int*[3];
        // for (int i = 0; i < 3; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c4(x, y)[0];
        matrix[0][1] = c4(x, y)[1];
        matrix[1][0] = c5(x, y)[0];
        matrix[1][1] = c5(x, y)[1];
        matrix[2][0] = c6(x, y)[0];
        matrix[2][1] = c6(x, y)[1];
        return matrix;
    }
    // Case 2: Top right corner
    else if (x == n-1 && y == 0){
        // int** matrix = new int*[3];
        // for (int i = 0; i < 3; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c6(x, y)[0];
        matrix[0][1] = c6(x, y)[1];
        matrix[1][0] = c7(x, y)[0];
        matrix[1][1] = c7(x, y)[1];
        matrix[2][0] = c8(x, y)[0];
        matrix[2][1] = c8(x, y)[1];

        return matrix;
    }
    //Case 3: Bottom right corner
    else if (x == n-1 && y == n-1){
        // int** matrix = new int*[3];
        // for (int i = 0; i < 3; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c1(x, y)[0];
        matrix[0][1] = c1(x, y)[1];
        matrix[1][0] = c2(x, y)[0];
        matrix[1][1] = c2(x, y)[1];
        matrix[2][0] = c8(x, y)[0];
        matrix[2][1] = c8(x, y)[1];

        return matrix;
    }

    //Case 4: Bottom left corner
    else if (x == 0 && y == n-1){
        // int** matrix = new int*[3];
        // for (int i = 0; i < 3; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c2(x, y)[0];
        matrix[0][1] = c2(x, y)[1];
        matrix[1][0] = c3(x, y)[0];
        matrix[1][1] = c3(x, y)[1];
        matrix[2][0] = c4(x, y)[0];
        matrix[2][1] = c4(x, y)[1];

        return matrix;
    }

    //Case 5: Top wall
    else if (x > 0 && x < n && y == 0){

        // int** matrix = new int*[5];
        // for (int i = 0; i < 5; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c4(x, y)[0];
        matrix[0][1] = c4(x, y)[1];
        matrix[1][0] = c5(x, y)[0];
        matrix[1][1] = c5(x, y)[1];
        matrix[2][0] = c6(x, y)[0];
        matrix[2][1] = c6(x, y)[1];
        matrix[3][0] = c7(x, y)[0];
        matrix[3][1] = c7(x, y)[1];
        matrix[4][0] = c8(x, y)[0];
        matrix[4][1] = c8(x, y)[1];

        return matrix;
    }

    //Case 6: Right wall
    else if (x == n-1 && y > 0 && y < n){

        // int** matrix = new int*[5];
        // for (int i = 0; i < 5; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c1(x, y)[0];
        matrix[0][1] = c1(x, y)[1];
        matrix[1][0] = c2(x, y)[0];
        matrix[1][1] = c2(x, y)[1];
        matrix[2][0] = c6(x, y)[0];
        matrix[2][1] = c6(x, y)[1];
        matrix[3][0] = c7(x, y)[0];
        matrix[3][1] = c7(x, y)[1];
        matrix[4][0] = c8(x, y)[0];
        matrix[4][1] = c8(x, y)[1];

        return matrix;
    }
    //Case 7: Bottom wall
    else if (x > 0 && x < n && y == n-1){
        // int** matrix = new int*[5];
        // for (int i = 0; i < 5; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c1(x, y)[0];
        matrix[0][1] = c1(x, y)[1];
        matrix[1][0] = c2(x, y)[0];
        matrix[1][1] = c2(x, y)[1];
        matrix[2][0] = c4(x, y)[0];
        matrix[2][1] = c4(x, y)[1];
        matrix[3][0] = c4(x, y)[0];
        matrix[3][1] = c4(x, y)[1];
        matrix[4][0] = c8(x, y)[0];
        matrix[4][1] = c8(x, y)[1];

        return matrix;
    }

    //Case 9: Left wall
    else if (x == 0 && y > 0 && y < n){
        // int** matrix = new int*[5];
        // for (int i = 0; i < 5; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c2(x, y)[0];
        matrix[0][1] = c2(x, y)[1];
        matrix[1][0] = c3(x, y)[0];
        matrix[1][1] = c3(x, y)[1];
        matrix[2][0] = c4(x, y)[0];
        matrix[2][1] = c4(x, y)[1];
        matrix[3][0] = c5(x, y)[0];
        matrix[3][1] = c5(x, y)[1];
        matrix[4][0] = c6(x, y)[0];
        matrix[4][1] = c6(x, y)[1];

        return matrix;
    }

    else{
        // int** matrix = new int*[5];
        // for (int i = 0; i < 5; ++i)
        //     matrix[i] = new int[2];

        matrix[0][0] = c1(x, y)[0];
        matrix[0][1] = c1(x, y)[1];
        matrix[1][0] = c2(x, y)[0];
        matrix[1][1] = c2(x, y)[1];
        matrix[2][0] = c3(x, y)[0];
        matrix[2][1] = c3(x, y)[1];
        matrix[3][0] = c4(x, y)[0];
        matrix[3][1] = c4(x, y)[1];
        matrix[4][0] = c5(x, y)[0];
        matrix[4][1] = c5(x, y)[1];
        matrix[5][0] = c6(x, y)[0];
        matrix[5][1] = c6(x, y)[1];
        matrix[6][0] = c7(x, y)[0];
        matrix[6][1] = c7(x, y)[1];
        matrix[7][0] = c8(x, y)[0];
        matrix[7][1] = c8(x, y)[1];

        return matrix;
    }

}