#include <stdio.h>

//HISTORY OF THE PLAYS

typedef struct history{
    char **mat;
    int *finalMat;
    int coordX, coordY;

}HISTORY;

//LOG FUNCTIONS

//Create a log txt file
void new_file();

//Open the txt file to read and returns the opened file in mode read
FILE* open_file_read();

//Open the txt file to edit and returns the opened file in mode append
FILE* open_file_edit();

//Close the file
void close_file(FILE *file);



//Update the file log.txt with the history of the board acoording with the plays until the end of the game
void edit_history(HISTORY info_plays, int nlin, int nCol);


//Update the file log.txt with the template when the game it's over
void editFinal_history(HISTORY info_plays, int nlin, int nCol);

//Calculates the game start time
void login_time();

//Prints the game start time
void recordTime(int day, int month, int year, int  hour, int  min, int sec);

//Prints a message to the player according with the chosen coordinates int the history
void print_message_history(int valid, int lin);

//Print the coordinate chosen by the player in the history
void print_chosen_coord(HISTORY info_plays);

