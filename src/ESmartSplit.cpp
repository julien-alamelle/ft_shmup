#include "ESmartSplit.hpp"
#include <ncurses.h>
#include "GameState.hpp"
#include "ft_shmup.hpp"

ESmartSplit::ESmartSplit():Enemy() {;}
ESmartSplit::ESmartSplit(int x, int y, int team):Enemy(x,y,team,300,1) {;}
ESmartSplit::ESmartSplit(const ESmartSplit &src):Enemy(src) {;}
ESmartSplit::~ESmartSplit() {;}

ESmartSplit&	ESmartSplit::operator=(const ESmartSplit &src) {
	if (this == &src) return (*this);
	Enemy::operator=(src);
	return (*this);
}

bool ESmartSplit::update() {
	if (rand()%FRAME_RATE == 0) ++(this->x);
	if (GameState::getInstance()->getTicks()%(FRAME_RATE*2) == 0) 
		this->_EntityCreator("bsmartplit", this->x, this->y, this->team);
	if (this->x < LINES)
		return true;
	delete this;
	return false;
}

void ESmartSplit::print(WINDOW *win) {
	mvwaddch(win, this->x, this->y, 'T');
}
