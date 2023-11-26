/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:26:07 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 19:03:52 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#define FRAME_RATE 20
#define SIDE_GAP 35
#define BAD_ALLOC "bad alloc"
#define WAVE_REGEN 3
#define get_maxy(cols) (cols - (2 * SIDE_GAP))
#define HARD_MODE FALSE

void ft_error(std::string s);
