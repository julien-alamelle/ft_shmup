#include "Player.hpp"
#include <ncurses.h>

Player::Player():Entity() {;}
Player::Player(const Player &src):Entity(src) {;}
Player::~Player() {;}

Player&	Player::operator=(const Player &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}

bool Player::update() {
	this->x += 2;
	this->x %= LINES;
	this->y += 1;
	this->y %= COLS;
	return true;
}

void Player::print() {
	mvaddch(x,y,'O');
}
