#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"
#include "log.h"

//ATENÇÃO!!!!
// Este arquivo deve ser compilado no seguinte formato: "gcc campo_minadoV2_sarah_lima.c matriz.c log.c"


//GAME'S FUNCTIONS

//Choose the game level
void gameLevel(int *lin, int *col, int *plays, int *nMines ){
    int level, invalid;
    invalid = 1;

    while(invalid){
        scanf("%d", &level);

        switch(level){
            case 1:
                *lin = 10;
                *col = 10;
                *nMines = 15;
                *plays = (*lin * (*col)) - (*nMines);
                invalid = 0;

                break;

            case 2:
                *lin = 20;
                *col = 20;
                *nMines = 60;
                *plays = (*lin * (*col)) - (*nMines);
                invalid = 0;

                break;
            
            case 3:
                *lin = 30;
                *col = 30;
                *nMines = 135;
                *plays = (*lin * (*col)) - (*nMines);
                invalid = 0;

                break;
            
            default:
                printf("ERROR! level not found =( \nPlease, enter a valid level!!!\n\n");
                invalid = 1;

                break;
        }
    }
}

//Initializing a matrix with the coordinate of the mines
void createMines(int *mines, int nLin, int nCol, int nMines, int coordX, int coordY){
    int randNum, cont, line, column;
    int coord[2];
    cont = 0;
    
    
    //Inicializating the seed with time
    srand(time(NULL));

    //Modifying the copy mines with "-1", which means that the designated coordinate has a mine
    while(cont < nMines){
        int element;

        //The valor of "coord" will be a number beetween 0 and the number of lines(because the number of lines is equal to the number of columns)
        for(int indV = 0; indV < 2; indV++){ 
            randNum = rand() %((nLin - 1));
            coord[indV] = randNum;
        }
        line = coord[0];
        column = coord[1];

        element = mines[line*nCol+column];
       
        if((element != -1) && (abs(coord[0]-coordX) > 1) && (abs(coord[1]-coordY) > 1)){
          
            mines[line*nCol+column] = -1;
            cont++;
        }
    }
}

//Calculates the number of mines within a distance of at least one 
int minesProx(int* mines, int nLin, int nCol, int coordX, int coordY){
    int qntdMines;
    qntdMines = 0;

    for(int i = 0; i < nLin; i++){
        for(int j = 0; j < nCol; j++){
    
            if((mines[i*nCol+j] == -1) && (abs(i - coordX) <= 1) && (abs(j - coordY) <= 1)){
                qntdMines++;
            }
        }
    }

    //Returns the number of mines near the coordinate chosen by the player
    return qntdMines;
}

//If the player hits a mine, it prints game over. But if the number of moves runs out and he hasn't hit a mine, he wins.
int gameOver(int* mines, int plays, int coordX, int coordY, int nCol){
    if(mines[coordX*nCol+coordY] == -1){
        return 1;
    }
    
    return 0;
} 

//Handling with exceptions
int noExceptions( int* plays, int *repeat, int valid, int lin, int col, int *coordX, int *coordY){
    int end;

        //Handling with some exceptions
        
        while(scanf("%d,%d", coordX, coordY) == 2){

            //Subtracts minus 1 from the value of the coordinates
            *coordX -= 1;
            *coordY -= 1;


            //Check if the coordinate has alredy been chosen
            if(repeat[(*coordX * col)+ *coordY] == 1){

                *plays++;
                return 2;
            }

            //Check if the coordinate is out of limits of the matrix
            else if((*coordX >= lin)||(*coordX < 0)||(*coordY >= col)||(*coordY < 0)){
                
                *plays++;
                return 0;
            }
            else{

                repeat[(*coordX * col)+ *coordY] = 1;
                return 1;
            }

        }
        if(scanf("%d", &end) == -1){  

            printf(" fim do arquivo...\n");
            return -1;
        }
}


//Flood fill functions
    
void flood_fill(char **mat, int *mines, int nLin, int nCol,  int coordX, int coordY){



    if( (coordX >= nLin) || (coordY >= nCol) || (coordX < 0) || (coordY < 0) ){
        return;
    }

     if(mat[coordX][coordY] != 'x'){
        return;
    }

    int qntdMines = mines[coordX*nCol + coordY];
    
    modifyMat(mat, nLin, nCol, coordX, coordY, qntdMines);

    if(mines[coordX*nCol+ coordY] != 0){
        return;
    }

    flood_fill(mat, mines, nLin, nCol, coordX -1, coordY); //up
    flood_fill(mat, mines, nLin, nCol, coordX +1, coordY); //down
    flood_fill(mat, mines, nLin, nCol, coordX, coordY -1); //right
    flood_fill(mat, mines, nLin, nCol, coordX, coordY +1); //left

    //diagonals
    flood_fill(mat, mines, nLin, nCol, coordX -1, coordY -1); 
    flood_fill(mat, mines, nLin, nCol, coordX -1, coordY +1);
    flood_fill(mat, mines, nLin, nCol, coordX +1, coordY -1);
    flood_fill(mat, mines, nLin, nCol, coordX +1, coordY +1); 

}
//Prints a  message to the player according with the chosen coordinates
void print_message(int valid, int lin){

    if(valid == 1){
        printf("- Digite uma coordenada no formato \"x,y\" que esteja entre 1 e %d:\n", lin);
    }
    else if(valid == 2){
        printf("- Essa coordenada já foi escolhida..\n- Por favor, digite outra coordenada  no formato \"x,y\" que esteja dentro do intervalo de 1 a %d!!\n", lin);
    }
    else if (!valid){
        printf("- Coordenada inválida!\n- Por favor, digite novamente uma coordenada no formato \"x y\" que esteja dentro do intervalo de 1 a %d!!\n", lin);
    }
}

