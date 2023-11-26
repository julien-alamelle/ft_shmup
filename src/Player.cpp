#include "Player.hpp"
#include "GameState.hpp"
#include <ncurses.h>
#include <algorithm>

Player::Player():Entity(LINES - 3, get_maxy(COLS) / 2, 1, LIVES),dmgtick(-(FRAME_RATE * 30)) {;}
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
	if (std::find(this->_input->begin(), this->_input->end(), ' ') != this->_input->end() || (this->shotSpeed && (GameState::getInstance()->getTicks() & 4))) {
		if (this->shotSpeed)
			this->shotSpeed -= 1;
		if (this->nbShot >= 7)
			this->_EntityCreator("bsplitUp", this->x, this->y, this->team);
		else {
			if (this->nbShot & 1)
				this->_EntityCreator("bulletUp", this->x, this->y, this->team);
			else {
				this->_EntityCreator("bulletUp", this->x, this->y+1, this->team);
				this->_EntityCreator("bulletUp", this->x, this->y-1, this->team);
			}
			if (this->nbShot > 2) {
				this->_EntityCreator("bulletUR", this->x, this->y, this->team);
				this->_EntityCreator("bulletUL", this->x, this->y, this->team);
			}
			if (this->nbShot > 4) {
				this->_EntityCreator("bulletRight", this->x, this->y, this->team);
				this->_EntityCreator("bulletLeft", this->x, this->y, this->team);
			}
		}
	}
	return true;
}

void Player::print(WINDOW *win) {
	if (this->isImmune() && GameState::getInstance()->getTicks() % FRAME_RATE < FRAME_RATE / 2)
		return ;
	mvwaddch(win, x,y,'O');
}

bool Player::collide(Entity *entity) {	
	if (this->x == entity->getx() && this->y == entity->gety() && this->team != entity->getTeam()) {
		return true;
	}
	return false;
}

bool Player::collidePowerUp(PowerUp *powerUp) {
	if (this->x == powerUp->getx() && this->y == powerUp->gety()) {
		switch (powerUp->getType()) {
			case 1:
				this->nbShot += 1;
				break;
			default:
				this->shotSpeed += FRAME_RATE * AUTOFIRE_LENGTH;
		}
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
		this->hp--;
		if (this->hp < 1)
			return true;
	}
	return false;
}
