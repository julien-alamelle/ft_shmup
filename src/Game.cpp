/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:32:25 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 21:03:24 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include <vector>
#include <algorithm>
#include "GameState.hpp"
#include "ft_shmup.hpp"

void get_input(std::vector<int> &input);
bool update(GameState *gs, std::vector<int> input);

int run_game(std::vector<int> &input) {
	clock_t start = clock();
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
	long score = gs->getScore();
	delete gs;
	return score;
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
