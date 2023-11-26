#include "Enemy.hpp"
#include <ncurses.h>
#include <cstdlib>
#include "ft_shmup.hpp"

Enemy::Enemy():Entity() {;}
Enemy::Enemy(int x, int y, int score, int hp):Entity(x,y,hp),score(score) {;}
Enemy::Enemy(const Enemy &src):Entity(src) {;}
Enemy::~Enemy() {;}

Enemy&	Enemy::operator=(const Enemy &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}

bool Enemy::update() {
	if (rand()%30 == 0) ++(this->x);
	int i = rand()%120;
	if (i==1) ++(this->y);
	if (i==2) --(this->y);
	if (rand()%30 == 0) 
		this->_EntityCreator("bulletDown", this->x, this->y);
	if (this->y < 1)
		this->y = 1;
	if (this->y > get_maxy(COLS) - 2)
		this->y = get_maxy(COLS) - 2;
	if (this->x < LINES)
		return true;
	delete this;
	return false;
}

void Enemy::print(WINDOW *win) {
	mvwaddch(win, this->x, this->y, 'V');
}

int	Enemy::getScore(){
	return this->score;
}
