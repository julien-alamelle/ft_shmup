#pragma once

#include "Entity.hpp"

class Enemy:public Entity {
private:
	int	score = 50;
public:
	Enemy();
	Enemy(int x, int y);
	Enemy(const Enemy &);
	virtual ~Enemy();
	Enemy&	operator=(const Enemy &);

	virtual bool update();
	virtual void print(WINDOW *win);
	int	getScore();
};
