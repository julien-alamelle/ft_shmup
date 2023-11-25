#include "Bullet.hpp"
#include <ncurses.h>

Bullet::Bullet():Entity() {;}
Bullet::Bullet(int x, int y, int d):Entity(x,y),d(d),t(0) {;}
Bullet::Bullet(const Bullet &src):Entity(src) {;}
Bullet::~Bullet() {;}

Bullet&	Bullet::operator=(const Bullet &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}

bool Bullet::update() {
	if (!t) {
		t = 3;
		x += d;
	} else --t;
	if (this->x >= 0 && this->x < LINES && this->y >= 0 && this->y < COLS)
		return true;
	delete this;
	return false;
}

void Bullet::print() {
	mvaddch(this->x, this->y, '|');
}

