#pragma once

#ifndef GAME_PIECE
#define GAME_PIECE

// list of colors for game pieces
enum piece_color {
	red = 0,
	orange = 1,
	yellow = 2,
	green = 3,
	blue = 4,
	purple = 5,
	brown = 6,
	black = 7,
	white = 8,
	noColor = 9,
	invalidColor = 10
};

// struct: a game_piece has a color, name, and display option (i.e. printed character)
struct game_piece {
	game_piece(piece_color color, string name, string display);
	piece_color color_;
	string name_;
	string display_;
};

// function declarations listed here: 
string enumToString(piece_color x);
piece_color stringToEnum(string y);

#endif /* GAME_PIECE */