#pragma once

#include "Entity.hpp"

class Enemy:public Entity {
private:

public:
	Enemy();
	Enemy(int x, int y);
	Enemy(const Enemy &);
	virtual ~Enemy();
	Enemy&	operator=(const Enemy &);

	virtual bool update();
	virtual void print();
};
