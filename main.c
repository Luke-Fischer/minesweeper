#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 16
#define COLS 30
#define BOMBS 99

char ** createBoard(){
    char ** array = (char **)malloc(ROWS * sizeof(char *));
    for (int i = 0; i < ROWS; i++){
        array[i] = (char*)malloc(COLS * sizeof(char));
    }
    return array;
}

char ** fillBackBoard(char ** backBoard){

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            backBoard[i][j] = '0';
        }
    }

    //Populate boards with mines
    int bombsLeft = 100;
    while (bombsLeft > 1) {
        int row_ran = rand() % ROWS;
        int col_ran = rand() % COLS;
        if(backBoard[row_ran][col_ran] == '0'){
            backBoard[row_ran][col_ran] = '1';
            bombsLeft--;    
        } 
    }
    return backBoard;
}

char ** fillFrontBoard(char ** frontBoard){

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            frontBoard[i][j] = '-';
        }
    }
    return frontBoard;
}

void printBoard(char ** backBoard){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%c  ", backBoard[i][j]);
        }
        printf("\n");
    }
}

void freeMem(char ** backBoard){
    for(int i = 0; i < ROWS; i++){
        free(backBoard[i]);
    }
    free(backBoard);
}

int main(){
    //Create Boards
    char ** backBoard; 
    char ** frontBoard;

    /****Set up boards for player****/
    srand(time(NULL));

    //Allocate memory for board
    backBoard = createBoard();
    frontBoard = createBoard();

    //Lay minds for the board
    backBoard = fillBackBoard(backBoard);
    frontBoard = fillFrontBoard(frontBoard);

    //Displays the front end of the board
    printBoard(backBoard);
    printBoard(frontBoard);

    //Free allocated memory
    freeMem(backBoard);
    freeMem(frontBoard);

    return 0;
}
