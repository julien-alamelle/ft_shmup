#include "Enemy.hpp"
#include <ncurses.h>
#include <cstdlib>

Enemy::Enemy():Entity() {;}
Enemy::Enemy(int x, int y):Entity(x,y) {;}
Enemy::Enemy(const Enemy &src):Entity(src) {;}
Enemy::~Enemy() {;}

Enemy&	Enemy::operator=(const Enemy &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}

bool Enemy::update() {
	//if (!rand()%5) 
	if (rand()%30 == 0) ++(this->x);
	int i = rand()%120;
	if (i==1) ++(this->y);
	if (i==2) --(this->y);
	if (this->x < LINES && this->y >= 0 && this->y < COLS)
		return true;
	delete this;
	return false;
}

void Enemy::print() {
	mvaddch(this->x, this->y, 'V');
}

