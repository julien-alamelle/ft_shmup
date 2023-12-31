#include "ESplit.hpp"
#include <ncurses.h>
#include "GameState.hpp"
#include "ft_shmup.hpp"

ESplit::ESplit():Enemy() {;}
ESplit::ESplit(int x, int y, int team):Enemy(x,y,team,300,1) {;}
ESplit::ESplit(const ESplit &src):Enemy(src) {;}
ESplit::~ESplit() {;}

ESplit&	ESplit::operator=(const ESplit &src) {
	if (this == &src) return (*this);
	Enemy::operator=(src);
	return (*this);
}

bool ESplit::update() {
	if (rand()%FRAME_RATE == 0) ++(this->x);
	if (GameState::getInstance()->getTicks()%(FRAME_RATE*2) == 0) 
		this->_EntityCreator("bsplit", this->x, this->y, this->team);
	if (this->x < LINES)
		return true;
	delete this;
	return false;
}

void ESplit::print(WINDOW *win) {
	mvwaddch(win, this->x, this->y, 'T');
}
