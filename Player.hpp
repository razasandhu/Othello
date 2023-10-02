// Jack Cartwright & Raza Sandhu

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>

class player {

public:

	std::string name;
	char piece;

	player();
	player(char);
	player(std::string, char);

};



#endif /* PLAYER_HPP_ */
