#include "Bullet.hpp"
#include "ft_shmup.hpp"
#include <ncurses.h>

Bullet::Bullet():Entity() {;}
Bullet::Bullet(int x, int y, int dx, int dy, int tmax, int team):Entity(x,y,team),dx(dx),dy(dy),tmax(tmax),t(0) {
	if (!dy) c = '|';
	else if (!dx) c = '-';
	else if (dx*dy > 0) c = '\\';
	else c = '/';
}
Bullet::Bullet(const Bullet &src):Entity(src) {;}
Bullet::~Bullet() {;}

Bullet&	Bullet::operator=(const Bullet &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}

bool Bullet::update() {
	if (!t) {
		t = tmax;
		x += dx;
		y += dy;
	} else --t;
	if (this->x >= 0 && this->x < LINES && this->y > 0 && this->y < get_maxy(COLS) - 1)
		return true;
	delete this;
	return false;
}

void Bullet::print(WINDOW *win) {
	if (this->team == 1)
		wattron(win, COLOR_PAIR(69));
	else
		wattron(win, COLOR_PAIR(42));
	mvwaddch(win, this->x, this->y, this->c);
	if (this->team == 1)
		wattroff(win, COLOR_PAIR(69));
	else
		wattroff(win, COLOR_PAIR(42));
}

int Bullet::getDir()
{
	return this->dx;
}
