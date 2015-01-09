/*
 * Connect4.h
 *
 *  Created on: Dec 26, 2014
 *      Author: hila
 */

#ifndef CONNECT4_H_
#define CONNECT4_H_

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <ctype.h>
#include "BoardMatrix.h"
#include "Connect4MiniMax.h"

//the board size
#define COLS 17
#define ROWS 8


// Errors defines
#define ERROR_GAME_OVER "Error: game is over.\n"
#define ERROR_MALLOC_FAILED "Error: standard function malloc has failed.\n"
#define ERROR_SET_NUMBER_OF_STEPS "Error: first command must be set_number_steps.\n"

#define command_length 40 // the length of the command from the user

//the commands names and lengths
#define cmd_num_steps "set_number_steps "
#define cmd_num_steps_len  17
#define cmd_add_disc  "add_disc "
#define cmd_add_disc_len  9
#define cmd_move  "suggest_move"
#define cmd_quit  "quit"
#define cmd_restart  "restart_game"
#define MODE_START 1
#define MODE_GAME 2
#define MODE_GAME_OVER 3




/*Global Variables*/
	int** mat;
	 int first_cmd_set_num_steps; /* flag if he first command is set_numer_steps
	 	 	 	 	 	 	 	 	*if it is not 0 then the first command is not set_number_steps
	 	 	 	 	 	 	 	 	 */
	 //char * command_pos; //the place where the command starts in the command line
	int num_steps;
	int game_over ; /* flag that determines if the game is over or not*/
	int current_mode;

typedef struct winner{
		bool win;
		int player;
		char* output;
	}Winner;


void print_board(int**  mat);
void init_height_col(); //maybe to delete
//void quit();
int empty_command(char * c);
char * non_ws(char *c);
int is_cmd_type(char *command, char *cmd_name);
int get_cmd_argument(char *command, char *cmd_name, int cmd_name_length );
int set_number_steps(char* command);
void suggested_move(int num_steps);
void add_disc(char * command);
//void add_disc_to_board(int col, int who);
void computer_move();
void restart_game();
void doing_commands( char * command);
Winner is_win(int player);
bool is_full();



#endif /* CONNECT4_H_ */
