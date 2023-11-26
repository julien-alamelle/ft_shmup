#include "EntityManager.hpp"

Entity *newEnemy(int x, int y) {
	return new Enemy(x,y);
}
Entity *newBulletDown(int x, int y) {
	return new Bullet(x,y,1,0,3); 
}
Entity *newBulletUp(int x, int y) {
	return new Bullet(x,y,-1,0,3); 
}

EntityManager::EntityManager():_player() {
	this->registerEntity("enemy", newEnemy);
	this->registerEntity("bulletDown", newBulletDown);
}
EntityManager::~EntityManager() {
	for (auto ite = EntityManager::_enemys.begin(); ite < EntityManager::_enemys.end(); ++ite)
		delete *ite;
	for (auto itb = EntityManager::_bullets.begin(); itb < EntityManager::_bullets.end(); ++itb)
		delete *itb;
}

void EntityManager::registerEntity(std::string key, Entity* (*value)(int , int)) {
	EntityManager::_factory[key] = value;
}

void EntityManager::createEntity(std::string key, int x, int y) {
	auto it = EntityManager::_factory.find(key);
	if (it != EntityManager::_factory.end())
		EntityManager::assign((it->second)(x, y));
}

void EntityManager::assign(Entity *entity) {
	
	Enemy *res = dynamic_cast<Enemy *>(entity);
	if (res) {
		EntityManager::_enemys.push_back(res);
		return;
	}
	Bullet *res2 = dynamic_cast<Bullet *>(entity);
	if (res2) EntityManager::_bullets.push_back(res2);
}

bool EntityManager::update() {
	this->_player.update();
	size_t e = 0;
	while (e < EntityManager::_enemys.size()) {
		if (!EntityManager::_enemys[e]->update())
			EntityManager::_enemys.erase(EntityManager::_enemys.begin() + e);
		else
			++e;
	}
	size_t b = 0;
	while (b < EntityManager::_bullets.size()) {
		if (!EntityManager::_bullets[b]->update())
			EntityManager::_bullets.erase(EntityManager::_bullets.begin() + b);
		else {
			if (this->_player.collide(EntityManager::_bullets[b]))
				return false;
			e = 0;
			while (e < EntityManager::_enemys.size()) {
				if (EntityManager::_enemys[e]->collide(EntityManager::_bullets[b]))
					EntityManager::_enemys.erase(EntityManager::_enemys.begin() + e);
				else
					++e;
			}
			++b;
		}
	}
	return true;
}

void EntityManager::print() {
	this->_player.print();
	for (auto ite = EntityManager::_enemys.begin(); ite < EntityManager::_enemys.end(); ++ite)
		(*ite)->print();
	for (auto itb = EntityManager::_bullets.begin(); itb < EntityManager::_bullets.end(); ++itb)
		(*itb)->print();
}
