*****************Grading**************
graded by: Jon Shidal
Grade: 98/100
deductions:
-2 poor modularity, should separate out header files

*************************************

========================================================================
	Project:	lab4
	Name:		Bryan Steiner, Elie Schramm, Ashley Shin
	Class:		CSE 332
========================================================================
Collaboration:
	Each of us as group members contributed about exactly evenly to this lab. We did all the work together
	on a single computer. Everyone was involved in the coding process but beyond that:
		Bryan was responsible for debugging.
		Elie was responsible for all the various trials.
		Ashley was responsible for the README.txt.
		
Files:
	Lab4.h			- Lab 4 Header file
	lab4.cpp		- Lab 4 Source file
	GameBase.h		- Game Base Header file
	GameBase.cpp		- Game Base Sourcefile
	GamePiece.h		- Game Piece Header file
	gamePiece.cpp		- Game Piece Source file
	nineAlmondsGame.cpp	- Nine Almonds Game Source file
	magicSquareGame.cpp 	- Magic Square Game Source file
	reversiGame.cpp		- Reversi Game Source file

Copy Control Design Decisions:

	GameBase:
		Copy constructor-
			1. We allowed use of copy constructor but did not implement it on our own.
			2. We initialize a shared pointer to a GameBase object but never need to copy it.
			3. We let compiler synthesize constructor if necessary (by not doing anything).
		Move constructor-
			1. We allowed use of move constructor but did not implement it on our own.
			2. We did not need to pass any copies of objects by r-value reference.
			3. We let compiler synthesize constructor if necessary (by not doing anything).
		Copy-assignment operator-
			1. We allowed use of copy-assignment operator even though we didn't use it for this class.
			2. We had no need to overload this operator.
			3. We let compiler use default definition of operator.
		Move-assignment operator-
			1. We allowed use of move-assignment operator but did not use it on our own.
			2. We had no need to overload this operator.
			3. We let compiler use default definition of operator.
		Destructor-
			1. We did not overload the destructor, so it is allowed. 
			2. The default destructor does what we need and it is necessary to have.
			3. We let compiler synthesize destructor so it is not prevented. 

	NineAlmonds:
		Copy constructor-
			1. We allowed use of copy construction but did not implement it on our own.
			2. We only needed to construct one NineAlmonds object for our game.
			3. We did not end the declaration with delete (let compiler synthesize constructor if necessary).
		Move constructor-
			1. We allowed use of move constructor but did not implement it on our own.
			2. We did not need to pass any copies of objects by r-value reference.
			3. We let compiler synthesize constructor if necessary (by not doing anything).
		Copy-assignment operator-
			1. We allowed use of copy-assignment operator even though we didn't use it for this class.
			2. We had no need to overload this operator.
			3. We let compiler use default definition of operator.
		Move-assignment operator-
			1. We allowed use of move-assignment operator but did not use it on our own.
			2. We had no need to overload this operator.
			3. We let compiler use default definition of operator.
		Destructor-
			1. We did not overload the destructor, so it is allowed. 
			2. The default destructor does what we need and it is necessary to have.
			3. We let compiler synthesize destructor so it is not prevented. 

	MagicSquare:
		Copy constructor-
			1. We allowed use of copy construction but did not implement it on our own.
			2. We only needed to construct one MagicSquare object for our game.
			3. We did not end the declaration with delete (let compiler synthesize constructor if necessary).
		Move constructor-
			1. We allowed use of move constructor but did not implement it on our own.
			2. We did not need to pass any copies of objects by r-value reference.
			3. We let compiler synthesize constructor if necessary (by not doing anything).
		Copy-assignment operator-
			1. We allowed use of copy-assignment operator even though we didn't use it for this class.
			2. We had no need to overload this operator.
			3. We let compiler use default definition of operator.
		Move-assignment operator-
			1. We allowed use of move-assignment operator but did not use it on our own.
			2. We had no need to overload this operator.
			3. We let compiler use default definition of operator.
		Destructor-
			1. We did not overload the destructor, so it is allowed. 
			2. The default destructor does what we need and it is necessary to have.
			3. We let compiler synthesize destructor so it is not prevented. 

	Reversi:
		Copy constructor-
			1. We allowed use of copy construction but did not implement it on our own.
			2. We only needed to construct one Reversi object for our game.
			3. We did not end the declaration with delete (let compiler synthesize constructor if necessary).
		Move constructor-
			1. We allowed use of move constructor but did not use it on our own.
			2. We did not need to pass any copies of objects by r-value reference.
			3. We let compiler synthesize constructor if necessary (by not doing anything).
		Copy-assignment operator-
			1. We allowed use of copy-assignment operator even though we didn't use it for this class.
			2. We had no need to overload this operator.
			3. We let compiler use default definition of operator.
		Move-assignment operator-
			1. We allowed use of move-assignment operator but did not use it on our own.
			2. We had no need to overload this operator.
			3. We let compiler use default definition of operator.
		Destructor-
			1. We did not overload the destructor, so it is allowed. 
			2. The default destructor does what we need and it is necessary to have.
			3. We let compiler synthesize destructor so it is not prevented. 

