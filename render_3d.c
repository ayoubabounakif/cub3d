/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:39:48 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/14 19:41:03 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	g_y;

void		draw_ceiling(int i, int wall_topp)
{
	g_y = 0;
	while (g_y < wall_topp)
	{
		img_update(i, g_y, rgb_to_int(
			g_ceiling_rgb.r, 
			g_ceiling_rgb.g,
			g_ceiling_rgb.b));
		g_y++;
	}
}

void		draw_floor(int i, int wall_botp)
{
	g_y = wall_botp;
	while (g_y < WIN_HEIGHT)
	{
		img_update(i, g_y, rgb_to_int(
			g_floor_rgb.r, 
			g_floor_rgb.g,
			g_floor_rgb.b));
		g_y++;
	}
}

void		draw_wall(int i, int wall_topp, int wall_botp, int wall_striph)
{
	g_y = wall_topp;
	if (g_rays[i].was_hit_vert)	// Calculate textureOffSetX if wallHit was Vert
		g_tex.offset_x = (int)g_rays[i].wall_hit_y % TILE_SIZE;
	else							// If the wallHit was Horz
		g_tex.offset_x = (int)g_rays[i].wall_hit_x % TILE_SIZE;
	while (g_y < wall_botp)		// Render the wall from wall_topp to wall_botp
	{
		g_tex.dist_ftop = g_y + (wall_striph / 2) - (WIN_HEIGHT / 2);
		g_tex.offset_y = g_tex.dist_ftop * ((float)TEX_HEIGHT / wall_striph);
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
		img_update(i, g_y, g_tex.color);
		g_y++;
	}
}

void		render_3d(void)
{
	int		i;
	int		wall_topp;
	int		wall_botp;
	float	dist_pplane;
	float	perp_dist;
	float	wall_striph;

	dist_pplane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	i = 0;
	while (i < WIN_WIDTH)
	{
		perp_dist = g_rays[i].distance * cosf(g_rays[i].ray_angle - g_player.rangle);
		wall_striph = (TILE_SIZE / perp_dist) * dist_pplane;
		wall_topp = (WIN_HEIGHT / 2) - (wall_striph / 2);
		wall_botp = wall_topp + wall_striph;
		draw_ceiling(i, wall_topp);
		draw_wall(i, wall_topp, wall_botp, wall_striph);
		draw_floor(i, wall_botp);
		i++;
	}
}
