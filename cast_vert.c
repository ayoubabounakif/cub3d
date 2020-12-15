/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:31:24 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 16:34:42 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vert(float ray_angle)
{
	g_ray.fvert_hit = FALSE;
	g_ray.offs_x = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	g_ray.offs_x += g_ray.isray_right ? TILE_SIZE : 0;
	g_ray.offs_y = g_player.y + (g_ray.offs_x - g_player.x) * tan(ray_angle);
	g_ray.xstep = TILE_SIZE;
	g_ray.xstep *= g_ray.isray_left ? -1 : 1;
	g_ray.ystep = g_ray.xstep * tan(ray_angle);
	g_ray.ystep *= (g_ray.isray_up && g_ray.ystep > 0) ? -1 : 1;
	g_ray.ystep *= (g_ray.isray_down && g_ray.ystep < 0) ? -1 : 1;
	g_ray.next_vtouch_x = g_ray.offs_x;
	g_ray.next_vtouch_y = g_ray.offs_y;
}

void	cast_vert(float ray_angle)
{
	init_vert(ray_angle);
	while (g_ray.next_vtouch_x >= 0 && g_ray.next_vtouch_x < COLS * 64 &&
	g_ray.next_vtouch_y >= 0 && g_ray.next_vtouch_y < ROWS * 64)
	{
		g_ray.x_check = g_ray.next_vtouch_x + (g_ray.isray_left ? -1 : 0);
		g_ray.y_check = g_ray.next_vtouch_y;
		if (wall_collision(g_ray.x_check, g_ray.y_check) == 1)
		{
			g_ray.fvert_hit = TRUE;
			g_ray.vert_hit_x = g_ray.next_vtouch_x;
			g_ray.vert_hit_y = g_ray.next_vtouch_y;
			break ;
		}
		else
		{
			g_ray.next_vtouch_x += g_ray.xstep;
			g_ray.next_vtouch_y += g_ray.ystep;
		}
	}
}
