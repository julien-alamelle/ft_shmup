/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:35:21 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/25 14:18:56 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <ctime>
#include <vector>
#include <algorithm>
#define FRAME_RATE 60

void get_input(std::vector<int> &input);
int	 update(WINDOW *win, std::vector<int> input);

int main(void)
{
	clock_t start;

	WINDOW *win;
	std::vector<int> input;

	win = initscr();
	cbreak();
	nodelay(win, TRUE);
	keypad(win, TRUE);
	start = clock();
	while (1)
	{
		while (clock() - start < CLOCKS_PER_SEC / FRAME_RATE)
			;
		start += CLOCKS_PER_SEC / FRAME_RATE;
		clear();
		get_input(input);
		// ;
		if (update(win, input))
			break;
		refresh();
	}
	endwin();
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

int update(WINDOW *win, std::vector<int> input)
{
	(void)win;
	if (std::find(input.begin(), input.end(), KEY_RESIZE) != input.end())
		return (1);
	printw("Hello World %d", std::find(input.begin(), input.end(), KEY_LEFT) != input.end());
	move(LINES-1, COLS-1);
	addch('.');
	return (0);
}
