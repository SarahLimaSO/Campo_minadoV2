#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

//CHARACTER MATRIX's functions

//Creating a new matrix board and initialize it with 'x'
char** newMatrix(int nLin, int nCol){
    char **mat = calloc(nLin,sizeof(char*));

    if(mat == NULL){
        printf("ERROR01! Insufficient memory!\n");
        exit(1);
    }

    for(int ind = 0; ind < nLin; ind++){
        mat[ind] = (char*) calloc(nCol,sizeof(char));

        if(mat == NULL){
        printf("ERROR02! Insufficient memory!\n");
            exit(1);
        }
    }
    for(int line = 0; line < nLin; line++){
        for(int column = 0; column < nCol; column++){
            mat[line][column] = 'x';
        }
    }
    return mat;
}

//Modifies the matrix mat according wih the coordinates that were chosen by the player
void modifyMat(char** mat, int nLin, int nCol, int coordX, int coordY, int minesProx){

    //Converts the int minesProx to the correspondent char
    char converted = '0' + minesProx;

    for(int line = 0; line < nLin; line++){
        for(int column = 0; column < nCol; column++){
            if((coordX == line)&&(coordY == column)){
              mat[line][column] = converted;
            }
        }
    }
}


//Priting the matrix Board
void printMatrix(char** mat, int nLin, int nCol){

    //Identifying  the positions columns
    
    printf("    ");
    for(int i = 0; i < nCol; i++){

        if(i < 9){
            printf(" %d  ", i+1);
        }
        else{
            printf(" %d ", i+1);
        }

    }

    putchar('\n');

    for(int line = 0; line < nLin; line++){

        //Identifying  the positions
        if(line < 9){
            printf("%d  ", line+1);
        }
        else{
            printf("%d ", line+1);
        }

        for(int column = 0; column < nCol; column++){
            
            
            putchar('|');
            printf(" %c ",mat[line][column]);  
        }

        putchar('|');
        putchar('\n');
    }
}

//Frees up the memory occupied by the board
void freeBoard(char** mat, int nLin, int nCol){

    for(int ind = 0; ind < nLin; ind++){
        free(mat[ind]);

    }
    free(mat);
}

//TEMPLATE's FUNCTIONS

//Creates the matrix template
int *newTemplate(int nLin, int nCol){

    //Create the template
    int *mines = calloc(nLin*nCol,sizeof(int));

    if(mines == NULL){
        printf("ERROR03! Insufficient memory!");
        exit(1);
    }

    return mines;
}

//Modify the template according to the number of nearby mines
void finalTemplate(int *mines, int nLin, int nCol, int nMines){
    int qntdMines;
    qntdMines = 0;

    //Matrix that stores the coordinates of the mines
    
    for(int i = 0; i < nLin; i++){
        for(int j = 0; j < nCol; j++){

           //If we find the mine... we add plus 1 to the value of the near positions
            if(mines[i*nCol+j] == -1){

                for(int x = i-1; x <= i+1; x++){
                    for(int y = j-1; y <= j+1; y++){

                        if(mines[x*nCol+y]!= -1){

                            if((x<nLin)&&(y<nCol)&&(x>=0)&&(y>=0)){
                                mines[x*nCol+y]++;
                            }
                        }
                    }
                }
            } 
        }
    } 
}

//Print the template with the positions of the mines
void printTemplate(int *mines, int nLin, int nCol){

    putchar('\n');

     //Identifying the positions of the columns
    
    printf("    ");
    for(int cont = 0; cont  < nCol; cont++){

        if(cont < 9){
            printf(" %d  ", cont+1);
        }
        else{
            printf(" %d ", cont+1);
        }

    }
    putchar('\n');

    for(int i = 0; i < nLin; i++){

        //Identifying the positions of the lines
        if(i < 9){
            printf("%d  ", i+1);
        }
        else{
            printf("%d ", i+1);
        }

        for(int j = 0; j < nCol; j++){
            putchar('|');

            if((mines[i*nCol+j] < 0) || (mines[i*nCol+j] > 9)){
                printf("%d ",mines[i*nCol+j]);  
            }
            else{
                printf(" %d ",mines[i*nCol+j]); 
            }

        }
        putchar('|');
        putchar('\n');
    }
    putchar('\n');
    putchar('\n');
} 


//Matrix REPEAT functions

//Create the matrix that checks if the coordinate was already chosen, and return this matrix initializated with zero
int *newRepeat(int nLin, int nCol){

    //Check if the coordinate has alredy been chosen
    int *repeat = calloc(nLin*nCol, sizeof(int));

    if(repeat == NULL){
        printf("ERROR04! Insufficient memory!");
        exit(1);
    }

    return repeat;
}






