#include "Bsplit.hpp"
#include "GameState.hpp"
#include "ft_shmup.hpp"

Bsplit::Bsplit():Bullet() {;}
Bsplit::Bsplit(int x, int y, int dx, int dy, int tmax, int team):Bullet(x,y,dx,dy,tmax,team) {this->c = '*';}
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
	if (GameState::getInstance()->getTicks() % (FRAME_RATE / 3) == 0) {
		this->_EntityCreator("bulletRight", this->x, this->y, this->team);
		this->_EntityCreator("bulletLeft", this->x, this->y, this->team);
	}
	if (this->x >= 0 && this->x < LINES && this->y > 0 && this->y < get_maxy(COLS) - 1)
		return true;
	delete this;
	return false;
}
