// nineAlmondsGame.cpp

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

NineAlmondsGame::NineAlmondsGame()
	: GameBase(), dimX_b(5), dimY_b(5), pos_b({
	game_piece(noColor, "empty", " "),	// pos_b[0] = (0,0)
	game_piece(noColor, "empty", " "),	// pos_b[1] = (1,0)
	game_piece(noColor, "empty", " "),	// pos_b[2] = (2,0)
	game_piece(noColor, "empty", " "),	// pos_b[3] = (3,0)
	game_piece(noColor, "empty", " "),	// pos_b[4] = (4,0)
	game_piece(noColor, "empty", " "),	// pos_b[5] = (0,1)
	game_piece(noColor, "almond", "A"),	// pos_b[6] = (1,1)
	game_piece(noColor, "almond", "A"),	// pos_b[7] = (2,1)
	game_piece(noColor, "almond", "A"),	// pos_b[8] = (3,1)
	game_piece(noColor, "empty", " "),	// pos_b[9] = (4,1)
	game_piece(noColor, "empty", " "),	// pos_b[10] = (0,2)
	game_piece(noColor, "almond", "A"),	// pos_b[11] = (1,2)
	game_piece(noColor, "almond", "A"),	// pos_b[12] = (2,2)
	game_piece(noColor, "almond", "A"),	// pos_b[13] = (3,2)
	game_piece(noColor, "empty", " "),	// pos_b[14] = (4,2)
	game_piece(noColor, "empty", " "),	// pos_b[15] = (0,3)
	game_piece(noColor, "almond", "A"),	// pos_b[16] = (1,3)
	game_piece(noColor, "almond", "A"),	// pos_b[17] = (2,3)
	game_piece(noColor, "almond", "A"),	// pos_b[18] = (3,3)
	game_piece(noColor, "empty", " "),	// pos_b[19] = (4,3)
	game_piece(noColor, "empty", " "),	// pos_b[20] = (0,4)
	game_piece(noColor, "empty", " "),	// pos_b[21] = (1,4)
	game_piece(noColor, "empty", " "),	// pos_b[22] = (2,4)
	game_piece(noColor, "empty", " "),	// pos_b[23] = (3,4)
	game_piece(noColor, "empty", " "),	// pos_b[24] = (4,4)
})
{

	restore();
}

ostream &operator<<(ostream &out, const NineAlmondsGame &game) {
	// Coordinates:
	//		(0,0)			 --> lower left-hand square of the board
	//		(dimX-1, dimY-1) --> upper right-hand square of the board

	// prints out game board

	for (int j = (game.dimY_b - 1); j >= 0; j--) { // row
		out << j << " ";
		for (unsigned int i = 0; i < game.dimX_b; i++) { // column
			out << setw(game.display_length); // adjusts the widths of the squares according to the maximum display string length 
											  //cout << setw(game.getDisplayLength());
			out << game.pos_b.at(game.dimX_b*j + i).display_ << " ";
		}
		out << endl;
	}
	out << "X 0 1 2 3 4" << endl;
	return out;
}

unsigned int NineAlmondsGame::coord2Index(unsigned int i, unsigned int j) {
	return dimX_b*j + i;
}

