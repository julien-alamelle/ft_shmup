/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:35:21 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 16:26:11 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include <ncurses.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include "GameState.hpp"
#include "ft_shmup.hpp"

void get_input(std::vector<int> &input);
bool update(GameState *gs, std::vector<int> input);
std::vector<Enemy *> EntityManager::_enemys;
std::vector<Bullet *> EntityManager::_bullets;
std::map<std::string, Entity *(*)(int, int)> EntityManager::_factory;
void (*Entity::_EntityCreator)(std::string, int, int) = EntityManager::createEntity;
const std::vector<int> *Entity::_input;

int main(void)
{
	clock_t start;
	std::vector<int> input;
	Entity::setInput(&input);

	srand(time(0));
	if (initscr() == NULL)
		ft_error("initscr failed");
	if (LINES < 20 || COLS < (SIDE_GAP * 2) + 30)
		ft_error("window too small");
	if (cbreak() == ERR)
		ft_error("cbreak fail");
	if (nodelay(stdscr, TRUE) == ERR)
		ft_error("nodelay fail");
	if (keypad(stdscr, TRUE) == ERR)
		ft_error("keypad fail");
	if (curs_set(0) == ERR)
		ft_error("curs_set fail");
	if (start_color() == ERR)
		ft_error("start_color fail");
	if (init_pair(42, COLOR_RED, COLOR_BLACK) == ERR)
		ft_error("init_pair fail");
	start = clock();
	GameState *gs;
	try {
		gs = new GameState();
	} catch (std::bad_alloc) {
		ft_error("bad alloc");
	}
	while (1)
	{
		while (clock() - start < CLOCKS_PER_SEC / FRAME_RATE)
			;
		start += CLOCKS_PER_SEC / FRAME_RATE;
		get_input(input);
		clear();
		if (update(gs, input))
			break;
	}
	endwin();
	printf("game end ! score: %ld, time: %ld\n", gs->getScore(), (clock() - gs->getStartTime()) / CLOCKS_PER_SEC);
	delete gs;
	return 0;
}

void get_input(std::vector<int> &input)
{
	int ch;
	input.clear();
	ch = getch();
	while(ch != ERR)
	{
		input.push_back(ch);
		ch = getch();
	}
}

bool update(GameState *gs, std::vector<int> input)
{
	if (std::find(input.begin(), input.end(), KEY_RESIZE) != input.end())
		ft_error("resizing window is not allowed");
	if (std::find(input.begin(), input.end(), 27) != input.end())
		return (TRUE);
	if (gs->update())
		return (TRUE);
	gs->print_data();
	refresh();
	return (FALSE);
}

void ft_error(std::string s){
	if (GameState::getInstance() != NULL)
		delete GameState::getInstance();
	endwin();
	std::cerr << s << std::endl;
	exit (1);
}
