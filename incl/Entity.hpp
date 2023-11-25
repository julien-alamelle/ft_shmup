#pragma once

class Entity {
protected:
	int		x;
	int		y;

public:
	Entity();
	Entity(const Entity &);
	virtual ~Entity();
	Entity&	operator=(const Entity &);

	virtual void update() = 0;
	virtual void print() = 0;
};
