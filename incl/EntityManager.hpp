#pragma once

#include <vector>
#include <map>
#include <string>
#include <Entity.hpp>
#include <Player.hpp>
#include <Enemy.hpp>
#include <Bullet.hpp>

class EntityManager {
private:
	Player		_player;
	std::vector<Enemy *>		_enemys;
	std::vector<Bullet *>		_bullets;
	std::map<std::string, Entity* (*)(int, int)> _factory;
	void assign(Entity *entity);

public:
	EntityManager();
	virtual ~EntityManager();
	void registerEntity(std::string key, Entity* (*value)(int , int ));
	void createEntity(std::string key, int x, int y);

	bool update();
	void print(); 
};
