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
	static std::vector<Enemy *>		_enemys;
	static std::vector<Bullet *>		_bullets;
	static std::map<std::string, Entity* (*)(int, int)> _factory;
	static void assign(Entity *entity);

public:
	EntityManager();
	virtual ~EntityManager();
	void registerEntity(std::string key, Entity* (*value)(int , int ));
	static void createEntity(std::string key, int x, int y);

	bool update();
	void print(); 
};
