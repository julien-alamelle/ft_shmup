#pragma once

#include "Enemy.hpp"

class ESmartSplit:public Enemy {
private:

public:
	ESmartSplit();
	ESmartSplit(int x, int y, int team);
	ESmartSplit(const ESmartSplit &);
	virtual ~ESmartSplit();
	ESmartSplit&	operator=(const ESmartSplit &);

	virtual bool update();
	virtual void print(WINDOW *win);
};
