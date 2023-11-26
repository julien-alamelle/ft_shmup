#include "Bsplit.hpp"
#include "GameState.hpp"
#include "ft_shmup.hpp"

Bsplit::Bsplit():Bullet() {;}
Bsplit::Bsplit(int x, int y, int dx, int dy, int tmax):Bullet(x,y,dx,dy,tmax) {this->c = '*';}
Bsplit::Bsplit(const Bsplit &src):Bullet(src) {;}
Bsplit::~Bsplit() {;}

Bsplit&	Bsplit::operator=(const Bsplit &src) {
	if (this == &src) return (*this);
	Bullet::operator=(src);
	return (*this);
}

bool Bsplit::update() {
	if (!t) {
		t = tmax;
		x += dx;
		y += dy;
	} else --t;
	if (GameState::getInstance()->getTicks() % (FRAME_RATE / 10) == 0) {
		this->_EntityCreator("bulletRight", this->x, this->y);
		this->_EntityCreator("bulletLeft", this->x, this->y);
	}
	if (this->x >= 0 && this->x < LINES && this->y > 0 && this->y < get_maxy(COLS) - 1)
		return true;
	delete this;
	return false;
}

void Bsplit::print(WINDOW *win) {
	mvwaddch(win, this->x, this->y, this->c);
}
