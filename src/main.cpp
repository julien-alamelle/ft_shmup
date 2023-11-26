/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:35:21 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 23:33:03 by ccouble          ###   ########.fr       */
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
#include "Game.hpp"

std::vector<Enemy *> EntityManager::_enemys;
std::vector<Bullet *> EntityManager::_bullets;
std::vector<PowerUp *> EntityManager::_powerUp;
std::map<std::string, Entity *(*)(int, int, int)> EntityManager::_factory;
void (*Entity::_EntityCreator)(std::string, int, int, int) = EntityManager::createEntity;
const std::vector<int> *Entity::_input;
int menu(std::vector<int> &input);

int main(void)
{
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
	if (init_pair(23, COLOR_WHITE, COLOR_BLUE) == ERR)
		ft_error("init_pair fail");
	if (init_pair(69, COLOR_GREEN, COLOR_BLACK) == ERR)
		ft_error("init_pair fail");
	return (menu(input));
}

int menu(std::vector<int> &input){
	clock_t start = clock();
	int pos = 0;
	long score = 0;
	while (1)
	{
		clear();
		while (clock() - start < CLOCKS_PER_SEC / FRAME_RATE)
			;
		start += CLOCKS_PER_SEC / FRAME_RATE;
		get_input(input);
		if (std::find(input.begin(), input.end(), KEY_RESIZE) != input.end())
			ft_error("no resize pt2");
		if (std::find(input.begin(), input.end(), KEY_UP) != input.end())
			pos--;
		if (std::find(input.begin(), input.end(), KEY_DOWN) != input.end())
			pos++;
		if (std::find(input.begin(), input.end(), '\n') != input.end())
		{
			if (pos == 0)
			{
				long scoretmp = run_game(input, FALSE);
				if (scoretmp > score)
					score = scoretmp;
			}
			if (pos == 1)
			{
				long scoretmp = run_game(input, TRUE);
				if (scoretmp > score)
					score = scoretmp;

			}
			if (pos == 2)
			{
				endwin();
				return 0;
			}
		}
		if (pos < 0)
			pos = 0;
		if (pos > 2)
			pos = 2;
		box(stdscr, 0, 0);
		std::string s = "Play";
		if (pos == 0)
			wattron(stdscr, A_UNDERLINE);
		wmove(stdscr, (LINES / 2) - 1, (COLS / 2) - (s.length() / 2));
		if (wprintw(stdscr, "%s", s.c_str()) == ERR)
			ft_error(BAD_ALLOC);
		wattroff(stdscr, A_UNDERLINE);

		s = "Hard mode";
		if (pos == 1)
			wattron(stdscr, A_UNDERLINE);
		wmove(stdscr, (LINES / 2) + 1, (COLS / 2) - (s.length() / 2));
		if (wprintw(stdscr, "%s", s.c_str()) == ERR)
			ft_error(BAD_ALLOC);
		wattroff(stdscr, A_UNDERLINE);

		s = "Exit";
		if (pos == 2)
			wattron(stdscr, A_UNDERLINE);
		wmove(stdscr, (LINES / 2) + 3, (COLS / 2) - (s.length() / 2));
		if (wprintw(stdscr, "%s", s.c_str()) == ERR)
			ft_error(BAD_ALLOC);
		wattroff(stdscr, A_UNDERLINE);
		wmove(stdscr, (LINES / 2) + 5, (COLS / 2) - 5);
		if (wprintw(stdscr, "highscore: %ld", score) == ERR)
			ft_error(BAD_ALLOC);
		refresh();
	}
}

void ft_error(std::string s){
	if (GameState::getInstance() != NULL)
		delete GameState::getInstance();
	endwin();
	std::cerr << s << std::endl;
	exit (1);
}
