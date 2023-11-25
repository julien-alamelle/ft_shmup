/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameState.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:00:30 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/25 20:37:03 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameState.hpp"
#include "Utils.hpp"
#include <ctime>

void GameState::update()
{
	this->background.update();
	if (ticks == 0)
		this->entityManager.createEntity("enemy", 0, rand() % COLS);
	this->entityManager.print();
	this->entityManager.update();
	ticks++;
}

void GameState::print_data()
{
	box(this->winData, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD);
	wmove(this->winData, 1, 1);
	wprintw(this->winData, "score: %d", this->score);
	wmove(this->winData, 2, 1);
	wprintw(this->winData, "lifes: %d", 3);
	wmove(this->winData, 3, 1);
	wprintw(this->winData, "time : %d", (int) ((clock() - this->startTime) / CLOCKS_PER_SEC));
	attron(A_NORMAL);
}

GameState::GameState():score(0),ticks(0)
{
	this->startTime = clock();
	this->winData = subwin(stdscr, 5, 17, 0, 0);
}

GameState::~GameState()
{

}
