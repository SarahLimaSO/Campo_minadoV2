#include <stdio.h>

//HISTORY OF THE PLAYS

typedef struct history{
    char **mat;
    int *finalMat;
    int coordX, coordY;

}HISTORY;

//Update the file log.txt with the history of the board acoording with the plays until the end of the game
void edit_history(HISTORY info_plays, int nlin, int nCol);


//Update the file log.txt with the template when the game it's over
void editFinal_history(HISTORY info_plays, int nlin, int nCol);

//Calculates the game start time
void login_time();


//Prints the game start time
void recordTime(int day, int month, int year, int  hour, int  min, int sec);

//Create a log txt file
void new_file();

//Open the txt file to read
FILE* open_file_read();

//Open the txt file to edit
FILE* open_file_edit();


