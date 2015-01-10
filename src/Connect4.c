#include "Connect4.h"
#include "utils.h"


/*Initialize the Global Variables*/
	int first_cmd_set_num_steps = 0;
	int num_steps=0;
	//int game_over = 0; /* flag that determines if the game is over or not*/


/*prints the board according to the matrix*/
void print_board(int**  mat)
{
	int i,j;
	for(i = 0; i < MAT_ROWS; i++)
	{
		printf("| ");
		for(j = 0; j< MAT_COLS; j++)
		{
			if(mat[i][j] == EMPTY)
				printf("  "); // 2 spaces
			else
				printf("%c ", mat[i][j] == USER ? USER_SIGN : COMPUTER_SIGN);
		}
		printf("|\n");
	}
	for(j = 0; j< 3 + MAT_COLS*2; j++){
		printf("-");
	}

	// next line + 1 space
	printf("\n ");
	for(j= 1; j<= MAT_COLS; j++)
	{
		printf(" %d",j);
	}

	printf("  \n");
}


/*exits the game with exit mode 0*/
void quit()
{
	FreeBoardMatrix(mat);
	exit(0);
}

/*return true iff the command include only whitespace */
int empty_command(char * c)
{
	while(*c != '\0'){
		if(!isspace(*c))
		{
			return 0;
		}
		c++;
	}
	return 1;
}



int main()
{
	_debug = true;

	current_mode = MODE_START;
	mat = buildBoardMatrix();
	if (mat == NULL)
		perror(ERROR_MALLOC_FAILED);
	char command [command_length+2]; //the command line include up to command_length characters and ('\n') and ('\0')

	print_board(mat);
	while(1)
	{
		if(fgets(command,sizeof(command),stdin)==NULL) /*stores the the characters from the user to 'command'*/
		{
			perror("Error: standard function fgets has failed.\n"); //standard function fails
			FreeBoardMatrix(mat);
			exit(1);
		}
		/*if the place before the last is not '\n' and length of the array is only command+1 then the input is longer then 40 characters*/
		if (command[sizeof(command)-2]!='\n'&&strlen(command)==command_length+1)
			{
				printf("Error: command length must be less than or equal to %d characters.\n",command_length);
				while(getchar()!='\n'){} /*read until '\n' in order to read the next command properly*/
				continue;
			}
		/* checks if the command includes only whitespace*/
		if(empty_command(command))
		{
			printf("Error: command must have at least one non-whitespace character.\n");
			continue;
		}

		doing_commands(command);

	}
	return 0;
}


/* returns a pointer to first non whitespace character, whitespace is ' ', '\n'*/
char * non_ws(char *c)
{
	while(isspace(*c)){
		c++;
	}
	return c;
}
/* gets a command , and a command name, returns true iff command is equal to command name */
int is_cmd_type(char *command, char *cmd_name)
{
	/*the strstr function returns a pointer in command that points to a string identical
	 * to command_name. if no such sub exists it returns a null pointer
	 */
	if (strstr(command, cmd_name) != NULL)
	{
		return 1;
	}
	return 0;
}

/* param the command line, the name of the command, the length of the command
 * getts the number from the command, according to it's type */
int get_cmd_argument(char *command, char *cmd_name, int cmd_name_length )
{
	char *pos = command + cmd_name_length;
	return atoi(pos);	// array to string, ignores white spaces
}

/*sets the number of steps to look ahead in the mini-max algorithm*/
int set_number_steps(char* command)
{
	int num_steps;

	num_steps=get_cmd_argument(command,cmd_num_steps,cmd_num_steps_len);
	if((num_steps<1)||(num_steps>7)){
		printf("Error: number of mini-max steps must be between 1-7.\n");
		return 0;
	}
	return num_steps;
}

/* calculate the best movement to general player, according the mini-max algorithm and the current state*/
int move (StateOfBoard player,int num_steps){
	int bestColumn;

	bestColumn = getBestMove(player,num_steps)+1;
	return bestColumn;
}

/*suggests the best movement to the user according the mini-max algorithm and the current state*/
void suggest_move(int num_steps)
{
	int bestColumn;
	StateOfBoard user;
	user.boradMatrix = mat;
	user.player = USER;
    user.isValid = true;
	bestColumn = move(user,num_steps);
	printf ("Suggested move: add disc to column %d.\n",bestColumn);
}

