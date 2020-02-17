// gameBase.cpp

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>	
#include <string>	
#include <vector>
#include <algorithm> 
#include <regex>
#include <iomanip>	 // std::setw
#include <memory>	 // shared_ptr

using namespace std;
#include "Lab4.h"
#include "GamePiece.h"
#include "GameBase.h"

GameBase::GameBase()
	: dimX_a(), dimY_a(), pos_a(), display_length()
{}

shared_ptr<GameBase> GameBase::instance() {
	if (GameBase::ptr != nullptr) {
		return GameBase::ptr;
	}
	throw nullpointer_exception;
}

size_t GameBase::getDisplayLength()
{
	size_t maxLength = 0;
	for (unsigned int i = 0; i < pos_a.size(); ++i) {
		if (maxLength < pos_a[i].display_.length()) {
			maxLength = pos_a[i].display_.length();
		}
	}
	return maxLength;
}

int GameBase::play() {
	print();
	int numTurns = 0;
	while (true) {
		int result = turn();
		numTurns++;
		if (done()) {
			cout << "Congrats! It took you " << numTurns << " moves to finish." << endl;;
			return success;
		}
		else if (stalemate()) {
			cout << "Oh no! There's a stalemate! No valid moves remain. You made " << numTurns << " moves." << endl;
			return failure_stalemate;
		}
		else if (result == failure_invalid_move) {
			numTurns--;
			cout << "You've made an invalid move!" << endl;
			cout << endl;
		}
		else if (result == success) {
			cout << numTurns << " move(s) made" << endl;
		}
		else {
			numTurns--;
			cout << "Looks like you quit. You made " << numTurns << " moves." << endl;
			save();
			return user_request_quit;
		}
	}
}

void GameBase::checkArguments(int argc, char *argv[]) {
	// check that exactly one argument has been passed (i.e. "NineAlmondsGame")
	if (GameBase::ptr != nullptr) {
		throw overwrite_instance;
	}

	if (argc > 4 || argc == 1) {	// incorrect
		throw failure_command_line_arguments;
	}
	else {
		if (!strcmp(argv[gameName], "NineAlmonds")) {
			GameBase::ptr = make_shared<NineAlmondsGame>();
		}
		else if (!strcmp(argv[gameName], "MagicSquare")) {
			GameBase::ptr = make_shared<MagicSquareGame>();
		}
		else if (!strcmp(argv[gameName], "Reversi")) {
			if (argc != 4) {
				throw failure_command_line_arguments;
			}
			string name1 = argv[2];
			string name2 = argv[3];
			GameBase::ptr = make_shared<ReversiGame>(name1, name2);
		}
		else {
			throw incorrect_name;
		}
	}
}

int GameBase::prompt(unsigned int &x, unsigned int &y) {
	while (true) {
		cout << "(Type \"quit\" to end the game or enter a valid coordinate \"x,y\")" << endl;
		string input;
		if (cin >> input) {
			if (input == "quit") {
				return user_request_quit;
			}
		}
		else {
			return failure_invalid_move;
		}

		// utilized the following: https://solarianprogrammer.com/2011/10/12/cpp-11-regex-tutorial/
		regex coordinate("[[:digit:]],[[:digit:]]");
		if (!regex_match(input, coordinate)) {
			cerr << "Badly formatted input. Does not match \"x,y\". Try again." << endl;
			return failure_invalid_move;
		}
		input.replace(input.find(","), 1, " ");
		istringstream i(input);
		if (i >> x && i >> y) {
			return success;
		}
		else
		{
			return failure_cannot_extract_coordinates;
		}
	}
}

shared_ptr<GameBase> GameBase::ptr = nullptr;