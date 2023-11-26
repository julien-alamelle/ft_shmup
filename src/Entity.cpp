#include "Entity.hpp"

Entity::Entity():x(0),y(0) {;}
Entity::Entity(int x, int y):x(x),y(y) {;}
Entity::Entity(const Entity &src):x(src.x),y(src.y) {;}
Entity::~Entity() {;}

Entity&	Entity::operator=(const Entity &src) {
	if (this == &src) return (*this);
	this->x = src.x;
	this->y = src.y;
	return (*this);
}

int Entity::getx() {return this->x;}
int Entity::gety() {return this->y;}

void Entity::setInput(std::vector<int> *input) {
	Entity::_input = input;
}

bool Entity::collide(Entity *entity) {
	if (this->x == entity->x && this->y == entity->y) {
		delete this;
		return true;
	}
	return false;
}
