/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Background.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:28:19 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/25 21:14:58 by ccouble          ###   ########.fr       */
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
		int	ticks_since_last;
		std::vector<std::string> image;
		BackgroundObject(int x, int y, int ticks_before_update);
		~BackgroundObject();
		void render_object(WINDOW *win);
		int update(WINDOW *win);
};

class Background {
	private:
		int ticks_since_last_obj;
		std::vector<BackgroundObject *> objects;
	public:
		void add_object();
		void update(WINDOW *win);
		Background();
		~Background();
};
