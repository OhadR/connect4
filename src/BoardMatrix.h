#ifndef BOARDMATRIXX_H_
#define BOARDMATRIXX_H_

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

//the matrix size
#define MAT_ROWS 6
#define MAT_COLS 7

//the sign and numbers represent the user and the computer
#define EMPTY 0
#define USER 1
#define COMPUTER -1
#define USER_SIGN 'O'
#define COMPUTER_SIGN 'X'
#define ERROR -1
#define SUCCESS 0

struct Print_error
	{
	bool success;
	char *errorCode;
	};
typedef struct Print_error print_error;

int** buildBoardMatrix();

void copyBoardsMatrix(int** fromBoardMatrix, int** toBoardMatrix);

//int addDiscToBoard(int player,int column, int** BoardMatrx);

void add_disc_to_board(int col, int who, int ** BoardMatrix);

print_error CheckIfDiscCanAdded(int column, int** BoardMatrx);

void FreeBoardMatrix(int** boardMatrix);
bool is_full();

#endif
