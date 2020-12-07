/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:39:48 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/07 17:24:21 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	g_wallTopPixel;
float	g_wallBotPixel;

void		draw_ceiling(int i)
{
	int		y;

	y = 0;
	while (y < g_wallTopPixel)
	{
		img_update(i, y, rgb_to_int(g_ceiling_rgb.r, g_ceiling_rgb.g, g_ceiling_rgb.b));
		y++;
	}
}

void		draw_floor(int i)
{
	int		y;

	y = g_wallBotPixel;
	while (y < WIN_HEIGHT)
	{
		img_update(i, y, rgb_to_int(g_floor_rgb.r , g_floor_rgb.g, g_floor_rgb.b));
		y++;
	}
}

void		draw_wall(int i, int wallStripHeight)
{
	int		y;

	y = g_wallTopPixel;
	if (g_rays[i].wasHitVertical)	// Calculate textureOffSetX if wallHit was Vert
		g_tex.texOffSetX = (int)g_rays[i].wallHitY % TILE_SIZE;
	else							// If the wallHit was Horz
		g_tex.texOffSetX = (int)g_rays[i].wallHitX % TILE_SIZE;
	while (y < g_wallBotPixel)		// Render the wall from wallTopPixel to wallBotPixel
	{
		g_tex.distanceFromTop = y + (wallStripHeight / 2) - (WIN_HEIGHT / 2);
		g_tex.texOffSetY = g_tex.distanceFromTop * ((float)TEX_HEIGHT / wallStripHeight);
		if (g_rays[i].isRayFacingUp && !g_rays[i].wasHitVertical)
			g_tex.texelColor = g_textnorth[(TEX_WIDTH * g_tex.texOffSetY) + g_tex.texOffSetX];
		else if (g_rays[i].isRayFacingDown && !g_rays[i].wasHitVertical)
			g_tex.texelColor = g_textsouth[(TEX_WIDTH * g_tex.texOffSetY) + g_tex.texOffSetX];
		else if (g_rays[i].isRayFacingRight && g_rays[i].wasHitVertical)
			g_tex.texelColor = g_textwest[(TEX_WIDTH * g_tex.texOffSetY) + g_tex.texOffSetX];
		else if (g_rays[i].isRayFacingLeft && g_rays[i].wasHitVertical)
			g_tex.texelColor = g_texteast[(TEX_WIDTH * g_tex.texOffSetY) + g_tex.texOffSetX];
		img_update(i, y, g_tex.texelColor);
		y++;
	}
}

void		render3DProjectionPlane(void)
{
	int		i;
	float	distanceProjPlane;
	float	perpDistance;
	float	wallStripHeight;

	i = 0;
	distanceProjPlane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	while (i < WIN_WIDTH)
	{
		perpDistance = g_rays[i].distance * cosf(g_rays[i].rayAngle - g_player.rotation_angle);
		wallStripHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;
		g_wallTopPixel = (WIN_HEIGHT / 2) - (wallStripHeight / 2) + g_3d.pitch;
		g_wallBotPixel = g_wallTopPixel + wallStripHeight;
		draw_ceiling(i);
		draw_wall(i, wallStripHeight);
		draw_floor(i);
		i++;
	}
}
