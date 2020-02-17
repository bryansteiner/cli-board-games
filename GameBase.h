#pragma once

#ifndef GAME_BASE
#define GAME_BASE

class GameBase {
public:
	GameBase();	// default constructor
	static shared_ptr<GameBase> instance();
	size_t getDisplayLength();
	int play();
	static void checkArguments(int argc, char *argv[]);
	virtual void save() = 0;
	virtual void restore() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int prompt(unsigned int &x, unsigned int &y);
	virtual int turn() = 0;
	virtual void print() = 0;
protected:
	unsigned int dimX_a;
	unsigned int dimY_a;
	vector<game_piece> pos_a;
	unsigned int display_length;
	static shared_ptr<GameBase> ptr;
};

class NineAlmondsGame : public GameBase {
public:
	NineAlmondsGame();	// default constructor
	friend ostream &operator<<(ostream &out, const NineAlmondsGame &game);	// insertion operator
	unsigned int coord2Index(unsigned int i, unsigned int j);
	virtual void save();
	virtual void restore();
	virtual bool done();
	bool valid();
	virtual bool stalemate();
	virtual int turn();
	virtual void print();
protected:
	unsigned int dimX_b;
	unsigned int dimY_b;
	vector<game_piece> pos_b;
};

class MagicSquareGame : public GameBase {
public:
	MagicSquareGame();	// default constructor
	friend ostream &operator<<(ostream &out, const MagicSquareGame &game);	// insertion operator
	unsigned int piece2Value(string nameOrDisplay);
	unsigned int coord2Index(unsigned int i, unsigned int j);
	virtual void save();
	virtual void restore();
	virtual bool done();
	virtual bool stalemate();
	virtual void prompt(unsigned int &x);
	virtual int turn();
	virtual void print();
protected:
	unsigned int dimX_c;
	unsigned int dimY_c;
	vector<game_piece> pos_c;
	vector<int> available;
};

class ReversiGame : public GameBase {
public:
	ReversiGame(string name1, string name2);	// default constructor
	friend ostream &operator<<(ostream &out, const ReversiGame &game);	// insertion operator
	unsigned int coord2Index(unsigned int i, unsigned int j);
	vector<pair<unsigned int, unsigned int>> isLegal(unsigned int x, unsigned int y);
	virtual void save();
	virtual void restore();
	virtual bool done();
	int valid();
	virtual bool stalemate();
	virtual int prompt(unsigned int &x, unsigned int &y);
	virtual int turn();
	virtual void print();
protected:
	unsigned int dimX_d;
	unsigned int dimY_d;
	vector<game_piece> pos_d;
	string player1;
	string player2;
	bool myTurn;
};

#endif /* GAME_BASE */