/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameState.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:00:30 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 12:51:36 by jalamell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameState.hpp"
#include "ft_shmup.hpp"
#include <ctime>

GameState *GameState::instance;

bool GameState::update()
{
	ticks++;
	box(this->winGame, 0, 0);
	this->background.update(this->winGame);
	if (ticks % (FRAME_RATE * 3) == 0)
		this->entityManager.createEntity("enemy", 0, rand() % (get_maxy(COLS)));
	if (ticks % (FRAME_RATE * 10) == 0)
		this->entityManager.createEntity("e3shot", 0, rand() % (get_maxy(COLS)));
	if (ticks % (FRAME_RATE * 30) == 0)
		this->entityManager.createEntity("emothership", 0, rand() % (get_maxy(COLS)));
	this->entityManager.print(this->winGame);
	int newscore = this->entityManager.update();
	if (newscore == -1)
		return (TRUE);
	this->score += newscore;
	return (FALSE);
}

void GameState::print_data()
{
	box(this->winData, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD);
	wmove(this->winData, 1, 1);
	wprintw(this->winData, "score: %ld", this->score);
	wmove(this->winData, 2, 1);
	wprintw(this->winData, "lifes: %d", this->entityManager.getPlayer()->getLives());
	wmove(this->winData, 3, 1);
	wprintw(this->winData, "time : %d", (int) ((clock() - this->startTime) / CLOCKS_PER_SEC));
	attron(A_NORMAL);
}

GameState::GameState():score(0),ticks(0)
{
	this->startTime = clock();
	this->winData = subwin(stdscr, 5, SIDE_GAP, 0, 0);
	this->winGame = subwin(stdscr, LINES, get_maxy(COLS), 0, SIDE_GAP);
	GameState::setInstance(this);
}

GameState::~GameState()
{

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