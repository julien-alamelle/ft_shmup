#include "EntityManager.hpp"
#include "E3shot.hpp"
#include "EMothership.hpp"
#include "Bsplit.hpp"
#include "ESplit.hpp"
#include "ft_shmup.hpp"

Entity *newEnemy(int x, int y) {
	return new Enemy(x,y);
}
Entity *newE3shot(int x, int y) {
	return new E3shot(x,y);
}
Entity *newEMothership(int x, int y) {
	return new EMothership(x,y);
}
Entity *newESplit(int x, int y) {
	return new ESplit(x,y); 
}
Entity *newBulletDown(int x, int y) {
	return new Bullet(x,y,1,0, FRAME_RATE / 30); 
}
Entity *newBulletDR(int x, int y) {
	return new Bullet(x,y,1,1,FRAME_RATE / 30); 
}
Entity *newBulletDL(int x, int y) {
	return new Bullet(x,y,1,-1,FRAME_RATE / 30); 
}
Entity *newBulletUp(int x, int y) {
	return new Bullet(x,y,-1,0,FRAME_RATE / 30); 
}
Entity *newBulletRight(int x, int y) {
	return new Bullet(x,y,0,1,FRAME_RATE / 30); 
}
Entity *newBulletLeft(int x, int y) {
	return new Bullet(x,y,0,-1,FRAME_RATE / 30); 
}
Entity *newBSplit(int x, int y) {
	return new Bsplit(x,y,1,0,FRAME_RATE / 30); 
}

EntityManager::EntityManager():_player() {
	this->registerEntity("enemy", newEnemy);
	this->registerEntity("e3shot", newE3shot);
	this->registerEntity("emothership", newEMothership);
	this->registerEntity("esplit", newESplit);
	this->registerEntity("bulletDown", newBulletDown);
	this->registerEntity("bulletDR", newBulletDR);
	this->registerEntity("bulletDL", newBulletDL);
	this->registerEntity("bulletUp", newBulletUp);
	this->registerEntity("bulletRight", newBulletRight);
	this->registerEntity("bulletLeft", newBulletLeft);
	this->registerEntity("bsplit", newBSplit);
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
			int db = 1;
			if (EntityManager::_bullets[b]->getDir() <= 0)
			{
				while (e < EntityManager::_enemys.size()) {
					int new_score = EntityManager::_enemys[e]->getScore();
					if (EntityManager::_enemys[e]->collide(EntityManager::_bullets[b]))
					{
						EntityManager::_enemys.erase(EntityManager::_enemys.begin() + e);
						delete EntityManager::_bullets[b];
						EntityManager::_bullets.erase(EntityManager::_bullets.begin() + b);
						bonus_score += new_score;
						db = 0;
						break;
					}
					++e;
				}
			}
			b += db;
		}
	}
	return bonus_score;
}

void EntityManager::print(WINDOW *win) {
	wattron(win, COLOR_PAIR(42));
	for (auto itb = EntityManager::_bullets.begin(); itb < EntityManager::_bullets.end(); ++itb)
		(*itb)->print(win);
	for (auto ite = EntityManager::_enemys.begin(); ite < EntityManager::_enemys.end(); ++ite)
		(*ite)->print(win);
	wattroff(win, COLOR_PAIR(42));
	this->_player.print(win);
}

Player *EntityManager::getPlayer()
{
	return &this->_player;
}

int EntityManager::getEnemyNumber()
{
	return this->_enemys.size();
}
