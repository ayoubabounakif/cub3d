/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:07:23 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 19:23:04 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	img_update(int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0
		&& y < WIN_HEIGHT)
		g_mlx.data[(x + (y * WIN_WIDTH))] = color;
}

int		abs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

float	distance_bpts(float x1, float y1, float x2, float y2)
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
