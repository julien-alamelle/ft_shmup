#pragma once

#include "Entity.hpp"

class Player:public Entity {
private:
	long dmgtick;
public:
	Player();
	Player(const Player &);
	virtual ~Player();
	Player&	operator=(const Player &);

	virtual bool update();
	virtual void print(WINDOW *win);
	virtual bool collide(Entity *);
	bool isImmune();
	bool hit();
	int getLives();
};
