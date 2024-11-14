//CHARACTER MATRIX's functions

//Creating the matrix board and initialize it with 'x'
char** newMatrix(int nLin, int nCol);

//Modifies the matrix mat according wih the coordinates that were chosen by the player with the number of nearby mines
void modifyMat(char** mat, int nLin, int nCol, int coordX, int coordY, int minesProx);

//Priting the matrix board
void printMatrix(char** mat, int nLin, int nCol);

//Frees up the memory occupied by the board
void freeBoard(char** mat, int nLin, int nCol);


//TEMPLATE's FUNCTIONS

//Create the template and return the matrix template initializated with zero
int *newTemplate(int nLin, int nCol);

//Modify the template according to the number of nearby mines
void finalTemplate(int *mines, int nLin, int nCol, int nMines);

//Prints the template
void printTemplate(int *mines, int nLin, int nCol);


//REPEAT matrix funtions

//Create the matrix that checks if the coordinate was already chosen, and return this matrix initializated with zero
int *newRepeat(int nLin, int nCol);
