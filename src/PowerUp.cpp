#include "PowerUp.hpp"
#include "ft_shmup.hpp"
#include "GameState.hpp"

PowerUp::PowerUp(int x, int y, int team):Entity(x,y,team) {
	this->type = 0;
	if (rand() % 10 == 0)
		this->type = 1;
}

PowerUp::PowerUp(const PowerUp &src):Entity(src) {;}
PowerUp::~PowerUp() {;}

PowerUp&	PowerUp::operator=(const PowerUp &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}

int PowerUp::getType() {return this->type;}

bool PowerUp::update() {
	if (GameState::getInstance()->getTicks() % (FRAME-RATE/2) == 0)
		this->x += 1;
	if (this->x >= COLS) {
		delete this;
		return false;
	}
	return true;
}

void PowerUp::print(WINDOW *win) {
	wattron(win, COLOR_PAIR(23));
	switch (this->type) {
		case 1:
			mvwaddch(win, x,y,'+');
			break;
		default:
			mvwaddch(win, x,y,'P');
	}
	wattroff(win, COLOR_PAIR(23));
}
