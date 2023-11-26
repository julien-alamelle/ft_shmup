#include "EMothership.hpp"
#include <ncurses.h>
#include "ft_shmup.hpp"

EMothership::EMothership():Enemy() {;}
EMothership::EMothership(int x, int y):Enemy(x,y,500) {;}
EMothership::EMothership(const EMothership &src):Enemy(src) {;}
EMothership::~EMothership() {;}

EMothership&	EMothership::operator=(const EMothership &src) {
	if (this == &src) return (*this);
	Enemy::operator=(src);
	return (*this);
}

bool EMothership::update() {
	if (rand()%600 == 0) ++(this->x);
	if (rand()%180 == 0) 
		this->_EntityCreator("enemy", this->x, this->y);
	if (rand()%600 == 0) 
		this->_EntityCreator("e3shot", this->x, this->y);
	if (this->y < 1)
		this->y = 1;
	if (this->y > get_maxy(COLS) - 2)
		this->y = get_maxy(COLS) - 2;
	if (this->x < LINES)
		return true;
	delete this;
	return false;
}

void EMothership::print(WINDOW *win) {
	wattron(win, A_REVERSE);
	mvwaddch(win, this->x, this->y, 'W');
	wattroff(win, A_REVERSE);
}