#include <stdio.h>
#include <math.h>
#include <pthread.h>


volatile int flag = 1;
int sudoku[9][9] = {{9,2,1,3,8,4,7,5,6},  // Example Input
                    {7,5,6,2,9,1,4,3,8},
                    {8,4,3,7,5,6,1,2,9},
                    {6,7,5,8,2,3,9,4,1},
                    {4,8,9,6,1,5,3,7,2},
                    {1,3,2,9,4,7,8,6,5},
                    {3,1,8,4,6,2,5,9,7},
                    {2,9,7,5,3,8,6,1,4},
                    {5,6,4,1,7,9,2,8,3}};

// Checks if a certain cell is valid
int checkValid(int sudoku[9][9], int lin, int col);

// Initiate a thread to work on 9 different cells
void* checkValidThr(void* v);


int main(void) {  
    pthread_t thr[9];
    for(int i = 0; i < 9; i++)
        pthread_create(&thr[i], NULL, checkValidThr, (void*) i);

    for(int i = 0; i < 9; i++)
        pthread_join(thr[i], NULL);
        
    if(flag == 1) {
        printf("Valid Solution\n");
    } else {
        printf("Invalid Solution\n");
    } 
}


void* checkValidThr(void* v) {
    int i = (int) v;
    // Checks Validity of [i][0,...,9] cells
    // sets global flag as 0 if any fails
    for(int j = 0; j < 9; j++)
        if(!checkValid(sudoku, i, j)){  
            flag = 0;
        }
    return NULL;
}


int checkValid(int sudoku[9][9], int lin, int col) {
    int n = sudoku[lin][col];
    if(n == 0)
        return 1;  // Unfilled cell cannot be wrong
    int i, j;
    for(i = 0; i < 9; i++) {  // Checks for repeats on a collumn
        if(i == col)
            continue;
        if(sudoku[lin][i] == n) {
            return 0;
        }
    }
    for(i = 0; i < 9; i++) {  // Checks for repeats on a line
        if(i == lin)
            continue;
        if(sudoku[i][col] == n) {
            return 0;
        }
    }

    int square = ((col/3)+1) + (lin/3)*3;

    // Checks for repeats on its own square
    if(square % 3 == 1){
        for(j = 0; j < 3; j++)
            for(i = square-1; i < square+2; i++) {
                if(i == lin && j == col)
                    continue;
                if(sudoku[i][j] == n)
                    return 0;
            }
    } else if(square % 3 == 2) {
        for(j = 3; j < 6; j++)
            for(i = square-2; i < square+1; i++) {
                if(i == lin && j == col)
                    continue;
                if(sudoku[i][j] == n)
                    return 0;
            }
    } else {
        for(j = 6; j < 9; j++)
            for(i = square-3; i < square; i++) {
                if(i == lin && j == col)
                    continue;
                if(sudoku[i][j] == n)
                    return 0;
            }
    }
    // Returns 0 if any repeats found
    // Returns 1 if correct
    return 1;
}
