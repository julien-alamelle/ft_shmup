/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:34:56 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 21:21:28 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "GameState.hpp"

long run_game(std::vector<int> &input, bool hard_mode);
void get_input(std::vector<int> &input);
bool update(GameState *gs, std::vector<int> input);
