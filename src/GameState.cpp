/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameState.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:00:30 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 22:52:53 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameState.hpp"
#include "ft_shmup.hpp"
#include <cmath>
#include <ctime>
#include <iostream>

GameState *GameState::instance;

bool GameState::update()
{
	box(this->winGame, 0, 0);
	this->background.update(this->winGame);
	if (this->entityManager.getEnemyNumber() == 0)
	{
		waves++;
		if (waves % WAVE_REGEN == 0)
			this->entityManager.getPlayer()->setHP(1 + this->entityManager.getPlayer()->getHP());
		if (this->getMode()) {
			for (int i = 0; i < 4 + ((this->score) % 50); i++) {
				this->entityManager.createEntity("enemy", 0, rand() % (get_maxy(COLS)), 2);
			}
			for (int i = 0; i < 1 + ((this->score) % 200); i++) {
				this->entityManager.createEntity("e3shot", 0, rand() % (get_maxy(COLS)), 2);
			}
			for (int i = 0; i < 0 + ((this->score) % 5000); i++) {
				this->entityManager.createEntity("emothership", 0, rand() % (get_maxy(COLS)), 2);
			}
			for (int i = 0; i < 1 + ((this->score) % 1000); i++) {
				this->entityManager.createEntity("esplit", 0, rand() % (get_maxy(COLS) - 2) + 1, 2);
			}
			for (int i = 0; i < 1 + ((this->score) % 1000); i++) {
				this->entityManager.createEntity("esmartsplit", 0, rand() % (get_maxy(COLS) - 2) + 1, 2);
			}
		}
		else {
			for (int i = 0; i < 3 + (std::sqrt(this->score) / 50); i++) {
				this->entityManager.createEntity("enemy", 0, rand() % (get_maxy(COLS)), 2);
			}
			for (int i = 0; i < 1 + (std::sqrt(this->score) / 100); i++) {
				this->entityManager.createEntity("e3shot", 0, rand() % (get_maxy(COLS)), 2);
			}
			for (int i = 0; i < 1 + (std::sqrt(this->score) / 150); i++) {
				this->entityManager.createEntity("emothership", 0, rand() % (get_maxy(COLS)), 2);
			}
			for (int i = 0; i < 1 + (std::sqrt(this->score) / 200); i++) {
				this->entityManager.createEntity("esplit", 0, rand() % (get_maxy(COLS) - 2) + 1, 2);
			}
			for (int i = 0; i < 0 + (std::sqrt(this->score) / 400); i++) {
				this->entityManager.createEntity("esmartsplit", 0, rand() % (get_maxy(COLS) - 2) + 1, 2);
			}
		}
	}
	this->entityManager.print(this->winGame);
	int newscore = this->entityManager.update();
	if (newscore == -1)
		return (TRUE);
	this->score += newscore;
	ticks++;
	return (FALSE);
}

void GameState::print_data()
{
	box(this->winData, ACS_VLINE, ACS_HLINE);
	wattron(this->winData, A_BOLD);
	wmove(this->winData, 1, 1);
	if (wprintw(this->winData, "score: %ld", this->score) == ERR)
		ft_error(BAD_ALLOC);
	wmove(this->winData, 2, 1);
	if (wprintw(this->winData, "lifes: %d", this->entityManager.getPlayer()->getHP()) == ERR)
		ft_error(BAD_ALLOC);
	wmove(this->winData, 3, 1);
	if (wprintw(this->winData, "time:  %d", (int) ((clock() - this->startTime) / CLOCKS_PER_SEC)) == ERR)
		ft_error(BAD_ALLOC);
	wmove(this->winData, 4, 1);
	if (wprintw(this->winData, "waves: %d", this->waves))
		ft_error(BAD_ALLOC);
	wattroff(this->winData, A_BOLD);
}

GameState::GameState():score(0),ticks(0),waves(0)
{
	this->startTime = clock();
	this->winData = subwin(stdscr, 6, SIDE_GAP, 0, 0);
	this->winGame = subwin(stdscr, LINES, get_maxy(COLS), 0, SIDE_GAP);
	GameState::setInstance(this);
}

GameState::~GameState()
{
	delwin(this->winGame);
	delwin(this->winData);
	GameState::setInstance(NULL);
}

void GameState::setInstance(GameState *gs)
{
	GameState::instance = gs;
}

GameState *GameState::getInstance()
{
	return GameState::instance;
}

long GameState::getTicks()
{
	return this->ticks;
}

long GameState::getScore()
{
	return this->score;
}

clock_t GameState::getStartTime()
{
	return this->startTime;
}

void GameState::setMode(bool mode) {
	this->hard_mode = mode;
}

bool GameState::getMode() {
	return this->hard_mode;
}

EntityManager *GameState::getEntityManager()
{
	return &(this->entityManager);
}
