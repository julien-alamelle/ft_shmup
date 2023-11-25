#pragma once
#include <string>

class Entity {
protected:
	int		x;
	int		y;
	static void (*_EntityCreator)(std::string, int, int);

public:
	Entity();
	Entity(int x, int y);
	Entity(const Entity &);
	virtual ~Entity();
	Entity&	operator=(const Entity &);
	int getx();
	int gety();
	static void setEntityCreator(void (*entityCreator)(std::string, int, int));

	virtual bool update() = 0;
	virtual void print() = 0;
	virtual bool collide(Entity *);
};
