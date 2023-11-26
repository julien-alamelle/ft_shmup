#include "EntityManager.hpp"
#include "E3shot.hpp"

Entity *newEnemy(int x, int y) {
	return new Enemy(x,y);
}
Entity *newE3shot(int x, int y) {
	return new E3shot(x,y);
}
Entity *newBulletDown(int x, int y) {
	return new Bullet(x,y,1,0,3); 
}
Entity *newBulletDR(int x, int y) {
	return new Bullet(x,y,1,1,3); 
}
Entity *newBulletDL(int x, int y) {
	return new Bullet(x,y,1,-1,3); 
}
Entity *newBulletUp(int x, int y) {
	return new Bullet(x,y,-1,0,3); 
}

EntityManager::EntityManager():_player() {
	this->registerEntity("enemy", newEnemy);
	this->registerEntity("e3shot", newE3shot);
	this->registerEntity("bulletDown", newBulletDown);
	this->registerEntity("bulletDR", newBulletDR);
	this->registerEntity("bulletDL", newBulletDL);
	this->registerEntity("bulletUp", newBulletUp);
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

int EntityManager::update() {
	int bonus_score = 0;
	this->_player.update();
	size_t e = 0;
	while (e < EntityManager::_enemys.size()) {
		if (!EntityManager::_enemys[e]->update())
		{
			EntityManager::_enemys.erase(EntityManager::_enemys.begin() + e);
			if (this->_player.hit())
				return (-1);
			while (EntityManager::_enemys.size() != 0)
			{
				delete EntityManager::_enemys[0];
				EntityManager::_enemys.erase(EntityManager::_enemys.begin());
			}
			break;
		}
		else
		{
			if (this->_player.collide(EntityManager::_enemys[e]) && this->_player.hit())
				return (-1);
			++e;
		}
	}
	size_t b = 0;
	while (b < EntityManager::_bullets.size()) {
		if (!EntityManager::_bullets[b]->update())
			EntityManager::_bullets.erase(EntityManager::_bullets.begin() + b);
		else {
			if (EntityManager::_bullets[b]->getDir() >= 0 && this->_player.collide(EntityManager::_bullets[b]) && this->_player.hit())
				return (-1);
			e = 0;
			if (EntityManager::_bullets[b]->getDir() <= 0)
			{
				while (e < EntityManager::_enemys.size()) {
					int new_score = EntityManager::_enemys[e]->getScore();
					if (EntityManager::_enemys[e]->collide(EntityManager::_bullets[b]))
					{
						EntityManager::_enemys.erase(EntityManager::_enemys.begin() + e);
						bonus_score += new_score;
					}
					else
						++e;
				}
			}
			++b;
		}
	}
	return bonus_score;
}

void EntityManager::print(WINDOW *win) {
	for (auto itb = EntityManager::_bullets.begin(); itb < EntityManager::_bullets.end(); ++itb)
		(*itb)->print(win);
	this->_player.print(win);
	for (auto ite = EntityManager::_enemys.begin(); ite < EntityManager::_enemys.end(); ++ite)
		(*ite)->print(win);
}

Player *EntityManager::getPlayer()
{
	return &this->_player;
}
