/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Background.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:41:49 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 16:50:15 by jalamell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Background.hpp"
#include "ft_shmup.hpp"
#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include <string.h>
#include "GameState.hpp"

static std::vector<std::string> img1;
static std::vector<std::string> img2;
static std::vector<std::string> img3;
static std::vector<std::string> img4;

BackgroundObject::BackgroundObject(int x, int y, int ticks_before_update, std::vector<std::string> &image):x(x), y(y), ticks_before_update(ticks_before_update),image(image)
{
	this->x -= this->image.size();
}

BackgroundObject::~BackgroundObject() {
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

int BackgroundObject::update(WINDOW *win)
{
	this->render_object(win);
	
	if (GameState::getInstance()->getTicks() % this->ticks_before_update == 0)
		this->x++;
	return (this->x > LINES);
}

void BackgroundLayer::add_object()
{
	BackgroundObject *ptr = new BackgroundObject(0, 0, this->ticks_before_update, this->image);
	this->objects.push_back(ptr);
	this->objects.back()->y = 1 + (rand() % (get_maxy(COLS) - this->objects.back()->image[0].length() - 1));
}

void BackgroundLayer::update(WINDOW *win)
{
	int i = 0;
	if ((GameState::getInstance()->getTicks() % (this->ticks_before_update * COLS / density)) == 0)
		this->add_object();
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

BackgroundLayer::BackgroundLayer(int ticks_before_update, int density, std::vector<std::string> &image):ticks_before_update(ticks_before_update),density(density),image(image) {}

BackgroundLayer::~BackgroundLayer()
{
	while (this->objects.size() > 0)
	{
		delete this->objects[0];
		this->objects.erase(this->objects.begin());
	}
	this->objects.clear();
}

Background::Background() {
img1.push_back("  |  ");
img1.push_back(" \\|/ ");
img1.push_back("--X--");
img1.push_back(" /|\\ ");
img1.push_back("  |  ");

img2.push_back("/--\\");
img2.push_back("|++|");
img2.push_back("\\--/");

img3.push_back("    .---------.    ");
img3.push_back("  ./...... /.\\ \\.  ");
img3.push_back(" /   :   : \\ /   \\ ");
img3.push_back("|.................|");
img3.push_back("|_________________|");
img3.push_back("|.................|");
img3.push_back(" \\   :   :   :   / ");
img3.push_back("  \\._........._./  ");
img3.push_back("     --.___.--     ");

img4.push_back(".");

	this->layers.push_back(new BackgroundLayer(FRAME_RATE*3, COLS*3, img4));
	this->layers.push_back(new BackgroundLayer(FRAME_RATE*1, 1, img3));
	this->layers.push_back(new BackgroundLayer(FRAME_RATE/2, 10, img2));
	this->layers.push_back(new BackgroundLayer(FRAME_RATE/10, 10, img1));
}

Background::~Background() {
	for (auto l : this->layers)
		delete l;
}

void Background::update(WINDOW *win) {
	for (auto l : this->layers)
		l->update(win);
}
