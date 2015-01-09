#ifndef CONNECT4MINIMAX_H_
#define CONNECT4MINIMAX_H_

//#include "Connect4.h"
#include "MiniMax.h"
#include "BoardMatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PLAYER 1
#define MIN_PLAYER -1
#define SCORES_TABLES_SIZE 9
#define MIN_4_SCORE -4
#define MAX_4_SCORE 4
#define WIN_SEQ_SIZE 4
#define CONST_VECTOR_SIZE 7
//#define EVAL_NOT_RELEVANT -1000000

extern const int constantVector[CONST_VECTOR_SIZE];

typedef struct boardstate {
	int** boradMatrix;
	int player;
	bool isValid;
}StateOfBoard;

int getBestMove(StateOfBoard currentState,int numSteps);

int checkForWinner(StateOfBoard currentState);

int evaluate(void* state);

ListRef getChildren(void* state);

StateOfBoard buildBoard();

void FreeState(void* state);

#endif /* CONNECT4MINIMAX_H_ */