void NineAlmondsGame::save() {
	cout << "Do you want to save the game?  Y/N : " << endl;
	string ans;
	cin >> ans;
	ofstream ofs;
	ofs.open("NineAlmonds.txt");
	if (ofs.is_open()) {
		if (ans == "Y") {
			ofs << "NineAlmonds" << endl;
			for (unsigned int i = 0; i < dimX_b*dimY_b; ++i) {
				ofs << pos_b[i].color_ << " " << pos_b[i].name_ << " " << pos_b[i].display_ << endl;
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

void NineAlmondsGame::restore() {
	vector<game_piece> board;
	ifstream ifs;
	ifs.open("NineAlmonds.txt");
	string line;
	getline(ifs, line);
	if (line == "NineAlmonds") {
		unsigned int count = 0;
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
		if (board.size() == dimX_b*dimY_b) {
			pos_b = board;
		}
	}
	return;
}

bool NineAlmondsGame::done() {
	if (pos_b.at(coord2Index(2, 2)).display_ == "A") {	// checks (2,2) coordinate
		for (unsigned int i = 0; i < dimX_b; ++i) {
			for (unsigned int j = 0; j < dimY_b; ++j) {
				if (i != 2 && j != 2) {
					if (pos_b.at(dimX_b*j + i).name_ == "almond") { // checks all other coordinates except (2,2)
						return false;
					}
				}
			}
		}
	}
	else {
		return false;
	}
	//overwrite file since game is complete
	ofstream ofs;
	ofs.open("NineAlmonds.txt");
	ofs << " " << endl;
	ofs.close();
	return true;
}

bool NineAlmondsGame::valid() {
	if (// valid moves for almond at (0,0)
		(pos_b.at(coord2Index(0, 0)).name_ == "almond" && pos_b.at(coord2Index(1, 0)).name_ == "almond" && pos_b.at(coord2Index(2, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 0)).name_ == "almond" && pos_b.at(coord2Index(0, 1)).name_ == "almond" && pos_b.at(coord2Index(0, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 0)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "empty") ||
		// valid moves for almond at (1,0)
		(pos_b.at(coord2Index(1, 0)).name_ == "almond" && pos_b.at(coord2Index(2, 0)).name_ == "almond" && pos_b.at(coord2Index(3, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 0)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 0)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "empty") ||
		// valid moves for almond at (2,0)
		(pos_b.at(coord2Index(2, 0)).name_ == "almond" && pos_b.at(coord2Index(1, 0)).name_ == "almond" && pos_b.at(coord2Index(0, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 0)).name_ == "almond" && pos_b.at(coord2Index(3, 0)).name_ == "almond" && pos_b.at(coord2Index(4, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 0)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 0)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(0, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 0)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(4, 2)).name_ == "empty") ||
		// valid moves for almond at (3,0)
		(pos_b.at(coord2Index(3, 0)).name_ == "almond" && pos_b.at(coord2Index(2, 0)).name_ == "almond" && pos_b.at(coord2Index(1, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 0)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 0)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "empty") ||
		// valid moves for almond at (4,0)
		(pos_b.at(coord2Index(4, 0)).name_ == "almond" && pos_b.at(coord2Index(3, 0)).name_ == "almond" && pos_b.at(coord2Index(2, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 0)).name_ == "almond" && pos_b.at(coord2Index(4, 1)).name_ == "almond" && pos_b.at(coord2Index(4, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 0)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "empty") ||

		// valid moves for almond at (0,1)
		(pos_b.at(coord2Index(0, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 1)).name_ == "almond" && pos_b.at(coord2Index(0, 2)).name_ == "almond" && pos_b.at(coord2Index(0, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "empty") ||
		// valid moves for almond at (1,1)
		(pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "empty") ||
		// valid moves for almond at (2,1)
		(pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(0, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(4, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(0, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(4, 3)).name_ == "empty") ||
		// valid moves for almond at (3,1)
		(pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "empty") ||
		// valid moves for almond at (4,1)
		(pos_b.at(coord2Index(4, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 1)).name_ == "almond" && pos_b.at(coord2Index(4, 2)).name_ == "almond" && pos_b.at(coord2Index(4, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "empty") ||

		// valid moves for almond at (0,2)
		(pos_b.at(coord2Index(0, 2)).name_ == "almond" && pos_b.at(coord2Index(0, 1)).name_ == "almond" && pos_b.at(coord2Index(0, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 2)).name_ == "almond" && pos_b.at(coord2Index(0, 3)).name_ == "almond" && pos_b.at(coord2Index(0, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 4)).name_ == "empty") ||
		// valid moves for almond at (1,2)
		(pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 4)).name_ == "empty") ||
		// valid moves for almond at (2,2)
		(pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(0, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(4, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "almond" && pos_b.at(coord2Index(0, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(0, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(4, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(4, 4)).name_ == "empty") ||
		// valid moves for almond at (3,2)
		(pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(3, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "almond" && pos_b.at(coord2Index(1, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 4)).name_ == "empty") ||
		// valid moves for almond at (4,2)
		(pos_b.at(coord2Index(4, 2)).name_ == "almond" && pos_b.at(coord2Index(4, 1)).name_ == "almond" && pos_b.at(coord2Index(4, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 2)).name_ == "almond" && pos_b.at(coord2Index(4, 3)).name_ == "almond" && pos_b.at(coord2Index(4, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "almond" && pos_b.at(coord2Index(2, 0)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 4)).name_ == "empty") ||

		// valid moves for almond at (0,3)
		(pos_b.at(coord2Index(0, 3)).name_ == "almond" && pos_b.at(coord2Index(0, 2)).name_ == "almond" && pos_b.at(coord2Index(0, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "empty") ||
		// valid moves for almond at (1,3)
		(pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "empty") ||
		// valid moves for almond at (2,3)
		(pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(0, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(4, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "almond" && pos_b.at(coord2Index(0, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(4, 1)).name_ == "empty") ||
		// valid moves for almond at (3,3)
		(pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(3, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "almond" && pos_b.at(coord2Index(1, 1)).name_ == "empty") ||
		// valid moves for almond at (4,3)
		(pos_b.at(coord2Index(4, 3)).name_ == "almond" && pos_b.at(coord2Index(4, 2)).name_ == "almond" && pos_b.at(coord2Index(4, 1)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "almond" && pos_b.at(coord2Index(2, 1)).name_ == "empty") ||

		// valid moves for almond at (0,4)
		(pos_b.at(coord2Index(0, 4)).name_ == "almond" && pos_b.at(coord2Index(0, 3)).name_ == "almond" && pos_b.at(coord2Index(0, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 4)).name_ == "almond" && pos_b.at(coord2Index(1, 4)).name_ == "almond" && pos_b.at(coord2Index(2, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(0, 4)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "empty") ||
		// valid moves for almond at (1,4)
		(pos_b.at(coord2Index(1, 4)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 4)).name_ == "almond" && pos_b.at(coord2Index(2, 4)).name_ == "almond" && pos_b.at(coord2Index(3, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(1, 4)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "empty") ||
		// valid moves for almond at (2,4)
		(pos_b.at(coord2Index(2, 4)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 4)).name_ == "almond" && pos_b.at(coord2Index(1, 4)).name_ == "almond" && pos_b.at(coord2Index(0, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 4)).name_ == "almond" && pos_b.at(coord2Index(3, 4)).name_ == "almond" && pos_b.at(coord2Index(4, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 4)).name_ == "almond" && pos_b.at(coord2Index(1, 3)).name_ == "almond" && pos_b.at(coord2Index(0, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(2, 4)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(4, 2)).name_ == "empty") ||
		// valid moves for almond at (3,4)
		(pos_b.at(coord2Index(3, 4)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(3, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 4)).name_ == "almond" && pos_b.at(coord2Index(2, 4)).name_ == "almond" && pos_b.at(coord2Index(1, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(3, 4)).name_ == "almond" && pos_b.at(coord2Index(2, 3)).name_ == "almond" && pos_b.at(coord2Index(1, 2)).name_ == "empty") ||
		// valid moves for almond at (4,4)
		(pos_b.at(coord2Index(4, 4)).name_ == "almond" && pos_b.at(coord2Index(4, 3)).name_ == "almond" && pos_b.at(coord2Index(4, 2)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 4)).name_ == "almond" && pos_b.at(coord2Index(3, 4)).name_ == "almond" && pos_b.at(coord2Index(2, 4)).name_ == "empty") ||
		(pos_b.at(coord2Index(4, 4)).name_ == "almond" && pos_b.at(coord2Index(3, 3)).name_ == "almond" && pos_b.at(coord2Index(2, 2)).name_ == "empty"))
	{
		return true;
	}
	else {
		return false;
	}
}

bool NineAlmondsGame::stalemate() {
	if (valid() || done()) {
		return false;
	}
	else {
		//overwrite file since game is complete
		ofstream ofs;
		ofs.open("NineAlmonds.txt");
		ofs << " " << endl;
		ofs.close();
		return true;
	}
}

int NineAlmondsGame::turn() {
	string moves = "";
	bool firstMove = true;

	unsigned int x1, y1;
	cout << "Enter a STARTING square:" << endl;
	if (prompt(x1, y1) == user_request_quit) {
		return user_request_quit;
	}
	else if (x1 > (dimX_b - 1) || y1 > (dimY_b - 1)) {
		return failure_invalid_move;
	}
	else {
		// check if almond located at (x1,y1)
		if (pos_b.at(coord2Index(x1, y1)).name_ == "almond") {
			while (true) {
				unsigned int x2, y2;
				cout << "Enter an ENDING square:" << endl;
				if (prompt(x2, y2) == user_request_quit) {
					return user_request_quit;
				}
				else {
					int deltaX = (int)x2 - (int)x1;
					int deltaY = (int)y2 - (int)y1;
					// check if (x1,y1) and (x2,y2) are 2 positions away from each other
					if ((abs(deltaX) == 2 && abs(deltaY) == 2) || (abs(deltaX) == 2 && abs(deltaY) == 0) || (abs(deltaX) == 0 && abs(deltaY) == 2)) {
						// check if empty located at (x2,y2)
						if (pos_b.at(coord2Index(x2, y2)).name_ == "empty") {
							// check if almond located between (x1,y1) and (x2,y2)
							if (pos_b.at(coord2Index(x1 + (deltaX / 2), y1 + (deltaY / 2))).name_ == "almond") {
								// make starting square empty
								pos_b.at(coord2Index(x1, y1)).color_ = noColor;
								pos_b.at(coord2Index(x1, y1)).name_ = "empty";
								pos_b.at(coord2Index(x1, y1)).display_ = " ";
								// make jumped over square empty 
								pos_b.at(coord2Index(x1 + (deltaX / 2), y1 + (deltaY / 2))).color_ = noColor;
								pos_b.at(coord2Index(x1 + (deltaX / 2), y1 + (deltaY / 2))).name_ = "empty";
								pos_b.at(coord2Index(x1 + (deltaX / 2), y1 + (deltaY / 2))).display_ = " ";
								// make ending square alomnd
								pos_b.at(coord2Index(x2, y2)).color_ = noColor;
								pos_b.at(coord2Index(x2, y2)).name_ = "almond";
								pos_b.at(coord2Index(x2, y2)).display_ = "A";
								// prints out updated game board and moves so far
								cout << endl;
								cout << *this << endl;

								if (firstMove) {
									moves = to_string(x1) + "," + to_string(y1) + " to " + to_string(x2) + "," + to_string(y2);
									firstMove = false;
								}
								else {
									moves += " to " + to_string(x2) + "," + to_string(y2);
								}
								cout << moves << endl;
								// make another move
								cout << "Continue this turn (y/n)?" << endl;
								string ans;
								cin >> ans;
								if (ans == "y") {
									x1 = x2;
									y1 = y2;
								}
								else {
									return success;
								}
							}
							else {
								return failure_invalid_move; // invalid move (no almond to jump over)
							}
						}
						else {
							return failure_invalid_move; // invalid move (no empty at destination)
						}
					}
					else {
						return failure_invalid_move; // invalid move (not two positions away)
					}
				}
			}
		}
		else {
			return failure_invalid_move; // invalid move (no almond at specified position)
		}
	}
}

void NineAlmondsGame::print() {
	cout << *this << endl;
};