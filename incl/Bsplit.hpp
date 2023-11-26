#pragma once

#include "Bullet.hpp"

class Bsplit:public Bullet {
private:

public:
	Bsplit();
	Bsplit(int x, int y, int dx, int dy, int tmax, int team);
	Bsplit(const Bsplit &);
	virtual ~Bsplit();
	Bsplit&	operator=(const Bsplit &);

	bool update();
};
