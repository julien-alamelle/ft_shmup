#pragma once

#include "Entity.hpp"
#include "PowerUp.hpp"
#include "ft_shmup.hpp"

class Player:public Entity {
private:
	long dmgtick;
	int shotSpeed = 0;
	int nbShot = 1;
public:
	Player();
	Player(const Player &);
	virtual ~Player();
	Player&	operator=(const Player &);

	virtual bool update();
	virtual void print(WINDOW *win);
	virtual bool collide(Entity *);
	virtual bool collidePowerUp(PowerUp *);
	bool isImmune();
	bool hit();
};
