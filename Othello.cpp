// Jack Cartwright & Raza Sandhu

#include <iostream>

#include "Othello.hpp"
#include "Player.hpp"

using namespace std;

Othello::Othello() {
	p1 = player('O');
	p2 = player('B');
	numplayers = 0;
}

Othello::Othello(string st1, char c) {
	p1 = player(st1, c);
	if (c == 'B') {
		p2 = player('O');
	}
	else {
		p2 = player('B');
	}
	numplayers = 1;
}

Othello::Othello(string st1, char c, string st2, char c2) {
	p1 = player(st1, c);
	p2 = player(st2, c2);
	numplayers = 2;
}

void Othello::makemat() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = '_';
		}
	}
	board[3][3] = 'B';
	board[4][4] = 'B';
	board[4][3] = 'O';
	board[3][4] = 'O';
}

void Othello::printmat() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (i == 0 && j % 2 == 0) {
				cout << ' ';
			}
			else if (i == 0) {
				cout << (j - 1) / 2;
			}
			else if (j == 0 && i % 2 == 0) {
				cout << ' ';
			}
			else if (j == 0) {
				cout << (i - 1) / 2;
			}
			else if (i == 15 && j % 2 == 0) {
				cout << '|';
			}
			else if (i % 2 == 0 && j % 2 == 0) {
				cout << '+';
			}
			else if (i % 2 == 1 && j % 2 == 0) {
				cout << '|';
			}
			else if (i % 2 == 0 && j % 2 == 1) {
				cout << "―";
			}
			else {
				if (board[(i + 1) / 2 - 1][(j + 1) / 2 - 1] == '_') {
					cout << ' ';
				}
				else {
					cout << board[(i + 1) / 2 - 1][(j + 1) / 2 - 1];
				}
			}
		}
		cout << endl;
	}
}

void Othello::placepiece(player p) {
	int x;
	int y;
	int notvalid = 1;
	while (notvalid) {
		cout<<"enter the x coordinate on the board: ";
		cin >> x;
		cout<<"enter the y coordinate on the board: ";
		cin >> y;
		if (x >= 0 && x <= 7 && y >= 0 && y <= 7 && board[y][x] == '_') {
			notvalid = 0;
		}
	}
	board[y][x] = p.piece;
	if (countandflippieces(x, y, p, 0) == 0) {
		cout << "Player forfeits turn" << endl;
		board[y][x] = '_';
	}
}

int Othello::countandflippieces(int x, int y, player p, int dryrun) {
	char piece = p.piece;
	int currcount = 0;
	int totalcount = 0;

	//check to the right
	if (x < 6) {
		for (int i = x + 1; i < 8 && board[y][i] != '_'; i++) {
			if (board[y][i] != piece) {
				currcount++;
			}
			else if (board[y][i] == piece) {
				totalcount += currcount;
				if (!dryrun) {
					for (int j = 1; j <= currcount; j++) {
						if (piece == 'B') {
							board[y][x + j] = 'B';
						}
						else {
							board[y][x + j] = 'O';
						}
					}	
				}
				break;
			}
		}
		currcount = 0;
	}

	//check to the left
	if (x > 1) {
		for (int i = x - 1; i >= 0 && board[y][i] != '_'; i--) {
			if (board[y][i] != piece) {
				currcount++;
			}
			else if (board[y][i] == piece) {
				totalcount += currcount;
				if (!dryrun) {
					for (int j = 1; j <= currcount; j++) {
						if (piece == 'B') {
							board[y][x - j] = 'B';
						}
						else {
							board[y][x - j] = 'O';
						}
					}
				}
				break;
			}
		}
		currcount = 0;
	}

	//check below
	if (y < 6) {
		for (int i = y + 1; i < 8 && board[i][x] != '_'; i++) {
			if (board[i][x] != piece) {
				currcount++;
			}
			else if (board[i][x] == piece) {
				totalcount += currcount;
				if (!dryrun) {
					for (int j = 1; j <= currcount; j++) {
						if (piece == 'B') {
							board[y + j][x] = 'B';
						}
						else {
							board[y + j][x] = 'O';
						}
					}	
				}
				break;
			}
		}
		currcount = 0;
	}

	//check above
	if (y > 1) {
		for (int i = y - 1; i >= 0 && board[i][x] != '_'; i--) {
			if (board[i][x] != piece) {
				currcount++;
			}
			else if (board[i][x] == piece) {
				totalcount += currcount;
				if (!dryrun) {
					for (int j = 1; j <= currcount; j++) {
						if (piece == 'B') {
							board[y - j][x] = 'B';
						}
						else {
							board[y - j][x] = 'O';
						}
					}
				}
				break;
			}
		}
		currcount = 0;
	}

	//check up and to the right
	if (x < 6 && y > 1) {
		for (int i = 1; x + i < 8 && y - i >= 0 && board[y - i][x + i] != '_'; i++) {
			if (board[y - i][x + i] != piece) {
				currcount++;
			}
			else if (board[y - i][x + i] == piece) {
				totalcount += currcount;
				if (!dryrun) {
					for (int j = 1; j <= currcount; j++) {
						if (piece == 'B') {
							board[y - j][x + j] = 'B';
						}
						else {
							board[y - j][x + j] = 'O';
						}
					}
				}
				break;
			}
		}
		currcount = 0;
	}

	//check down and to the left
	if (x > 1 && y < 6) {
		for (int i = 1; x - i >= 0 && y + i < 8 && board[y + i][x - i] != '_'; i++) {
			if (board[y + i][x - i] != piece) {
				currcount++;
			}
			else if (board[y + i][x - i] == piece) {
				totalcount += currcount;
				if (!dryrun) {
					for (int j = 1; j <= currcount; j++) {
						if (piece == 'B') {
							board[y + j][x - j] = 'B';
						}
						else {
							board[y + j][x - j] = 'O';
						}
					}
				}
				break;
			}
		}
		currcount = 0;
	}

	//check down and  to the right
	if (x < 6 && y < 6) {
		for (int i = 1; x + i < 8 && y + i < 8 && board[y + i][x + i] != '_'; i++) {
			if (board[y + i][x + i] != piece) {
				currcount++;
			}
			else if (board[y + i][x + i] == piece) {
				totalcount += currcount;
				if (!dryrun) {
					for (int j = 1; j <= currcount; j++) {
						if (piece == 'B') {
							board[y + j][x + j] = 'B';
						}
						else {
							board[y + j][x + j] = 'O';
						}
					}
				}
				break;
			}
		}
		currcount = 0;
	}
	
	//check up and to the left
	if (x > 1 && y > 1) {
		for (int i = 1; x - i >= 0 && y - i >= 0 && board[y - i][x - i] != '_'; i++) {
			if (board[y - i][x - i] != piece) {
				currcount++;
			}
			else if (board[y - i][x - i] == piece) {
				totalcount += currcount;
				if (!dryrun) {
					for (int j = 1; j <= currcount; j++) {
						if (piece == 'B') {
							board[y - j][x - j] = 'B';
						}
						else {
							board[y - j][x - j] = 'O';
						}
					}
				}
				break;
			}
		}
		currcount = 0;
	}
	
	return totalcount;
}

