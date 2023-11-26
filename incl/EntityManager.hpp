#pragma once

#include <vector>
#include <map>
#include <string>
#include <Entity.hpp>
#include <Player.hpp>
#include <Enemy.hpp>
#include <Bullet.hpp>
#include <ncurses.h>

class EntityManager {
private:
	Player		_player;
	static std::vector<Enemy *>		_enemys;
	static std::vector<Bullet *>		_bullets;
	static std::vector<PowerUp *>		_powerUp;
	static std::map<std::string, Entity* (*)(int, int, int)> _factory;
	static void assign(Entity *entity);

public:
	EntityManager();
	virtual ~EntityManager();
	void registerEntity(std::string key, Entity* (*value)(int, int, int));
	static void createEntity(std::string key, int x, int y, int team);

	int update();
	void print(WINDOW *win); 
	Player *getPlayer();
	int getEnemyNumber();
};
