/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:07:06 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/09 12:11:55 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		abs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
    return (angle);
}

int		rgb_to_int(int r, int g, int b)
{
	return ((r * (256 * 256)) + (g * (256)) + (b));
}

int		wall_collision(float x, float y)
{
	int		grid_x;
	int		grid_y;

	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	if (grid_y < 0 || grid_y >= g_sizeofmap ||
	grid_x < 0 || grid_x >= g_biglen)
        return (0);
	if (g_map[grid_y][grid_x] == '1' || g_map[grid_y][grid_x] == ' ')
		return (1);
	return (0);
}

void		draw_square(int y, int x, int size, int color)
{
	int		x_end;
	int		y_end;
	int		original_x;

	x_end = x + size;
	y_end = y + size;
	original_x = x;
	g_vars.y = y;
	while (y < y_end)
	{
		x = original_x;
		while (x < x_end)
		{
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
				g_mlx.data[x + y * WIN_WIDTH] = color;
			x++;
		}
		y++;
	}
}
