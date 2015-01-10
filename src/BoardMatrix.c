#include "BoardMatrix.h"
#include "utils.h"

//this function builds the matrix
int** buildBoardMatrix()
{
	int **board=(int**)malloc(MAT_ROWS*sizeof(int*));
	for(int i=0; i<MAT_ROWS; i++)
	{
		board[i]= (int*)calloc(MAT_COLS, sizeof(int));

		// Check if inner malloc failed and free memory
		if (board[i] == NULL)
		{
			for (int j=0; j<i; j++)
			{
				debug("free memory");
				free(board[i]);
			}
			free(board);
			return NULL;
		}
	}
	return board;
}

void copyBoardsMatrix(int** fromBoardMatrix, int** toBoardMatrix) {
	for (int row=0; row<MAT_ROWS; row++) {
		for (int col=0; col<MAT_COLS; col++) {
			toBoardMatrix[row][col]	= fromBoardMatrix[row][col];
		}
	}
}

void FreeBoardMatrix(int** boardMatrix) {
	int i;
	for(i=0;i<MAT_ROWS;i++){
		free(boardMatrix[i]);
	}
	free (boardMatrix);
}


/*add disc to the place in the board and prints it*/
void add_disc_to_board(int col, int who, int ** BoardMatrix)
{
	/*updates the matrix according to the player*/
	for(int row=MAT_ROWS-1;row>=0;row--){
		if(BoardMatrix[row][col-1]==EMPTY){
			BoardMatrix[row][col-1] = who;
			break;
		}
	}
}


//returns true if disc can be added to the column
print_error CheckIfDiscCanAdded(int column, int** BoardMatrix) {
	print_error canAdd;
	if((column<1)||(column>7))
		{
			canAdd.success = false;
			//canAdd.errorCode= ERROR 1;
			canAdd.errorCode = "Error: column number must be in the range 1-7.\n";
		}
	else if(BoardMatrix[0][column-1]!=EMPTY)// if the column is full
		{
			canAdd.success = false;
			//canAdd.errorCode=ERROR 2;
			canAdd.errorCode = "Error: column %d is full.\n";
		}
	else canAdd.success = true;
	return canAdd;
}
//if the board is full prints the right output and returns true
bool is_full(int** mat){

	//checks only the row[0], it is the last row to be filled
	for(int i=0; i <MAT_COLS; i++){
		if(mat[0][i]==EMPTY){
			return false;
		}
	}
	return true;
}


void debug(const char * msg)
{
	if(_debug)
	{
		printf( "[debug] %s\n", msg);
	}
}

