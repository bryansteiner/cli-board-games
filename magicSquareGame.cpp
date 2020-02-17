// magicSquareGame.cpp

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

MagicSquareGame::MagicSquareGame()
	: dimX_c(3), dimY_c(3),
	pos_c({
	game_piece(noColor, "empty", " "),	// pos_c[0] = (0,0)
	game_piece(noColor, "empty", " "),	// pos_c[1] = (1,0)
	game_piece(noColor, "empty", " "),	// pos_c[2] = (2,0)
	game_piece(noColor, "empty", " "),	// pos_c[3] = (0,1)
	game_piece(noColor, "empty", " "),	// pos_c[4] = (1,1)
	game_piece(noColor, "empty", " "),	// pos_c[5] = (2,1)
	game_piece(noColor, "empty", " "),	// pos_c[6] = (0,2)
	game_piece(noColor, "empty", " "),	// pos_c[7] = (1,2)
	game_piece(noColor, "empty", " "),	// pos_c[8] = (2,2) 
}),
available({
	1,2,3,4,5,6,7,8,9
})
{
	restore();
}

ostream &operator<<(ostream &out, const MagicSquareGame &game) {
	// Coordinates:
	//		(0,0)			 --> lower left-hand square of the board
	//		(dimX-1, dimY-1) --> upper right-hand square of the board

	// prints out game board
	for (int j = (game.dimY_c - 1); j >= 0; j--) { // row
		out << j << " ";
		for (unsigned int i = 0; i < game.dimX_c; i++) { // column
			out << setw(game.display_length); // adjusts the widths of the squares according to the maximum display string length 
			out << game.pos_c.at(game.dimX_c*j + i).display_ << " ";
		}
		out << endl;
	}
	out << "X 0 1 2" << endl;
	out << endl;
	// prints out available pieces
	out << "Available pieces: ";
	for (unsigned int k = 0; k < game.available.size(); ++k) {
		out << game.available[k] << " ";
	}
	out << endl;
	return out;
}

unsigned int MagicSquareGame::piece2Value(string nameOrDisplay) {
	istringstream buffer(nameOrDisplay);
	int value;
	buffer >> value;
	return value;
}

unsigned int MagicSquareGame::coord2Index(unsigned int i, unsigned int j) {
	return dimX_c*j + i;
}

void MagicSquareGame::save() {
	cout << "Do you want to save the game?  Y/N : " << endl;
	string ans;
	cin >> ans;
	ofstream ofs;
	ofs.open("MagicSquare.txt");
	if (ofs.is_open()) {
		if (ans == "Y") {
			ofs << "MagicSquare" << endl;
			for (unsigned int i = 0; i < dimX_c*dimY_c; ++i) {
				ofs << pos_c[i].color_ << " " << pos_c[i].name_ << " " << pos_c[i].display_ << endl;
			}

		}
		else {
			ofs << "NO DATA" << endl;
		}
		ofs.close();
	}
	else {
		throw failure_cannot_open_file;
	}
}

void MagicSquareGame::restore() {
	vector<game_piece> board;
	ifstream ifs;
	ifs.open("MagicSquare.txt");
	string line;
	getline(ifs, line);
	if (line == "MagicSquare") {
		while (getline(ifs, line)) {
			istringstream iss(line);
			int color;
			string name;
			string display;
			if ((iss >> color) && iss >> name) {
				if (iss >> display) {
					game_piece g(piece_color(color), name, display);
					board.push_back(g);
				}
				else {
					game_piece g(piece_color(color), name, " ");
					board.push_back(g);
				}
			}
			else {
				return;
			}
		}
		if (board.size() == dimX_c*dimY_c) {
			pos_c = board;
			for (unsigned int i = 0; i < board.size(); ++i) {
				remove(available.begin(), available.end(), piece2Value(pos_c[i].name_));
			}
		}
	}
	return;
}

bool MagicSquareGame::done() {
	// check whether every square contains a piece
	regex coordinate("[[:digit:]]");
	for (unsigned int i = 0; i < dimX_c; ++i) {
		for (unsigned int j = 0; j < dimY_c; ++j) {
			if (!regex_match(pos_c[coord2Index(i, j)].display_, coordinate)) {
				return false;	// the board is not full (i.e. doesn't contain a digit at every position)
			}
		}
	}

	// check whether sum across rows, columns, and diagonals are different;
	int sumExpected = 15;
	int sumRows[3] = { 0,0,0 };
	for (unsigned int i = 0; i < dimX_c; ++i) {
		for (unsigned int j = 0; j < dimY_c; ++j) {
			sumRows[i] += piece2Value(pos_c[coord2Index(i, j)].name_);
		}
		if (sumRows[i] != sumExpected) {
			return false;
		}
	}
	int sumCols[3] = { 0,0,0 };
	for (unsigned int j = 0; j < dimY_c; ++j) {
		for (unsigned int i = 0; i < dimX_c; ++i) {
			sumCols[j] += piece2Value(pos_c[coord2Index(i, j)].name_);
		}
		if (sumCols[j] != sumExpected) {
			return false;
		}
	}
	int sumDiags[2] = { 0,0 };
	sumDiags[0] = piece2Value(pos_c[coord2Index(0, 0)].name_) + piece2Value(pos_c[coord2Index(1, 1)].name_) + piece2Value(pos_c[coord2Index(2, 2)].name_);
	sumDiags[1] = piece2Value(pos_c[coord2Index(0, 2)].name_) + piece2Value(pos_c[coord2Index(1, 1)].name_) + piece2Value(pos_c[coord2Index(2, 0)].name_);
	if (sumDiags[0] != sumExpected || sumDiags[1] != sumExpected) {
		return false;
	}
	//overwrite file since game is complete
	ofstream ofs;
	ofs.open("MagicSquare.txt");
	ofs << " " << endl;
	ofs.close();
	return true; // sums all match
}

