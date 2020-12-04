/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:07:06 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/04 04:44:10 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		abs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
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
	unsigned int		mapGridIndexX;
	unsigned int		mapGridIndexY;

	mapGridIndexX = floor(x / TILE_SIZE);
	mapGridIndexY = floor(y / TILE_SIZE);
	if (g_mapread[mapGridIndexY][mapGridIndexX] == '0' ||
		g_mapread[mapGridIndexY][mapGridIndexX] == 'N' ||
		g_mapread[mapGridIndexY][mapGridIndexX] == 'S' ||
		g_mapread[mapGridIndexY][mapGridIndexX] == 'W' || 
		g_mapread[mapGridIndexY][mapGridIndexX] == 'E')
		return (0);
	else if (g_mapread[mapGridIndexY][mapGridIndexX] == '1' ||
			g_mapread[mapGridIndexY][mapGridIndexX] == ' ')
		return (1);
	else if (g_mapread[mapGridIndexY][mapGridIndexX] == '2')
		return (2);
	else if (x < 0 && x >= WIN_WIDTH && y < 0 && y >= WIN_HEIGHT)	// OUTSIDE THE BOUNDARIES
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
