#pragma once

class EntityManager {
private:
	Player		_player;
	std::vector<Enemy>		_enemys;
	std::vector<Bullet>		_bullets;
	std::map<std::string, Entity* (*)(int, int)> _factory;

public:
	EntityManager();
	EntityManager(const EntityManager &);
	virtual ~EntityManager();
	EntityManager&	operator=(const EntityManager &);
	void registerEntity(std::string key, Entity* (*value)(int , int ));
	void createEntity(std::string key, int x, int y);
};
