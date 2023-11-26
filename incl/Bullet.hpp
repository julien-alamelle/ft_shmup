#pragma once

#include "Entity.hpp"

class Bullet:public Entity {
protected:
	int dx;
	int dy;
	int tmax;
	int t;
	char c;

public:
	Bullet();
	Bullet(int x, int y, int dx, int dy, int tmax);
	Bullet(const Bullet &);
	virtual ~Bullet();
	Bullet&	operator=(const Bullet &);

	bool update();
	void print(WINDOW *win);
	int getDir();
};
