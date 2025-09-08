/**
 * @file latinsquare.c
 * @brief Program of a latin square game implementation.
 * 
 * This file contains functions to read, display, and play a Latin square game,
 * as well as functions for validating moves and checking the game state.
 * 
 * @author Nicolas Constantinou
 * @date 27/09/2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 9 // Max size of the Latin square

/**
 * @brief Reads a Latin square from a file.
 * 
 * Reads the Latin square from the specified file and stores it in the provided 
 * 2D array as well as retrieves the size of the square.
 * 
 * @param file The name of the file to read from.
 * @param sudoku The 2D array where the Latin square is stored.
 * @param n Pointer to an integer where the size of the square is stored.
 * @return void
 */
void readLatinSquare(char file[], int sudoku[][N],int *n);

/**
 * @brief Displays the Latin square on the console.
 * 
 * Prints the Latin square with proper formatting.
 * 
 * @param sudoku The 2D array representing the Latin square.
 * @param size The size of the square.
 * @return void
 */
void displayLatinSquare(int sudoku[][N], int size);

/**
 * @brief Plays the Latin square game.
 * 
 * Allows the user to interact with the game, inserting values, checking 
 * validity of moves, and saving the game state.
 * 
 * @param sudoku The 2D array representing the Latin square.
 * @param size The size of the square.
 * @param file The file to save the game state to.
 * @return void
 */
void play(int sudoku[][N], int size, char file[]);

/**
 * @brief Prints the commands for the game.
 *
 * @return void
 */
void printCommands();

/**
 * @brief Checks if a move is valid.
 * 
 * Validates if a move is allowed based on the current state of the Latin square.
 * 
 * @param sudoku The 2D array representing the Latin square.
 * @param size The size of the square.
 * @param val The value to be inserted.
 * @param i The row index.
 * @param j The column index.
 * @return 1 if the move is valid, 0 otherwise.
 */
int validMove(int sudoku[][N], int size, int val, int i, int j);

/**
 * @brief Validates the input provided by the user.
 * 
 * Checks if the row, column, and value entered by the user are within valid ranges.
 * 
 * @param i Row index.
 * @param j Column index.
 * @param val The value to be inserted.
 * @param size The size of the square.
 * @return 1 if input is valid, 0 otherwise.
 */
int checkInput(int i, int j, int val, int size);

/**
 * @brief Checks if the game is complete.
 * 
 * Validates if the Latin square is correctly filled and the game is won.
 * 
 * @param sudoku The 2D array representing the Latin square.
 * @param size The size of the square.
 * @return 1 if the game is won, 0 otherwise.
 */
int checkGame(int sudoku[][N], int size);

/**
 * @brief Saves the current state of the Latin square to a file.
 * 
 * Writes the current game state to an output file.
 * 
 * @param sudoku The 2D array representing the Latin square.
 * @param size The size of the square.
 * @param file The file to save the state to.
 * @return void
 */
void writeLatinSquare(int sudoku[][N], int size, char file[]);

/**
 * @brief The main function to run the game.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return void
 */
void main(int argc, char *argv[]){
    int sudoku[N][N] = {0};
    int size = 0;
    if(argc != 2){
        printf("Missing arguments\n");
        return;    
    }
    readLatinSquare(argv[1], sudoku, &size);
    if(size == 0){
        return;
    }
    play(sudoku, size, argv[1]);
}

void readLatinSquare(char file[], int sudoku[][N], int *n){

    FILE *fp;
    fp = fopen(file, "r");
    if(fp == NULL){
        printf("error, cannot open file...");
    }

    fscanf(fp, "%d", n);
    if(*n>N){
        printf("wrong n...");
        return;
    }

    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
        fscanf(fp, "%d", &sudoku[i][j]);
        if(abs(sudoku[i][j])>*n){
            printf("File contains invalid values!\n");
            *n = 0;
            return;
        }
        }
    }

    if(!feof(fp)){
        printf("File contains more data than expected!\n");
        *n = 0;
        return;
    }

    fclose(fp);

}

void displayLatinSquare(int sudoku[][N], int size){

    int col = 0, row = 0;
    for(int i = 0; i <= (2*size); i++){
       for(int j = 0; j <= (size*6); j++){
        if(j%6==0 && i%2==0){
            printf("+");
        }
        else if(j%6!=0 && i%2==0){
            printf("-");
        }
        else if(i%2!=0 && j%6==0){
            printf("|");
        }
        else if(i%2!=0 && sudoku[row][col]<0 && j%2==0){
            printf("(%d)", abs(sudoku[row][col]));
            j+=2;
            col++;
        }
        else if(j%3==0 && i%2!=0){
            printf("%d ", sudoku[row][col]);
            j++;
            col++;
        }
        else{
            printf(" ");
        }
       }
       if(i%2==0 && i%4!=0){
        row++;
       }
       col=0;
       printf("\n");
    }
}

