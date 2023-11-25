/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Background.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:28:19 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/25 17:55:42 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

class BackgroundObject {
	public:
		int x;
		int y;
		int ticks_before_update;
		int	ticks_since_last;
		std::vector<std::string> image;
		BackgroundObject(int x, int y, int ticks_before_update);
		~BackgroundObject();
		void render_object();
		int update();
};

class Background {
	private:
		int ticks_since_last_obj;
		std::vector<BackgroundObject *> objects;
	public:
		void add_object();
	void update();
	Background();
	~Background();
};
