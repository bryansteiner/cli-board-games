B// lab4.cpp : Defines the entry point for the console application.

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

int usage(const string &name, const string info) {
	cout << info << endl;
	cout << "Usage: ";
	// iterate through file name and print out each character
	for (auto c : name) {
		cout << c;
	}
	cout << " gameName player1 player2" << endl;
	cout << "	* list names only for multiplayer game" << endl;
	return failure_command_line_arguments;
}

int main(int argc, char *argv[])
{
	try {
		GameBase::checkArguments(argc, argv);
		auto sp = GameBase::instance();

		if (sp == nullptr || (strcmp(argv[gameName], "NineAlmonds") && strcmp(argv[gameName], "MagicSquare") && strcmp(argv[gameName], "Reversi"))) {
			string programInfo = "Please run the program as follows:";
			usage(argv[programName], programInfo);
		}
		else {
			return sp->play();
		}
	}
	catch (flags e) {
		if (e == failure_command_line_arguments || e == incorrect_name) {
			string programInfo = "Please run the program as follows:";
			return usage(argv[programName], programInfo);
		}
		else return e;
	}
	catch (...) {
		return failure_bad_alloc_exception;
	}
	return success;
}

