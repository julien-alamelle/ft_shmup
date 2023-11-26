/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Background.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:41:49 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 09:53:12 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Background.hpp"
#include "ft_shmup.hpp"
#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include <string.h>

BackgroundObject::BackgroundObject(int x, int y, int ticks_before_update):x(x), y(y), ticks_before_update(ticks_before_update), ticks_since_last(0)
{
	this->image.push_back("  _  ");
	this->image.push_back(" /+\\ ");
	this->image.push_back("|+++|");
	this->image.push_back(" \\+/ ");
	this->image.push_back("  -  ");
	this->x -= this->image.size();
}

BackgroundObject::~BackgroundObject() {
	this->image.clear();
}

void BackgroundObject::render_object(WINDOW *win)
{
	int i = 0;
	wmove(win, x, y);
	while (i < (int)image.size())
	{
		if (x + i < LINES && x + i >= 0)
		{
			wprintw(win, "%s", image[i].c_str());
		}
		i++;
		wmove(win, x + i, y);
	}
}

void Background::add_object()
{
	BackgroundObject *ptr = new BackgroundObject(0, 0, FRAME_RATE / 20);
	this->objects.push_back(ptr);
	this->objects.back()->y = rand() % (get_maxy(COLS) - this->objects.back()->image[0].length());
	ptr->ticks_since_last = this->objects.front()->ticks_since_last;
	size_t i = 0;
	while (i < this->objects.size())
	{
		this->objects[i]->ticks_since_last = 0;
		i++;
	}
}

int BackgroundObject::update(WINDOW *win)
{
	this->render_object(win);
	
	if (this->ticks_since_last >= this->ticks_before_update)
	{
		this->x++;
		this->ticks_since_last = 0;
	}
	else
		this->ticks_since_last++;
	return (this->x > LINES);
}

void Background::update(WINDOW *win)
{
	int i = 0;
	if (this->objects.size() < 15 && ticks_since_last_obj > FRAME_RATE / 2)
	{
		this->add_object();
		this->ticks_since_last_obj = 0;
	}
	else 
		this->ticks_since_last_obj++;
	while (i < (int)this->objects.size())
	{
		if (this->objects[i]->update(win))
		{
			delete this->objects[i];
			this->objects.erase(this->objects.begin() + i);
		}
		else
			i++;
	}
}

Background::Background():ticks_since_last_obj(0)
{
	
}

Background::~Background()
{
	while (this->objects.size() > 0)
	{
		delete this->objects[0];
		this->objects.erase(this->objects.begin());
	}
	this->objects.clear();
}
