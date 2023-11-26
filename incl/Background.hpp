/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Background.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:28:19 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 16:35:06 by jalamell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <ncurses.h>

class BackgroundObject {
	public:
		int x;
		int y;
		int ticks_before_update;
		std::vector<std::string> &image;
		BackgroundObject(int x, int y, int ticks_before_update, std::vector<std::string> &image);
		~BackgroundObject();
		void render_object(WINDOW *win);
		int update(WINDOW *win);
};

class BackgroundLayer {
	private:
		int ticks_before_update;
		int density;
		std::vector<BackgroundObject *> objects;
		std::vector<std::string> &image;
	public:
		void add_object();
		void update(WINDOW *win);
		BackgroundLayer(int tick_before_update, int density, std::vector<std::string> &image);
		~BackgroundLayer();
};

class Background {
	private:
		std::vector<BackgroundLayer *> layers;
	public:
		void update(WINDOW *win);
		Background();
		~Background();
};
