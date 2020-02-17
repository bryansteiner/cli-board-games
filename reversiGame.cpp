// reversiGame.cpp

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

ReversiGame::ReversiGame(string name1, string name2)
	: dimX_d(8), dimY_d(8), player1(name1), player2(name2), myTurn(true),
	pos_d({
	game_piece(noColor, "empty", " "),	// pos_d[0] = (0,0)
	game_piece(noColor, "empty", " "),	// pos_d[1] = (1,0)
	game_piece(noColor, "empty", " "),	// pos_d[2] = (2,0)
	game_piece(noColor, "empty", " "),	// pos_d[3] = (3,0)
	game_piece(noColor, "empty", " "),	// pos_d[4] = (4,0)
	game_piece(noColor, "empty", " "),	// pos_d[5] = (5,0)
	game_piece(noColor, "empty", " "),	// pos_d[6] = (6,0)
	game_piece(noColor, "empty", " "),	// pos_d[7] = (7,0)
	game_piece(noColor, "empty", " "),	// pos_d[8] = (0,1) 
	game_piece(noColor, "empty", " "),	// pos_d[9] = (1,1)
	game_piece(noColor, "empty", " "),	// pos_d[10] = (2,1)
	game_piece(noColor, "empty", " "),	// pos_d[11] = (3,1)
	game_piece(noColor, "empty", " "),	// pos_d[12] = (4,1)
	game_piece(noColor, "empty", " "),	// pos_d[13] = (5,1)
	game_piece(noColor, "empty", " "),	// pos_d[14] = (6,1)
	game_piece(noColor, "empty", " "),	// pos_d[15] = (7,1)
	game_piece(noColor, "empty", " "),	// pos_d[16] = (0,2)
	game_piece(noColor, "empty", " "),	// pos_d[17] = (1,2) 
	game_piece(noColor, "empty", " "),	// pos_d[18] = (2,2)
	game_piece(noColor, "empty", " "),	// pos_d[19] = (3,2)
	game_piece(noColor, "empty", " "),	// pos_d[20] = (4,2)
	game_piece(noColor, "empty", " "),	// pos_d[21] = (5,2)
	game_piece(noColor, "empty", " "),	// pos_d[22] = (6,2)
	game_piece(noColor, "empty", " "),	// pos_d[23] = (7,2)
	game_piece(noColor, "empty", " "),	// pos_d[24] = (0,3)
	game_piece(noColor, "empty", " "),	// pos_d[25] = (1,3)
	game_piece(noColor, "empty", " "),	// pos_d[26] = (2,3) 
	game_piece(black, "black", "X"),	// pos_d[27] = (3,3)
	game_piece(white, "white", "O"),	// pos_d[28] = (4,3) 
	game_piece(noColor, "empty", " "),	// pos_d[29] = (5,3)
	game_piece(noColor, "empty", " "),	// pos_d[30] = (6,3)
	game_piece(noColor, "empty", " "),	// pos_d[31] = (7,3)
	game_piece(noColor, "empty", " "),	// pos_d[32] = (0,4)
	game_piece(noColor, "empty", " "),	// pos_d[33] = (1,4)
	game_piece(noColor, "empty", " "),	// pos_d[34] = (2,4)
	game_piece(white, "white", "O"),	// pos_d[35] = (3,4)
	game_piece(black, "black", "X"),	// pos_d[36] = (4,4) 
	game_piece(noColor, "empty", " "),	// pos_d[37] = (5,4)
	game_piece(noColor, "empty", " "),	// pos_d[38] = (6,4)
	game_piece(noColor, "empty", " "),	// pos_d[39] = (7,4)
	game_piece(noColor, "empty", " "),	// pos_d[40] = (0,5)
	game_piece(noColor, "empty", " "),	// pos_d[41] = (1,5)
	game_piece(noColor, "empty", " "),	// pos_d[42] = (2,5)
	game_piece(noColor, "empty", " "),	// pos_d[43] = (3,5)
	game_piece(noColor, "empty", " "),	// pos_d[44] = (4,5) 
	game_piece(noColor, "empty", " "),	// pos_d[45] = (5,5)
	game_piece(noColor, "empty", " "),	// pos_d[46] = (6,5)
	game_piece(noColor, "empty", " "),	// pos_d[47] = (7,5)
	game_piece(noColor, "empty", " "),	// pos_d[48] = (0,6)
	game_piece(noColor, "empty", " "),	// pos_d[49] = (1,6)
	game_piece(noColor, "empty", " "),	// pos_d[50] = (2,6)
	game_piece(noColor, "empty", " "),	// pos_d[51] = (3,6) 
	game_piece(noColor, "empty", " "),	// pos_d[52] = (4,6)
	game_piece(noColor, "empty", " "),	// pos_d[53] = (5,6)
	game_piece(noColor, "empty", " "),	// pos_d[54] = (6,6)
	game_piece(noColor, "empty", " "),	// pos_d[55] = (7,6)
	game_piece(noColor, "empty", " "),	// pos_d[56] = (0,7)
	game_piece(noColor, "empty", " "),	// pos_d[57] = (1,7)
	game_piece(noColor, "empty", " "),	// pos_d[58] = (2,7)
	game_piece(noColor, "empty", " "),	// pos_d[59] = (3,7) 
	game_piece(noColor, "empty", " "),	// pos_d[60] = (4,7)
	game_piece(noColor, "empty", " "),	// pos_d[61] = (5,7)
	game_piece(noColor, "empty", " "),	// pos_d[62] = (6,7)
	game_piece(noColor, "empty", " "),	// pos_d[63] = (7,7)
})
{
	restore();
}

