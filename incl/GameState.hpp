/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameState.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:00:41 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/25 20:26:39 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EntityManager.hpp"
#include "Background.hpp"
#include <ncurses.h>

class GameState {
	private:
		int score;
		int ticks;
		clock_t startTime;
		EntityManager entityManager;
		Background background;
	public:
		WINDOW *winData;
		void update();
		void print_data();
		GameState();
		~GameState();
};
