/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:39:48 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/09 14:39:04 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_ceiling(int i, int wallTopPixel)
{
	int		y;

	y = 0;
	while (y < wallTopPixel)
	{
		img_update(i, y, rgb_to_int(g_ceiling_rgb.r, g_ceiling_rgb.g, g_ceiling_rgb.b));
		y++;
	}
}

void		draw_floor(int i, int wallBotPixel)
{
	int		y;

	y = wallBotPixel;
	while (y < WIN_HEIGHT)
	{
		img_update(i, y, rgb_to_int(g_floor_rgb.r , g_floor_rgb.g, g_floor_rgb.b));
		y++;
	}
}

void		draw_wall(int i, int wallTopPixel, int wallBotPixel, int wallStripHeight)
{
	int		y;

	y = wallTopPixel;
	if (g_rays[i].wasHitVertical)	// Calculate textureOffSetX if wallHit was Vert
		g_tex.texOffSetX = (int)g_rays[i].wallHitY % TILE_SIZE;
	else							// If the wallHit was Horz
		g_tex.texOffSetX = (int)g_rays[i].wallHitX % TILE_SIZE;
	while (y < wallBotPixel)		// Render the wall from wallTopPixel to wallBotPixel
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
	int		wallTopPixel;
	int		wallBotPixel;
	float	distanceProjPlane;
	float	perpDistance;
	float	wallStripHeight;

	distanceProjPlane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	i = 0;
	while (i < WIN_WIDTH)
	{
		perpDistance = g_rays[i].distance * cosf(g_rays[i].rayAngle - g_player.rotation_angle);
		wallStripHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;
		wallTopPixel = (WIN_HEIGHT / 2) - (wallStripHeight / 2) + g_3d.pitch;
		wallBotPixel = wallTopPixel + wallStripHeight;
		draw_ceiling(i, wallTopPixel);
		draw_wall(i, wallTopPixel, wallBotPixel, wallStripHeight);
		draw_floor(i, wallBotPixel);
		i++;
	}
}
