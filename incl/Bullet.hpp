#pragma once

#include "Entity.hpp"

class Bullet:public Entity {
private:
	int d;
	int t;

public:
	Bullet();
	Bullet(int x, int y, int d);
	Bullet(const Bullet &);
	virtual ~Bullet();
	Bullet&	operator=(const Bullet &);

	bool update();
	void print(WINDOW *win);
	int getDir();
};
