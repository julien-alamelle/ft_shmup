#include "EntityManager.hpp"

EntityManager::EntityManager():_player(),_enemys(),_bullets() {;}
EntityManager::EntityManager(const EntityManager &src):_player(src._player),_enemys(src._enemys),_bullets(src._bullets) {;}
EntityManager::~EntityManager() {;}

EntityManager&	EntityManager::operator=(const EntityManager &src) {
	if (this == &src) return (*this);
	this->_player = src._player;
	this->_enemys = src._enemys;
	this->_bullets = src._bullets;
	return (*this);
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
	//todo
}
