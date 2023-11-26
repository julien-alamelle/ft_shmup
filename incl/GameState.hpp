/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameState.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:00:41 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 22:17:48 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "EntityManager.hpp"
#include "Background.hpp"
#include <ncurses.h>

class GameState {
	private:
		static GameState *instance;
		long score;
		long ticks;
		int waves;
		clock_t startTime;
		EntityManager entityManager;
		Background background;
		bool hard_mode;
		WINDOW *winData;
		WINDOW *winGame;
	public:
		bool update();
		void print_data();
		GameState();
		~GameState();
		static void setInstance(GameState *gs);
		static GameState *getInstance();
		long getTicks();
		long getScore();
		EntityManager *getEntityManager();
		clock_t getStartTime();
		void setMode(bool mode);
		bool getMode();
};
