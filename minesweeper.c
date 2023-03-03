#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWS 16
#define COLS 30
#define BOMBS 99

//Allocated memory for boards
char ** createBoard(){
    char ** array = (char **)malloc(ROWS * sizeof(char *));
    for (int i = 0; i < ROWS; i++){
        array[i] = (char*)malloc(COLS * sizeof(char));
    }
    return array;
}

//Fills the backend board
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

//Fills users board grid
char ** fillFrontBoard(char ** frontBoard){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            frontBoard[i][j] = '-';
        }
    }
    return frontBoard;
}

//Displays baord in grid form
void printBoard(char ** backBoard){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%c  ", backBoard[i][j]);
        }
        printf("\n");
    }
}

//Frees mallocd board mem
void freeMem(char ** backBoard){
    for(int i = 0; i < ROWS; i++){
        free(backBoard[i]);
    }
    free(backBoard);
}

//Check if tile is on the board
bool isEligible(int x, int y){
    if((x >= ROWS) || (x < 0) || (y >= COLS) || (y < 0)){
        return false;
    }
    return true;
}

//computes how many bombs are next to each non-bomb tile
char ** computeTiles(char ** backBoard, char ** temp){

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            int bombsTouching = 0;
            if(backBoard[i][j] == '0'){
                //top left
                if((isEligible(i - 1, j - 1) == true) && (backBoard[i - 1][j - 1] == '1')){
                    bombsTouching++;
                }
                //top middle
                if((isEligible(i, j - 1) == true) && backBoard[i][j - 1] == '1'){
                    bombsTouching++;
                }
                
                //Top right
                if((isEligible(i + 1, j - 1) == true) && backBoard[i + 1][j - 1] == '1'){
                    bombsTouching++;
                }
            
                //middle left
                if((isEligible(i - 1, j) == true) && backBoard[i - 1][j] == '1'){
                    bombsTouching++;
                }
                //middle right
                if((isEligible(i + 1, j) == true) && backBoard[i + 1][j] == '1'){
                    bombsTouching++;
                }
                //bottom left 
                if((isEligible(i - 1, j + 1) == true) && backBoard[i - 1][j + 1] == '1'){
                    bombsTouching++;
                }
                //bottom middle
                if((isEligible(i, j + 1) == true) && backBoard[i][j + 1] == '1'){
                    bombsTouching++;
                }
                //bottom right 
                if((isEligible(i + 1, j + 1) == true) && backBoard[i + 1][j + 1] == '1'){
                    bombsTouching++;
                }
                temp[i][j] = bombsTouching + '0';
            }
            else{
                temp[i][j] = '-';
            }
        }
    }

    //Free board before losing its pointer
    for(int i = 0; i < ROWS; i++){
        free(backBoard[i]);
    }
    free(backBoard);
    
    //Return backend board
    return temp;
}

bool validateInput(char action, int x, int y){
    if(action != 'S' && action != 'F'){
        return false;
    }
    if(isEligible(x, y) == false){
        return false;
    }
    return true;
}

int main(){
    int bombsLeft = BOMBS;
    int tilesLeft = (ROWS * COLS) - BOMBS;
    //Create Boards
    char ** backBoard; 
    char ** backBoardTemp;
    char ** frontBoard;

    /****Set up boards for player****/
    srand(time(NULL));

    //Allocate memory for board
    backBoard = createBoard();
    backBoardTemp = createBoard();
    frontBoard = createBoard();

    //Lay minds for the board
    backBoard = fillBackBoard(backBoard);
    frontBoard = fillFrontBoard(frontBoard);

    //Displays the front end of the board
    backBoard = computeTiles(backBoard, backBoardTemp);

    while(1){
        char action = '\0';
        int x = 0;
        int y = 0;
        printf("\n\n");
        printBoard(frontBoard);
        printf("Bombs Left: %d\n", bombsLeft);
        printf("step on a tile using: \"S row col\" where x and y are coordinates on the map\n");
        printf("Plant a warning flag using: \"F row col\" where x and y are coordinates on the map\n");
        scanf("%c %d %d", &action, &x, &y);
        
        x--;
        y--;

        if(validateInput(action, x, y) == true){
            if(action == 'S'){
                if(backBoard[x][y] == '-'){
                    printBoard(backBoard);
                    printf("\nGame Over!\n");
                    //free memory
                    freeMem(frontBoard);
                    freeMem(backBoardTemp);
                    exit(1);
                }
                else{
                    tilesLeft--;
                    frontBoard[x][y] = backBoard[x][y];
                    if(tilesLeft == 0){
                        printf("Congrats you safely cleared all the mines!\n");

                        //Free allocated memory
                        freeMem(frontBoard);
                        freeMem(backBoardTemp);
                        exit(1);
                    }
                }
            }
            else{
                frontBoard[x][y] = 'F';
                bombsLeft--;
            }
        }
        else{
            printf("Invalid input. See usage above.\n");
        }
        printf("\n\n");
        
    }

    //Free allocated memory
    freeMem(frontBoard);
    freeMem(backBoardTemp);

    return 0;
}