unsigned int ReversiGame::coord2Index(unsigned int i, unsigned int j) {
	return dimX_d*j + i;
}

ostream &operator<<(ostream &out, const ReversiGame &game) {
	// Coordinates:
	//		(0,0)			 --> lower left-hand square of the board
	//		(dimX-1, dimY-1) --> upper right-hand square of the board

	// prints out game board

	for (int j = (game.dimY_d - 1); j >= 0; j--) { // row
		out << j << " ";
		for (unsigned int i = 0; i < game.dimX_d; i++) { // column
			out << setw(game.display_length); // adjusts the widths of the squares according to the maximum display string length 
											  //cout << setw(game.getDisplayLength());
			out << game.pos_d.at(game.dimX_d*j + i).display_ << " ";
		}
		out << endl;
	}
	out << "X 0 1 2 3 4 5 6 7" << endl;
	return out;
}

void ReversiGame::save() {
	cout << "Do you want to save the game?  Y/N : " << endl;
	string ans;
	cin >> ans;
	ofstream ofs;
	ofs.open("Reversi.txt");
	if (ofs.is_open()) {
		if (ans == "Y") {
			ofs << "Reversi" << endl;
			ofs << myTurn << endl;
			ofs << player1 << endl;
			ofs << player2 << endl;
			for (unsigned int i = 0; i < dimX_d*dimY_d; ++i) {
				ofs << pos_d[i].color_ << " " << pos_d[i].name_ << " " << pos_d[i].display_ << endl;
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

void ReversiGame::restore() {
	vector<game_piece> board;
	ifstream ifs;
	ifs.open("Reversi.txt");
	string line;
	getline(ifs, line);
	if (line == "Reversi") {
		getline(ifs, line);
		if (line == "1") {
			myTurn = true;
		}
		else if (line == "0") {
			myTurn = false;
		}
		else {
			return;
		}
		getline(ifs, line);
		player1 = line;
		getline(ifs, line);
		player2 = line;
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
		if (board.size() == dimX_d*dimY_d) {
			pos_d = board;
		}
	}
	return;
}

bool ReversiGame::done() {
	// check whether all pieces on board are of the same color
	bool allSame = true;
	piece_color color = red;
	for (unsigned int i = 0; i < dimX_d; ++i) {
		for (unsigned int j = 0; j < dimY_d; ++j) {
			if (color == red && pos_d[coord2Index(i, j)].color_ != noColor) {
				color = pos_d[coord2Index(i, j)].color_;
			}
			if (color != red && pos_d[coord2Index(i, j)].color_ != color && pos_d[coord2Index(i, j)].color_ != noColor) {
				allSame = false;
				break;
			}
		}
	}
	if (allSame) {
		//overwrite file since game is complete
		ofstream ofs;
		ofs.open("Reversi.txt");
		ofs << " " << endl;
		ofs.close();
		return true;
	}
	// check whether there are more pieces of one color than another color and:
	//		a) all squares are filled
	//		b) no remaining moves for either player
	bool boardFull = true;
	for (unsigned int i = 0; i < dimX_d; ++i) {
		for (unsigned int j = 0; j < dimY_d; ++j) {
			if (pos_d[coord2Index(i, j)].color_ == noColor) {
				boardFull = false;
				break;
			}
		}
	}
	if (boardFull || valid() != success) {
		int blackCount = 0;
		int whiteCount = 0;
		for (unsigned int i = 0; i < dimX_d; ++i) {
			for (unsigned int j = 0; j < dimY_d; ++j) {
				if (pos_d[coord2Index(i, j)].color_ == black) {
					++blackCount;
				}
				else if (pos_d[coord2Index(i, j)].color_ == white) {
					++whiteCount;
				}
			}
		}
		if (blackCount != whiteCount) {
			string winner = blackCount > whiteCount ? player1 : player2;
			cout << winner << " WINS!" << endl;
			//overwrite file since game is complete
			ofstream ofs;
			ofs.open("Reversi.txt");
			ofs << " " << endl;
			ofs.close();
			return true;
		}
	}
	return false;
}

int ReversiGame::valid() {
	for (unsigned int i = 0; i < dimX_d; ++i) {
		for (unsigned int j = 0; j < dimY_d; ++j) {
			if (pos_d[coord2Index(i, j)].color_ == noColor) {
				if (isLegal(i, j).size() > 0) {
					return success;
				}
			}
		}
	}
	return no_valid_moves_one;
}

void ReversiGame::print() {
	cout << *this << endl;
}

bool ReversiGame::stalemate() {
	// check whether every square contains a piece
	if (valid() == success || done()) {
		return false; 
	}
	if (valid() == no_valid_moves_one) {
		myTurn = !myTurn;		// check if other player also has no moves
		if (valid() == no_valid_moves_one) {
			//overwrite file since game is complete
			ofstream ofs;
			ofs.open("Reversi.txt");
			ofs << " " << endl;
			ofs.close();
			return true;
		}
		myTurn = !myTurn;
	}
	return false;
}

vector<pair<unsigned int, unsigned int>> ReversiGame::isLegal(unsigned int x, unsigned int y) {
	vector<pair<unsigned int, unsigned int>> ends;
	if (x >= 0 && x < dimX_d && y >= 0 && y < dimY_d) {
		if (pos_d[coord2Index(x, y)].color_ == noColor) {
			bool neighbor = false;
			vector<pair<unsigned int, unsigned int>> coords;
			piece_color myColor = myTurn ? black : white;	// player 1 (myturn) is black
			piece_color otherColor = myTurn ? white : black;
			game_piece g = myTurn ? game_piece(black, "black", "X") : game_piece(white, "white", "O");

			// check for neighbor of opposite color
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					if (i == 0 && j == 0) {	// piece itself
						continue;
					}
					if (x + i < 0 || x + i >= dimX_d || y + j < 0 || y + j >= dimY_d) { // out of bounds
						continue;
					}
					if (pos_d[coord2Index(x + i, y + j)].color_ == otherColor) { // bordering neighbors
						neighbor = true;
						coords.push_back(make_pair(x + i, y + j));
					}
				}
			}

			if (neighbor) {
				//check for same color on other side 
				if (coords.size() > 0) {
					for (auto &xy : coords) {
						unsigned int i = xy.first;
						unsigned int j = xy.second;
						int xdiff = i - x;
						int ydiff = j - y;
						while (i >= 0 && i < dimX_d && j >= 0 && j < dimY_d) {
							if (pos_d[coord2Index(i, j)].color_ == myColor) {
								ends.push_back(make_pair(i, j));
								break;
							}
							else if (pos_d[coord2Index(i, j)].color_ == noColor) {
								break;
							}
							i += xdiff;
							j += ydiff;
						}
					}
				}
			}
			else {
				// cout << "no neighbors of opposite color" << endl;
			}
		}
		else {
			cout << "already occupied." << endl;
		}
	}
	else {
		cout << "out of range." << endl;
	}
	return ends;
}

int ReversiGame::turn() {
	game_piece g(noColor, "empty", " ");
	if (myTurn) { // player1
		cout << player1 << ", it's your turn. You are X" << endl;
		g = game_piece(black, "black", "X");
	}
	else { // player2
		cout << player2 << ", it's your turn. You are O" << endl;
		g = game_piece(white, "white", "O");
	}

	if (stalemate()) {
		// cout << "Stalemate!" << endl;
		return failure_stalemate;
	}
	unsigned int x;
	unsigned int y;
	int isValid = valid();
	if (isValid == no_valid_moves_one) {
		cout << "You have no possible legal moves, so we're skipping your turn." << endl;
		myTurn = !myTurn;
		return success;
	}
	else if (isValid == no_valid_moves_both) {
		cout << "(game should end)" << endl;
		return no_valid_moves_both;
	}
	else {
		while (true) {
			int result = prompt(x, y);
			if (result == success) {
				vector<pair<unsigned int, unsigned int>> ends = isLegal(x, y);
				if (ends.size() > 0) {		// flip all the necessary tiles
					for (auto &end : ends) {
						unsigned int i = x;
						unsigned int j = y;
						int xdiff = end.first - x;
						xdiff = xdiff > 0 ? 1 : xdiff < 0 ? -1 : 0;		// formula for sgn from stackoverflow
						int ydiff = end.second - y;
						ydiff = ydiff > 0 ? 1 : ydiff < 0 ? -1 : 0;
						while (i != end.first || j != end.second) {
							i += xdiff;
							j += ydiff;
							pos_d[coord2Index(i, j)] = g;
						}
					}
					pos_d[coord2Index(x, y)] = g;
					break;
				}
				else {
					cout << "That's an illegal move! Try again." << endl;
				}
			}
			else { // if they quit for example
				return result;
			}
		}
	}


	print();
	myTurn = !myTurn;
	return success;
}

int ReversiGame::prompt(unsigned int &x, unsigned int &y) {
	while (true) {
		cout << "(Type \"quit\" to end the game or enter a valid starting square \"x,y\")" << endl;
		string input;
		if (cin >> input) {
			if (input == "quit") {
				return user_request_quit;
			}
		}
		else {
			return failure_invalid_move;
		}
		regex coordinate("[[:digit:]],[[:digit:]]");
		if (!regex_match(input, coordinate)) {
			return failure_invalid_move;
		}
		input.replace(input.find(","), 1, " ");
		istringstream i(input);
		if (i >> x && i >> y) {
			if (x >= dimX_d || y >= dimY_d) {
				cout << "Please pick a square in the range [0,7],[0,7]." << endl;
			}
			else {
				if (pos_d[coord2Index(x, y)].color_ != noColor) {
					cerr << "That square is not available! Please select an open square." << endl;
				}
				else {
					return success;
				}
			}
		}
		else
		{
			return failure_cannot_extract_coordinates;
		}
	}
}
