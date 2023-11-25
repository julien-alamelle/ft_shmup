#include "Bullet.hpp"

Bullet::Bullet():Entity() {;}
Bullet::Bullet(const Bullet &src):Entity(src) {;}
Bullet::~Bullet() {;}

Bullet&	Bullet::operator=(const Bullet &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}
