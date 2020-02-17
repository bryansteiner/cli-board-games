#pragma once

#ifndef LAB_4
#define LAB_4

// list of array_indices in argv array
enum array_indices {
	programName = 0,
	gameName = 1,
	numArguments = 2
};

// list of flags that will be thrown if the program runs succesfully or with an error
enum flags {
	success = 0,
	failure_command_line_arguments = 1,
	failure_cannot_open_file = 2,
	failure_cannot_read_dimensions = 3,
	failure_cannot_read_line = 4,
	failure_cannot_read_game_piece = 5,
	failure_cannot_match_vector_to_dimensions = 6,
	failure_cannot_extract_coordinates = 7,
	failure_invalid_move = 8,
	failure_stalemate = 9,
	failure_bad_alloc_exception = 10,
	user_request_quit = 11,
	nullpointer_exception = 12,
	overwrite_instance = 13,
	incorrect_name = 14,
	no_valid_moves_one = 15,
	no_valid_moves_both = 16
};

// function declarations listed here: 
int usage(const string &name, const string info);

#endif /* LAB4 */

#pragma once




