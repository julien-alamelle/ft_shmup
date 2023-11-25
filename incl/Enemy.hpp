#pragma once

#include "Entity.hpp"

class Enemy:public Entity {
private:

public:
	Enemy();
	Enemy(const Enemy &);
	virtual ~Enemy();
	Enemy&	operator=(const Enemy &);
};
