#pragma once

#include "Entity.hpp"
#include <ncurses.h>

class PowerUp:public Entity {
private:
	int type;
public:
	PowerUp(int x, int y, int type);
	PowerUp(const PowerUp &);
	virtual ~PowerUp();
	PowerUp&	operator=(const PowerUp &);

	virtual bool update();
	virtual void print(WINDOW *win);
	int getType();
};