bool MagicSquareGame::stalemate() {
	// check whether every square contains a piece
	regex coordinate("[[:digit:]]");
	for (unsigned int i = 0; i < dimX_c; ++i) {
		for (unsigned int j = 0; j < dimY_c; ++j) {
			if (!regex_match(pos_c[coord2Index(i, j)].display_, coordinate)) {
				return false;	// the board is not full (i.e. doesn't contain a digit at every position)
			}
		}
	}

	// check whether sum across rows, columns, and diagonals are different;
	int sumExpected = 15;
	int sumRows[3] = { 0,0,0 };
	for (unsigned int i = 0; i < dimX_c; ++i) {
		for (unsigned int j = 0; j < dimY_c; ++j) {
			sumRows[i] += piece2Value(pos_c[coord2Index(i, j)].name_);
		}
		if (sumRows[i] != sumExpected) {
			//overwrite file since game is complete
			ofstream ofs;
			ofs.open("MagicSquare.txt");
			ofs << " " << endl;
			ofs.close();
			return true;
		}
	}
	int sumCols[3] = { 0,0,0 };
	for (unsigned int j = 0; j < dimY_c; ++j) {
		for (unsigned int i = 0; i < dimX_c; ++i) {
			sumCols[j] += piece2Value(pos_c[coord2Index(i, j)].name_);
		}
		if (sumCols[j] != sumExpected) {
			//overwrite file since game is complete
			ofstream ofs;
			ofs.open("MagicSquare.txt");
			ofs << " " << endl;
			ofs.close();
			return true;
		}
	}
	int sumDiags[2] = { 0,0 };
	sumDiags[0] = piece2Value(pos_c[coord2Index(0, 0)].name_) + piece2Value(pos_c[coord2Index(1, 1)].name_) + piece2Value(pos_c[coord2Index(2, 2)].name_);
	sumDiags[1] = piece2Value(pos_c[coord2Index(0, 2)].name_) + piece2Value(pos_c[coord2Index(1, 1)].name_) + piece2Value(pos_c[coord2Index(2, 0)].name_);
	if (sumDiags[0] != sumExpected || sumDiags[1] != sumExpected) {
		//overwrite file since game is complete
		ofstream ofs;
		ofs.open("MagicSquare.txt");
		ofs << " " << endl;
		ofs.close();
		return true;
	}
	return false; // sums all match
}

void MagicSquareGame::prompt(unsigned int &x) {
	while (true) {
		cout << "(Type \"quit\" to end the game or enter a valid available piece \"x\")" << endl;
		string input;
		if (cin >> input) {
			if (input == "quit") {
				save();
				cout << "Looks like you quit. See ya next time!";
				throw user_request_quit;
			}
		}
		else {
			throw failure_invalid_move;
		}
		regex coordinate("[[:digit:]]");
		if (!regex_match(input, coordinate)) {
			cerr << "Badly formatted input. Does not match 1-9. Try again." << endl;
			prompt(x);
		}
		auto check = find(available.begin(), available.end(), piece2Value(input));
		if (check < available.end()) {
			if (piece2Value(input) != *check) {
				cerr << "This piece is not available. Try again." << endl;
				prompt(x);
			}
		}
		else {
			cerr << "This piece is not available. Try again." << endl;
			prompt(x);
		}

		istringstream i(input);
		if (i >> x) {
			return;
		}
		else
		{
			throw failure_cannot_extract_coordinates;
		}
	}
}

int MagicSquareGame::turn() {
	unsigned int piece;
	cout << "Enter an AVAILABLE piece:" << endl;
	MagicSquareGame::prompt(piece);

	unsigned int x, y;
	cout << "Enter an EMPTY square to place piece on" << endl;
	if (GameBase::prompt(x, y) == user_request_quit) {
		return user_request_quit;
	}
	else if (x > (dimX_c - 1) || y > (dimY_c - 1)) {
		return failure_invalid_move;
	}
	else {
		// check if piece already located at x,y
		if (pos_c.at(coord2Index(x, y)).name_ != "empty") {
			cerr << "This position already has a piece. Try again." << endl;
			return failure_invalid_move;
		}
		else { // valid move
			   // place piece on game board
			pos_c.at(coord2Index(x, y)).name_ = to_string(piece);
			pos_c.at(coord2Index(x, y)).display_ = to_string(piece);
			// remove piece from available pieces
			available.erase(find(available.begin(), available.end(), piece));
			// print out updated game board
			cout << endl;
			print();
		}
	}
	return success;
}

void MagicSquareGame::print() {
	cout << *this << endl;
}