#include "BsmartSplit.hpp"
#include "GameState.hpp"
#include "ft_shmup.hpp"

BsmartSplit::BsmartSplit():Bullet() {;}
BsmartSplit::BsmartSplit(int x, int y, int dx, int dy, int tmax, int team):Bullet(x,y,dx,dy,tmax,team) {this->c = '*';}
BsmartSplit::BsmartSplit(const BsmartSplit &src):Bullet(src) {;}
BsmartSplit::~BsmartSplit() {;}

BsmartSplit&	BsmartSplit::operator=(const BsmartSplit &src) {
	if (this == &src) return (*this);
	Bullet::operator=(src);
	return (*this);
}

bool BsmartSplit::update() {
	if (!t) {
		t = tmax;
		x += dx;
		y += dy;
	} else --t;
	int playerx = GameState::getInstance()->getEntityManager()->getPlayer()->getx() ;
	if (playerx == this->getx() || playerx + 1 == this->getx()) {
		this->_EntityCreator("bulletRight", playerx, this->y, this->team);
		this->_EntityCreator("bulletLeft", playerx, this->y, this->team);
		delete this;
		return false;
	}
	if (this->x >= 0 && this->x < LINES && this->y > 0 && this->y < get_maxy(COLS) - 1)
		return true;
	delete this;
	return false;
}
