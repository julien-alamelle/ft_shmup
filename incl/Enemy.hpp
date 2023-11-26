#pragma once

#include "Entity.hpp"

class Enemy:public Entity {
private:
	int	score;
public:
	Enemy();
	Enemy(int x, int y, int team, int score=50, int hp=1);
	Enemy(const Enemy &);
	virtual ~Enemy();
	Enemy&	operator=(const Enemy &);

	virtual bool update();
	virtual void print(WINDOW *win);
	virtual bool collide(Entity *entity);
	int	getScore();
};