void Othello::ckwin() {
	int ocount = 0;
	int bcount = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 'B') {
				bcount++;
			}
			else if (board[i][j] == 'O') {
				ocount++;
			}
		}
	}
	if (bcount > ocount) {
		cout << "Black won with: " << bcount << " versus " << ocount << endl;
	}
	else if (ocount > bcount) {
		cout << "Orange won with: " << ocount << " versus " << bcount << endl;
	}
	else {
		cout << "Tie" << endl;
	}
}

void Othello::compplacepiece(player p) {
	int bestx;
	int besty;
	int bestscore = 0;
	int highscorecount = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == '_') {
				int testscore = countandflippieces(j, i, p, 1);
				if ((i == 0 || i == 7) && (j == 0 || j == 7)) {
					testscore *= 3; //value corner spaces the most
				}
				else if (i == 0 || j == 0 || i == 7 || j == 7) {
					testscore *= 2; //value edge spaces more
				}
				if (testscore > bestscore) {
					bestscore = testscore;
					highscorecount = 1;
				}
				else if (testscore == bestscore) {
					highscorecount++;
				}
			}
		}
	}
	int move = rand() % highscorecount + 1;
	highscorecount = 1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == '_') {
				int testscore = countandflippieces(j, i, p, 1);
				if ((i == 0 || i == 7) && (j == 0 || j == 7)) {
					testscore *= 3; //value corner spaces the most
				}
				else if (i == 0 || j == 0 || i == 7 || j == 7) {
					testscore *= 2; //value edge spaces more
				}
				if (testscore == bestscore && highscorecount == move) {
					bestx = j;
					besty = i;
					break;
				}	
				else if (testscore == bestscore) {
					highscorecount++;
				}
			}
		}
	}
	if (bestscore > 0) {
		board[besty][bestx] = p.piece;
		countandflippieces(bestx, besty, p, 0);
	}
}

void Othello::playGame(){
	makemat();
	printmat();
	bool play = true;
	int fullsqrs = 4;
	player p = p1;
	bool whichp = true;
	bool turn = true;
	if (rand()%2 == 0) {  // p1 plays first
		p = p2;
		turn = false;
		whichp = false;
	}
	while ((play) && (fullsqrs < 64)){
		cout << endl << p.name <<" ("<<p.piece<<") choose your square: "<<endl;
		if ((numplayers == 2) || ((numplayers == 1) && turn)){
			placepiece(p);
		}
		else if ((numplayers == 0) || ((numplayers == 1) && (turn == false))){
			compplacepiece(p);
		}
		turn = !turn;
		printmat();
		if (whichp) {
			p = p2;
			whichp = false;
		}
		else {
			p=p1;
			whichp = true;
		}
		fullsqrs+=1;
	}
	ckwin();
}
