#pragma once

#include "Bullet.hpp"

class BsmartSplit:public Bullet {
private:

public:
	BsmartSplit();
	BsmartSplit(int x, int y, int dx, int dy, int tmax, int team);
	BsmartSplit(const BsmartSplit &);
	virtual ~BsmartSplit();
	BsmartSplit&	operator=(const BsmartSplit &);

	bool update();
};
