#include "Enemy.hpp"

Enemy::Enemy():Entity() {;}
Enemy::Enemy(const Enemy &src):Entity(src) {;}
Enemy::~Enemy() {;}

Enemy&	Enemy::operator=(const Enemy &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}
