/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:31:37 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 19:22:06 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_horz(float ray_angle)
{
	g_ray.fhorz_hit = FALSE;
	g_ray.offs_y = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	g_ray.offs_y += g_ray.isray_down ? TILE_SIZE : 0;
	g_ray.offs_x = g_player.x + (g_ray.offs_y - g_player.y) / tan(ray_angle);
	g_ray.ystep = TILE_SIZE;
	g_ray.ystep *= g_ray.isray_up ? -1 : 1;
	g_ray.xstep = g_ray.ystep / tan(ray_angle);
	g_ray.xstep *= (g_ray.isray_left && g_ray.xstep > 0) ? -1 : 1;
	g_ray.xstep *= (g_ray.isray_right && g_ray.xstep < 0) ? -1 : 1;
	g_ray.next_htouch_x = g_ray.offs_x;
	g_ray.next_htouch_y = g_ray.offs_y;
}

void	cast_horz(float ray_angle)
{
	init_horz(ray_angle);
	while (g_ray.next_htouch_x >= 0 && g_ray.next_htouch_x < COLS * 64 &&
	g_ray.next_htouch_y >= 0 && g_ray.next_htouch_y < ROWS * 64)
	{
		g_ray.x_check = g_ray.next_htouch_x;
		g_ray.y_check = g_ray.next_htouch_y + (g_ray.isray_up ? -1 : 0);
		if (wall_collision(g_ray.x_check, g_ray.y_check) == 1)
		{
			g_ray.fhorz_hit = TRUE;
			g_ray.horz_hit_x = g_ray.next_htouch_x;
			g_ray.horz_hit_y = g_ray.next_htouch_y;
			break ;
		}
		else
		{
			g_ray.next_htouch_x += g_ray.xstep;
			g_ray.next_htouch_y += g_ray.ystep;
		}
	}
}
