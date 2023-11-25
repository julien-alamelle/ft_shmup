#pragma once

#include "Entity.hpp"

class Bullet:public Entity {
private:

public:
	Bullet();
	Bullet(const Bullet &);
	virtual ~Bullet();
	Bullet&	operator=(const Bullet &);
};
