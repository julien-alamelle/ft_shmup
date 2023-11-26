#pragma once

#include "Enemy.hpp"

class ESplit:public Enemy {
private:

public:
	ESplit();
	ESplit(int x, int y);
	ESplit(const ESplit &);
	virtual ~ESplit();
	ESplit&	operator=(const ESplit &);

	virtual bool update();
	virtual void print(WINDOW *win);
};
