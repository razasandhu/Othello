// Jack Cartwright & Raza Sandhu

#include "Player.hpp"

player::player() {

}

player::player(char p) {
	name = "computer";
	piece = p;
}

player::player(std::string n, char p) {
	name = n;
	piece = p;
}
