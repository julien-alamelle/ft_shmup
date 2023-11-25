#pragma once

class Entity {
protected:
	int		x;
	int		y;

public:
	Entity();
	Entity(int x, int y);
	Entity(const Entity &);
	virtual ~Entity();
	Entity&	operator=(const Entity &);

	virtual bool update() = 0;
	virtual void print() = 0;
	virtual bool collide(Entity *);
};