/* the computer move according the mini-max algorithm and the current state*/
void computer_move()
{
	int bestColumn;
	StateOfBoard computer;
	computer.boradMatrix = mat;
	computer.player = COMPUTER;
	computer.isValid = true;
	bestColumn = move(computer, num_steps);
	printf("Computer move: add disc to column %d.\n", bestColumn);
	add_disc_to_board(bestColumn,COMPUTER,mat);
}

//add disc according to the user choice to the board
void add_disc(char * command)
{
	int col=1;
	print_error canAdd;
	Winner winner;

	col = get_cmd_argument(command,cmd_add_disc,cmd_add_disc_len);
	canAdd=CheckIfDiscCanAdded(col,mat);

	/*if the column is not full, add the disc*/
	if(canAdd.success)
	{
		add_disc_to_board(col,USER,mat);

		//if the user didn't win the computer will continue to play
		winner = is_win(USER);
		if(!(winner.win))
		{
			//if the board is full, the computer won't play
			if(!is_full(mat))
			{
				computer_move();

				// if the computer win
				winner = is_win(COMPUTER);
				if(winner.win)
				{
					print_board(mat);
					printf("%s", winner.output);
				}

				//if the computer didn't win, check if the board is full
				else
				{
					if (is_full(mat)) {
						printf("Game over: board is full and there is no winner.\n");
						current_mode = MODE_GAME_OVER;
					}
					else {
						print_board(mat);
					}
				}
			}
			else
			{
				printf("Game over: board is full and there is no winner.\n");
				current_mode = MODE_GAME_OVER;
			}
		}
		//if the user win, print the right output
		else {
			print_board(mat);
			printf("%s", winner.output);
		}

	}
	//the disc can't be added then we need to print the right error
	else {
		char stringError[50];
		sprintf(stringError ,canAdd.errorCode,col);
		printf("%s",stringError);
	}
}



/* restarts the game,
 * resets the board to empty board,prints the right message and resets the game over flag
 */
void restart_game()
{
	int i,j;
	for (i=0;i<MAT_ROWS;i++)
	{
		for(j=0;j<MAT_COLS;j++)
		{
			mat[i][j]=EMPTY;
		}
	}
	printf("Game restarted.\n");
	print_board(mat);
	current_mode = MODE_START;

	//the first function should be set_number_steps again
	first_cmd_set_num_steps=0;
}

//doing the game's command
void doing_commands( char * command)
{

	char *command_pos=non_ws(command);

	if (is_cmd_type(command_pos,cmd_num_steps))
	{
		if (current_mode != MODE_GAME_OVER) {
			num_steps= set_number_steps(command_pos);
			if (num_steps) current_mode = MODE_GAME;
		}
		else
		{
			printf(ERROR_GAME_OVER);
		}
	}

	else if(is_cmd_type(command_pos,cmd_quit))
	{
		quit();
	}
	else if(is_cmd_type(command_pos,cmd_restart))
	{
		restart_game();
	}
	else if(is_cmd_type(command_pos,cmd_move))
	{
		if (current_mode == MODE_GAME_OVER) printf(ERROR_GAME_OVER);
		if (current_mode == MODE_START) printf(ERROR_SET_NUMBER_OF_STEPS);
		if (current_mode == MODE_GAME) suggest_move(num_steps);
	}
	else if(is_cmd_type(command_pos,cmd_add_disc))
	{
		if (current_mode == MODE_GAME_OVER) printf(ERROR_GAME_OVER);
		if (current_mode == MODE_START) printf(ERROR_SET_NUMBER_OF_STEPS);
		if (current_mode == MODE_GAME) add_disc(command);
	}
	//if the command is not from the command list
	else {
		printf("Error: command %s not supported.\n",strtok(command_pos,"\n"));
	}
}

//checks whether there is a winner
Winner is_win(int player)
{
	StateOfBoard currentGameState;
	currentGameState.player=player;
	currentGameState.boradMatrix = mat;
	currentGameState.isValid = true;
	Winner winner;

	//the computer won
	winner.win = false;
	winner.player = checkForWinner(currentGameState);
	if (winner.player == USER) {
		winner.win = true;
		winner.output = "Game over: you win.\n";
		current_mode = MODE_GAME_OVER;
	}
	else if (winner.player == COMPUTER)
	{
		winner.win = true;
		winner.output = "Game over: computer wins.\n";
		current_mode = MODE_GAME_OVER;
	}
	return winner;
}


