#pragma once

#include "Enemy.hpp"

class E3shot:public Enemy {
private:

public:
	E3shot();
	E3shot(int x, int y, int team);
	E3shot(const E3shot &);
	virtual ~E3shot();
	E3shot&	operator=(const E3shot &);

	virtual bool update();
	virtual void print(WINDOW *win);
};
