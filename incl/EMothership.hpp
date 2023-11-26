#pragma once

#include "Enemy.hpp"

class EMothership:public Enemy {
private:

public:
	EMothership();
	EMothership(int x, int y);
	EMothership(const EMothership &);
	virtual ~EMothership();
	EMothership&	operator=(const EMothership &);

	virtual bool update();
	virtual void print(WINDOW *win);
};
