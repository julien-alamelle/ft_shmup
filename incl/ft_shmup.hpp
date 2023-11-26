/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:26:07 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/26 22:56:28 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#define FRAME_RATE 20
#define AUTOFIRE_LENGTH 2
#define SIDE_GAP 35
#define BAD_ALLOC "bad alloc"
#define WAVE_REGEN 3
#define LIVES 5
#define get_maxy(cols) (cols - (2 * SIDE_GAP))

void ft_error(std::string s);
