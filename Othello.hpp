// Jack Cartwright & Raza Sandhu

#ifndef OTHELLO_HPP_
#define OTHELLO_HPP_

#include <string>
#include "Player.hpp"

using namespace std;

class Othello {

	char board[8][8];
	int size;
	player p1;
	player p2;
	int numplayers;

	void makemat();
	void printmat();
	void placepiece(player p);
	void ckwin();
	void compplacepiece(player p);
	int countandflippieces(int, int, player, int);

public:

	Othello();
	Othello(string st1, char c);
	Othello(string st1, char c, string st2, char c2);

	void playGame();

};



#endif /* OTHELLO_HPP_ */