Save/Restore Design Decisions:

	When the user asks to quit, we ask if they would like to save the game. If so, we write "Reversi" followed by 
	a bool for whose turn it is and the names of the two players. After that we write the necessary info to construct 
	each game_piece in order, as before. If not, we just write "NO DATA" in the eponymous text file. 
	For restoring, if the file starts with "Reversi" then we start reading in the data that is there. We add construct 
	the game_pieces and add them to a temporary vector. If the length of the vector is the same as the dimensions say 
	it should be (i.e. correct number of pieces) then we replace the board vector with that vector.s
	
Errors/Warnings: 

	1. We had an issue where we flipped the pieces in the isLegal() method instead of as a result of the isLegal() method

	2. We had a signed, unsigned conversion issue that we corrected.

Cases:

	1.	INCORRECT COMMAND LINE ARGUMENTS

		Input-
			lab3.exe Reversi
		Output-
			lab4.exe Reversi
			Please run the program as follows:
			Usage: lab4.exe gameName player1 player2
				 * list names only for multiplayer game
		Returns-
			1 (i.e. failure_command_line_arguments)

	2.	QUIT GAME (SAVE + RESTORE)

		Input-
			lab4.exe Reversi Elie Bryan
			...
		Output-
			7
			6   X O
			5     O X X
			4     O O O O
			3       X X O
			2         X O
			1
			0
			X 0 1 2 3 4 5 6 7

			10 move(s) made
			Elie, it's your turn. You are X
			(Type "quit" to end the game or enter a valid starting square "x,y")
		Input-
			quit
		Output-
			Looks like you quit. You made 10 moves.
			Do you want to save the game?  Y/N :
		Input-
			Y
			lab4.exe Reversi Elie Bryan
		Output-
			7
			6   X O
			5     O X X
			4     O O O O
			3       X X O
			2         X O
			1
			0
			X 0 1 2 3 4 5 6 7

			Elie, it's your turn. You are X
			(Type "quit" to end the game or enter a valid starting square "x,y")
			...

	3.	BADLY FORMATTED INPUT --> TRY AGAIN
		
		Input-
			lab4.exe Reversi Elie Bryan
		Output-
			7
			6
			5
			4       O X
			3       X O
			2
			1
			0
			X 0 1 2 3 4 5 6 7

			Elie, it's your turn. You are X
			(Type "quit" to end the game or enter a valid starting square "x,y")
		Input-
			8 8
			Badly formatted input. Does not match "x,y". Try again.
			You've made an invalid move!

			Elie, it's your turn. You are X
			(Type "quit" to end the game or enter a valid starting square "x,y")
			...

	4.	INVALID MOVE --> TRY AGAIN
		
		Input-
			lab4.exe Reversi Elie Bryan
		Output-
			7
			6
			5
			4       O X
			3       X O
			2
			1
			0
			X 0 1 2 3 4 5 6 7

			Elie, it's your turn. You are X
			(Type "quit" to end the game or enter a valid starting square "x,y")
			0,0
			That's an illegal move! Try again.
			(Type "quit" to end the game or enter a valid starting square "x,y")

	5.	STALEMATE (*ALTERED SAVE FILE)

		Input-
			Reversi Elie Bryan 
		Output-
			7
			6
			5
			4       O
			3
			2
			1   X
			0
			X 0 1 2 3 4 5 6 7

			Elie, it's your turn. You are X
			Oh no! There's a stalemate! No valid moves remain. You made 1 moves.
		Returns-
			9 (i.e failure_stalemate)

	6.	DONE (PLAYER 1 WINS)

		Input-
			lab4.exe Reversi Elie Bryan
			...
			1,6
		Output-
			7
			6   X
			5     X X X X
			4       X X X
			3       X X X
			2           X
			1           X
			0
			X 0 1 2 3 4 5 6 7

			Congrats! It took you 9 moves to finish.
		Returns-
			0 (i.e. success)

	7.	DONE (PLAYER 2 WINS)

		Input-
			lab4.exe Reversi Elie Bryan
			...
		Output-
			Bryan, it's your turn. You are O
			(Type "quit" to end the game or enter a valid starting square "x,y")
		Input-
			7,6
		Output-
			7 X X X X O O O
			6 O O O O O O O O
			5   O X O X X O O
			4 O O X X O O X O
			3 O O X X O O X O
			2 O O O O O X O O
			1 O O O X X O O O
			0 O O O O O O O O
			X 0 1 2 3 4 5 6 7

			58 move(s) made
			Elie, it's your turn. You are X
			(Type "quit" to end the game or enter a valid starting square "x,y")
		Input-
			7,7
			7 X X X X X X X X
			6 O O O O O O X O
			5   O X O X X O O
			4 O O X X O O X O
			3 O O X X O O X O
			2 O O O O O X O O
			1 O O O X X O O O
			0 O O O O O O O O
			X 0 1 2 3 4 5 6 7

			Bryan WINS!
			Congrats! It took you 59 moves to finish.
		Returns-
			0 (i.e. success)