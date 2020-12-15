/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:43:35 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 19:23:06 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		wall_collision(float x, float y)
{
	int		grid_x;
	int		grid_y;

	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	if (grid_y < 0 || grid_y >= ROWS ||
	grid_x < 0 || grid_x >= COLS)
		return (0);
	if (g_map[grid_y][grid_x] == '1' || g_map[grid_y][grid_x] == ' ')
		return (1);
	return (0);
}
