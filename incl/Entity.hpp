#pragma once
#include <string>
#include <vector>
#include <ncurses.h>

class Entity {
protected:
	int		x;
	int		y;
	static void (*_EntityCreator)(std::string, int, int);
	static const std::vector<int> *_input;

public:
	Entity();
	Entity(int x, int y);
	Entity(const Entity &);
	virtual ~Entity();
	Entity&	operator=(const Entity &);
	int getx();
	int gety();
	static void setInput(std::vector<int> *input);

	virtual bool update() = 0;
	virtual void print(WINDOW *win) = 0;
	virtual bool collide(Entity *entity);
};
