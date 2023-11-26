#include "ESplit.hpp"
#include <ncurses.h>
#include "ft_shmup.hpp"

ESplit::ESplit():Enemy() {;}
ESplit::ESplit(int x, int y):Enemy(x,y,300,2) {;}
ESplit::ESplit(const ESplit &src):Enemy(src) {;}
ESplit::~ESplit() {;}

ESplit&	ESplit::operator=(const ESplit &src) {
	if (this == &src) return (*this);
	Enemy::operator=(src);
	return (*this);
}

bool ESplit::update() {
	if (rand()%FRAME_RATE == 0) ++(this->x);
	if (rand()%FRAME_RATE == 0) 
		this->_EntityCreator("bsplit", this->x, this->y);
	if (this->x < LINES)
		return true;
	delete this;
	return false;
}

void ESplit::print(WINDOW *win) {
	mvwaddch(win, this->x, this->y, 'T');
}
