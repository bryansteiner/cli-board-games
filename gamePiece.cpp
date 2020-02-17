// gamePiece.cpp

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>	
#include <string>	
#include <vector>
#include <iomanip>	// std::setw
#include <memory>	// shared_ptr

using namespace std;
#include "Lab4.h"
#include "GamePiece.h"
#include "GameBase.h"

game_piece::game_piece(piece_color color, string name, string display)
	: color_(color), name_(name), display_(display) {}

string enumToString(piece_color x) {
	switch (x)
	{
	case red:
		return "red";
		break;
	case orange:
		return "orange";
		break;
	case yellow:
		return "yellow";
		break;
	case green:
		return "green";
		break;
	case blue:
		return "blue";
		break;
	case purple:
		return "purple";
		break;
	case brown:
		return "brown";
		break;
	case black:
		return "black";
		break;
	case white:
		return "white";
		break;
	case noColor:
		return "no color";
		break;
	default:
		return "invalid color";
		break;
	}
}

piece_color stringToEnum(string y) {
	if (y == "red") return red;
	else if (y == "orange") return orange;
	else if (y == "yellow") return yellow;
	else if (y == "green") return green;
	else if (y == "blue") return blue;
	else if (y == "purple") return purple;
	else if (y == "brown") return noColor;
	else if (y == "black") return black;
	else if (y == "white") return white;
	else if (y == "noColor" || y == " " || y == "\t") return noColor;
	else return invalidColor;
}

