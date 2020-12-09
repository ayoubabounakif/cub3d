/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 03:21:29 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/09 10:32:16 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(int X0, int Y0, int X1, int Y1, int color)
{
    // calculate dx & dy
	int		dx = X1 - X0;
	int		dy = Y1 - Y0;
	int		i = 0;
    // calculate steps required for generating pixels
	int		steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    // calculate increment in x & y for each steps
	float	Xinc = dx / (float) steps;
	float	Yinc = dy / (float) steps;
    // Put pixel for each step
	float	X = X0;
	float	Y = Y0;
	while (i <= steps)
	{
		img_update(X ,Y , color);  // put pixel at (X,Y)
		X += Xinc;           // increment in x at each step
		Y += Yinc;           // increment in y at each step
		i++;
	}
}

void	put_character()
{
	float	phi;
	float	val;
	int		r;
	float	x;
	float	y;

	val = g_player.rotation_angle;
	r = 4;
	while (r >= 0)
	{
		phi = 0;
		while (phi <= 360)
		{
			y = (g_player.y) + (r * sin(phi * val));
			x = (g_player.x) + (r * cos(phi * val));
			if (x >= 0 && x < WIN_WIDTH &&
			y >= 0 && y < WIN_HEIGHT)
				img_update(x, y, 0xff0000);
			phi += 0.1;
		}
		r--;
	}
}

void	drawemptysquare(int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (i == 0 || i == TILE_SIZE -1 || j == 0 || j == TILE_SIZE -1)
				img_update((x + i), (y + j), color);
			j++;
		}
		i++;
	}
}

void	drawsquare(int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			img_update((x + i), (y + j), color);
			j++;
		}
		i++;
	}
}

void	draw_map()
{
	int		x = 0;
	int		y = 0;
	int		i = -1;
	int		j;
	while (++i < ROWS)
	{
		j = -1;
		x = 0;
		while (++j < COLS)
		{
			if (g_map[i][j] == '1')
				drawsquare(x, y, 0x00FF00);
			else if (g_map[i][j] == '2')
				drawsquare(x, y, 0x0000FF);
			else
				drawemptysquare(x, y, 0xFFFFFF);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	put_character();
}
