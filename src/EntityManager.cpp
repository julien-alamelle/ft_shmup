#include "EntityManager.hpp"

Entity *newEnemy(int x, int y) {
	return new Enemy(x,y);
}

EntityManager::EntityManager():_player(),_enemys(),_bullets(),_factory() {
	this->registerEntity("enemy", newEnemy);
}
EntityManager::~EntityManager() {
	for (auto ite = this->_enemys.begin(); ite < this->_enemys.end(); ++ite)
		delete *ite;
	for (auto itb = this->_bullets.begin(); itb < this->_bullets.end(); ++itb)
		delete *itb;
}

void EntityManager::registerEntity(std::string key, Entity* (*value)(int , int)) {
	this->_factory[key] = value;
}

void EntityManager::createEntity(std::string key, int x, int y) {
	auto it = this->_factory.find(key);
	if (it != this->_factory.end())
		this->assign((it->second)(x, y));
}

void EntityManager::assign(Entity *entity) {
	
	Enemy *res = dynamic_cast<Enemy *>(entity);
	if (res) {
		this->_enemys.push_back(res);
		return;
	}
	Bullet *res2 = dynamic_cast<Bullet *>(entity);
	if (res2) this->_bullets.push_back(res2);
}

bool EntityManager::update() {
	this->_player.update();
	size_t e = 0;
	while (e < this->_enemys.size()) {
		if (!this->_enemys[e]->update())
			this->_enemys.erase(this->_enemys.begin() + e);
		else
			++e;
	}
	size_t b = 0;
	while (b < this->_bullets.size()) {
		if (!this->_bullets[b]->update())
			this->_bullets.erase(this->_bullets.begin() + b);
		else {
			if (this->_player.collide(this->_bullets[b]))
				return false;
			e = 0;
			while (e < this->_enemys.size()) {
				if (this->_enemys[e]->collide(this->_bullets[b]))
					this->_enemys.erase(this->_enemys.begin() + e);
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
	for (auto ite = this->_enemys.begin(); ite < this->_enemys.end(); ++ite)
		(*ite)->print();
	for (auto itb = this->_bullets.begin(); itb < this->_bullets.end(); ++itb)
		(*itb)->print();
}
