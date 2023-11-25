/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameState.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:00:30 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/25 19:21:13 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameState.hpp"
#include "Utils.hpp"
#include <ctime>

void GameState::update()
{
	this->background.update();
	this->entityManager.print();
	this->entityManager.update();
}

void GameState::print_data()
{
	rectangle(0, 0, 4, 20);
	attron(A_BOLD);
	move(1, 1);
	printw("score: %d", this->score);
	move(2, 1);
	printw("lifes: %d", 3);
	move(3, 1);
	printw("time : %d", (int) ((clock() - this->startTime) / CLOCKS_PER_SEC));
	attron(A_NORMAL);
}

GameState::GameState():score(0)
{
	this->startTime = clock();
}

GameState::~GameState()
{

}
