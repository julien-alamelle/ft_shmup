#pragma once

#include "Entity.hpp"

class Player:public Entity {
private:

public:
	Player();
	Player(const Player &);
	virtual ~Player();
	Player&	operator=(const Player &);

	virtual void update();
	virtual void print();
};