int main() {
    int lin, col, coordX, coordY, plays, valid, nMines, previousX, previousY, firstPlay;
    HISTORY info_plays;


    //If log.txt file has not yet been created, it calls the new_file function
    if(!open_file_read()){
        new_file();
    }

    //Check if the coordinates chosen by the player are valid
    valid = 1;


    //Check if  its the first round
    firstPlay = 1;

    //Records the start time of the game
    login_time();


    //Start of the game
    printf("\n\n                             ---------------- Bem-vind@ ao minefield game!! -----------------\n\n");

    //Rules of the game
    printf("**O objetivo do jogo eh escolher todas as coordenadas do tabuleiro sem acertar uma\n das minas, ou seja, chegar ao fim do número de jogadas sem acertar uma mina!\n\n");
    
    //Choosing the game level
    printf("Agora, escolha o nível do jogo:\n\n");
    printf("-Digite 1 para o nível fácil;\n");
    printf("-Digite 2 para o nível médio;\n");
    printf("-Digite 3 para o nível difícil;\n\n");
    gameLevel(&lin, &col, &plays, &nMines);


    //Check if the coordinate has alredy been chosen
    int *repeat = newRepeat(lin,col);
   
    //We call the funcion "newMatrix" to create and initializate the matrix mat(board) with 'x'
    char ** mat = newMatrix(lin,col);


    //Create the template
    int *mines = newTemplate(lin, col);


    //Start of the game
    while(plays >= 0){
        int qntdMines = 0;


        //Draw the line of the beginning of the game
        putchar('\n');
        for(int k = 0; k < 110; k++){
            putchar('-');
        }
        putchar('\n');
        putchar('\n');


        //Printing the matrix
        printMatrix(mat, lin, col);

        

        //Draw the line of the beginning of the game
        putchar('\n');
        for(int k = 0; k < 110; k++){
            putchar('-');
        }
        putchar('\n');


        //The player is notified with a message acoording with the chosen coordinates
        print_message(valid, lin);

        //Read the coordinates and verify if it is valid
        valid = noExceptions(&plays, repeat, valid, lin, col, &coordX, &coordY);
        

        //Only initializes the mines after the first coordinate is chosen
        if(firstPlay){
            
            //Inicilizating a copy of the matrix mat acoording with the coodinated generated by the random

            createMines(mines, lin, col, nMines, coordX , coordY); //Subtract minus one because the coordinates chosen by the player starts with 1
            finalTemplate(mines,lin,col,nMines);

            firstPlay = 0;
        }

        //If its not the EOF
        if(valid != -1){ 

            //Initialize the history info

            info_plays.mat = mat;
            info_plays.finalMat = mines;
            info_plays.coordX = coordX+1;
            info_plays.coordY = coordY+1;

        }

        //Updates the history of the plays 
        edit_history(info_plays, lin, col);

        //Prints the message that notified the player in the history
        print_message_history(valid, lin);

        //Print the coordinate chosen by the player in the history
        if(valid != -1) print_chosen_coord(info_plays);


        if(valid == 1){

            qntdMines = minesProx(mines, lin, col, coordX, coordY);

            //Activates the flood fill acoording with the coordinate (who has its valor equal to zero)
            flood_fill(mat, mines, lin, col, coordX, coordY);
        }


        //If the funcion game over return 1, the player lost, and the loop stops 
        int endOfGame = gameOver(mines, plays, coordX, coordY, col);

        if((endOfGame) || valid == -1){

            //Draw the line of the beginning of the game
            putchar('\n');
            for(int k = 0; k < 110; k++){
                putchar('-');
            }
            putchar('\n');


            //Print the matrix template
            printTemplate(mines,lin,col);

            printf("Game over :(\n\n");
            

            //Updating the history of plays with the template
            editFinal_history(info_plays, lin, col);

            break;
        }
        
        else if((plays == 0)){
            printf("parabéns, vc eh fera :)\n");

            //Print the matrix template
            printTemplate(mines,lin,col);

            //Updating the history of plays with the template
            editFinal_history(info_plays, lin, col);

            break;
        }
       
        if(valid){
            plays--;
        }
    }


    //Freeing up the memory occupied by the board and template
    freeBoard(mat, lin, col);
    free(mines);
    free(repeat);

    return 0;
}