void writeLatinSquare(int sudoku[][N], int size, char file[]){

    char filename[100] = "-out";
    strcat(filename, file);

    FILE *fp;
    fp = fopen(filename, "w");

    printf("\nSaving to out-lsq1.txt...\n");

    fprintf(fp, "%d\n", size);
    for(int i=0; i<size; i++){
        for(int j = 0; j<size; j++){
            fprintf(fp, "%d ", (sudoku[i][j]));
        }
       fprintf(fp, "\n");
    }

    fclose(fp);

    printf("Done\n");

}

void play(int sudoku[][N], int size, char file[]){
    int playing = 1;
    int i=0, j=0, val=0;
    int win = 0;
    while(playing == 1 && win == 0){

        displayLatinSquare(sudoku, size);
        printCommands();

        while (scanf("%d,%d=%d",&i,&j,&val) != 3) { 
            while (getchar() != '\n') {}; 
            printf("Error: wrong format of command!\n");
            displayLatinSquare(sudoku, size);
            printCommands();
            }

        int check = checkInput(i, j, val, size);
        while(check==0){
            printf("\nError: i,j or val are outside the allowed range [1..4]!\n");
            displayLatinSquare(sudoku, size);
            printCommands();
            while (scanf("%d,%d=%d",&i,&j,&val) != 3) { 
                while (getchar() != '\n') {}; 
                printf("Error: wrong format of command!\n");
                displayLatinSquare(sudoku, size);
                printCommands();
                }
            check = checkInput(i, j, val, size);
        }

        if(validMove(sudoku, size, val, i, j) == 1){
            if(i==0 && j==0 && val==0){
                playing = 0;
            }
            else if(sudoku[i-1][j-1] != 0 && val==0){
                sudoku[i-1][j-1] = 0;
                printf("\nValue cleared!\n");
            }
            else{
                for(int row = 0; row < size; row++){
                    for(int col = 0; col < size; col++){
                        if(i-1 == row && j-1 == col){
                            sudoku[row][col] = val;
                        }  
                    }
                }
                printf("\nValue inserted!\n");
            }
        }

        win = checkGame(sudoku, size);

    }

    if(win==1){
        printf("\nGame completed!!!\n");
        displayLatinSquare(sudoku, size);
    }

    writeLatinSquare(sudoku, size, file);

    return;

}

int checkGame(int sudoku[][N], int size){

    for(int i = 0; i < size; i++){
        int arr[N] = {0};
        for(int j = 0; j < size; j++){
            if(abs(sudoku[i][j]) == 0){
                return 0;
            }
            else if(arr[abs(sudoku[i][j])-1] ==  0){
                arr[abs(sudoku[i][j])-1] == 1;
            }
            else{
                return 0;
            }
        }
    }

    for(int j = 0; j < size; j++){
        int arr[N] = {0};
        for(int i = 0; i < size; i++){
            if(abs(sudoku[i][j]) == 0){
                return 0;
            }
            else if(arr[abs(sudoku[i][j])-1] ==  0){
                arr[abs(sudoku[i][j])-1] == 1;
            }
            else{
                return 0;
            }
        }
    }

    return 1;

}

int validMove(int sudoku[][N], int size, int val, int i, int j){

    if(i==0 && j==0 && val==0){
        return 1;
    }
    if(sudoku[i-1][j-1] != 0 && val!=0){
        printf("\nError: cell is already occupied!\n");
        return 0;
    }
    else if(sudoku[i-1][j-1] == 0 && val==0){
        printf("\nError: illegal to clear cell!\n");
        return 0;
    }
    else if(sudoku[i-1][j-1] < 0 && val==0){
        printf("\nError: illegal to clear cell!\n");
        return 0;
    }
    
    if(i!=0 && j!=0 && val==0){
        return 1;
    }

    for(int col = 0; col < N; col++){
        if(abs(sudoku[i-1][col]) == val){
            printf("\nError: Illegal value insertion!\n");
            return 0;
        }
    }

    for(int row = 0; row < N; row++){
        if(abs(sudoku[row][j-1]) == val){
            printf("\nError: Illegal value insertion!\n");
            return 0;
        }
    }

    return 1;

}

void printCommands(){
    printf("Enter your command in the following format:\n");
    printf(">i,j=val: for entering val at position (i,j)\n");
    printf(">i,j=0 : for clearing cell (i,j)\n");
    printf(">0,0=0 : for saving and ending the game\n");
    printf("Notice: i,j,val numbering is from [1..4]\n");
    printf(">");
}

int checkInput(int i, int j, int val, int size){
    if((i<0 || i>size)||(j<0 || j>size)||(val<0 || val>size)){
        return 0;
    }
    return 1;
}