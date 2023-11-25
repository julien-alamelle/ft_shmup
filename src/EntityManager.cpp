#include "EntityManager.hpp"

EntityManager::EntityManager():_player(),_enemys(),_bullets(),_factory() {;}
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
	for (auto ite = this->_enemys.begin(); ite < this->_enemys.end(); ++ite)
		(*ite)->update();
	for (auto itb = this->_bullets.begin(); itb < this->_bullets.end(); ++itb)
	{
		(*itb)->update();
		if (this->_player.collide(*itb))
			return false;
		size_t i=0;
		while (i < this->_enemys.size()) {
			if (this->_enemys[i]->collide(*itb))
				this->_enemys.erase(this->_enemys.begin()+i);
			else
				++i;
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
