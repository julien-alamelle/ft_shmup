#include "Player.hpp"
#include "GameState.hpp"
#include <ncurses.h>
#include <algorithm>
#include "ft_shmup.hpp"

Player::Player():Entity(LINES - 3, get_maxy(COLS) / 2),lives(3),dmgtick(-(FRAME_RATE * 30)) {;}
Player::Player(const Player &src):Entity(src) {;}
Player::~Player() {;}

Player&	Player::operator=(const Player &src) {
	if (this == &src) return (*this);
	Entity::operator=(src);
	return (*this);
}

bool Player::update() {
	if (std::find(this->_input->begin(), this->_input->end(), KEY_UP) != this->_input->end())
		this->x -= 1;
	if (std::find(this->_input->begin(), this->_input->end(), KEY_DOWN) != this->_input->end())
		this->x += 1;
	if (std::find(this->_input->begin(), this->_input->end(), KEY_LEFT) != this->_input->end())
		this->y -= 1;
	if (std::find(this->_input->begin(), this->_input->end(), KEY_RIGHT) != this->_input->end())
		this->y += 1;
	if (this->x > LINES - 2)
		this->x = LINES - 2;
	if (this->x < LINES - 20)
		this->x = LINES - 20;
	if (this->y >= get_maxy(COLS) - 1)
		this->y = 1;
	if (this->y < 1)
		this->y = get_maxy(COLS) - 2;
	if (std::find(this->_input->begin(), this->_input->end(), ' ') != this->_input->end())
		this->_EntityCreator("bulletUp", this->x, this->y);
	return true;
}

void Player::print(WINDOW *win) {
	if (this->isImmune())
	{
		attron(A_BLINK);
		mvwaddch(win, x,y,'X');
	}
	else
		mvwaddch(win, x,y,'O');
	attron(A_NORMAL);
}

bool Player::collide(Entity *entity) {	
	if (this->x == entity->getx() && this->y == entity->gety()) {
		return true;
	}
	return false;
}

bool Player::isImmune(){
	return ((GameState::getInstance()->getTicks() - this->dmgtick) < FRAME_RATE * 3);
}

bool Player::hit()
{
	if (!this->isImmune())
	{
		this->dmgtick = GameState::getInstance()->getTicks();
		this->lives--;
		if (this->lives < 1)
			return true;
	}
	return false;
}

int Player::getLives()
{
	return this->lives;
}
