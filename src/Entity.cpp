#include "Entity.hpp"

Entity::Entity():x(0),y(0) {;}
Entity::Entity(const Entity &src):x(src.x),y(src.y) {;}
Entity::~Entity() {;}

Entity&	Entity::operator=(const Entity &src) {
	if (this == &src) return (*this);
	this->x = src.x;
	this->y = src.y;
	return (*this);
}
