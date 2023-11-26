/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:35:21 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 13:20:20 by jalamell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include "GameState.hpp"
#include "ft_shmup.hpp"

void get_input(std::vector<int> &input);
bool update(GameState &gs, std::vector<int> input);
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
	initscr();
	cbreak();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(42, COLOR_RED, COLOR_BLACK);
	start = clock();
	GameState gs;
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
	printf("game end ! score: %ld, time: %ld\n", gs.getScore(), (clock() - gs.getStartTime()) / CLOCKS_PER_SEC);
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

bool update(GameState &gs, std::vector<int> input)
{
	if (std::find(input.begin(), input.end(), KEY_RESIZE) != input.end())
		return (TRUE);
	if (std::find(input.begin(), input.end(), 27) != input.end())
		return (TRUE);
	if (gs.update())
		return (TRUE);
	gs.print_data();
	refresh();
	return (FALSE);
}
