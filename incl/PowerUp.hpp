#pragma once

#include "Entity.hpp"

class PowerUp:public Entity {
private:
	int type;
public:
	PowerUp(int x, int y, int type);
	PowerUp(const PowerUp &);
	virtual ~PowerUp();
	PowerUp&	operator=(const PowerUp &);

	int getType();
};
