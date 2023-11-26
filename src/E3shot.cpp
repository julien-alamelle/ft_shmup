#include "E3shot.hpp"
#include <ncurses.h>
#include "ft_shmup.hpp"

E3shot::E3shot():Enemy() {;}
E3shot::E3shot(int x, int y):Enemy(x,y,150) {;}
E3shot::E3shot(const E3shot &src):Enemy(src) {;}
E3shot::~E3shot() {;}

E3shot&	E3shot::operator=(const E3shot &src) {
	if (this == &src) return (*this);
	Enemy::operator=(src);
	return (*this);
}

bool E3shot::update() {
	if (rand()%10 == 0) ++(this->x);
	int i = rand()%120;
	if (i==1) ++(this->y);
	if (i==2) --(this->y);
	if (rand()%30 == 0) { 
		this->_EntityCreator("bulletDown", this->x, this->y);
		this->_EntityCreator("bulletDR", this->x, this->y);
		this->_EntityCreator("bulletDL", this->x, this->y);
	}
	if (this->y < 1)
		this->y = 1;
	if (this->y > get_maxy(COLS) - 2)
		this->y = get_maxy(COLS) - 2;
	if (this->x < LINES)
		return true;
	delete this;
	return false;
}

void E3shot::print(WINDOW *win) {
	mvwaddch(win, this->x, this->y, 'Y');
}
