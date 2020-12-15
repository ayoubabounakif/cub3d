/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:39:48 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 17:07:31 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	g_wall_topp;
static int	g_wall_botp;
static int	g_y;

void		draw_ceiling(int i)
{
	g_y = -1;
	while (++g_y < g_wall_topp)
	{
		img_update(i, g_y, rgb_to_int(
			g_ceiling_rgb.r,
			g_ceiling_rgb.g,
			g_ceiling_rgb.b));
	}
}

void		draw_floor(int i)
{
	g_y = g_wall_botp - 1;
	while (++g_y < WIN_HEIGHT)
	{
		img_update(i, g_y, rgb_to_int(
			g_floor_rgb.r,
			g_floor_rgb.g,
			g_floor_rgb.b));
	}
}

void		draw_wall(int i, int wall_striph)
{
	g_y = g_wall_topp - 1;
	g_tex.offset_x = g_rays[i].was_hit_vert ?
		(int)g_rays[i].wall_hit_y % 64 : (int)g_rays[i].wall_hit_x % 64;
	while (++g_y < g_wall_botp)
	{
		g_tex.dist_ftop = g_y + (wall_striph / 2) - (WIN_HEIGHT / 2);
		g_tex.offset_y = g_tex.dist_ftop * ((float)TEX_HEIGHT / wall_striph);
		if ((TEX_WIDTH * g_tex.offset_y + g_tex.offset_x) > 0)
		{
			if (g_rays[i].isray_up && !g_rays[i].was_hit_vert)
				g_tex.color = g_texnorth[(TEX_WIDTH * g_tex.offset_y)
									+ g_tex.offset_x];
			else if (g_rays[i].isray_down && !g_rays[i].was_hit_vert)
				g_tex.color = g_texsouth[(TEX_WIDTH * g_tex.offset_y)
									+ g_tex.offset_x];
			else if (g_rays[i].isray_right && g_rays[i].was_hit_vert)
				g_tex.color = g_texwest[(TEX_WIDTH * g_tex.offset_y)
									+ g_tex.offset_x];
			else if (g_rays[i].isray_left && g_rays[i].was_hit_vert)
				g_tex.color = g_texeast[(TEX_WIDTH * g_tex.offset_y)
									+ g_tex.offset_x];
		}
		img_update(i, g_y, g_tex.color);
	}
}

void		render_3d(void)
{
	int		i;
	float	dist_pplane;
	float	perp_dist;
	float	wall_striph;

	dist_pplane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		perp_dist = g_rays[i].distance * cosf(
			g_rays[i].ray_angle - g_player.rangle);
		wall_striph = (TILE_SIZE / perp_dist) * dist_pplane;
		g_wall_topp = (WIN_HEIGHT / 2) - (wall_striph / 2);
		g_wall_botp = g_wall_topp + wall_striph;
		draw_ceiling(i);
		draw_wall(i, wall_striph);
		draw_floor(i);
	}
}
