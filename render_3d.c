/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:39:48 by aabounak          #+#    #+#             */
/*   Updated: 2020/11/26 03:53:52 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_ceiling(int i, int wallTopPixel)
{
	int		y;

	y = 0;
	while (y < wallTopPixel)
	{
		img_update(i, y, 0x404040);
		y++;
	}
}

void		draw_floor(int i, int wallBottomPixel)
{
	int		y = wallBottomPixel;
	while (y < WIN_HEIGHT)
	{
		img_update(i, y, 0x808080);
		y++;
	}
}

void		draw_wall(int i, int wallTopPixel, int wallBottomPixel, int wallStripHeight)
{
	int		y;

	y = wallTopPixel;
	if (g_rays[i].wasHitVertical)	// Calculate textureOffSetX if wallHit was Vert
		g_tex.texOffSetX = (int)g_rays[i].wallHitY % TILE_SIZE;
	else							// If the wallHit was Horz
		g_tex.texOffSetX = (int)g_rays[i].wallHitX % TILE_SIZE;
	while (y < wallBottomPixel)		// Render the wall from wallTopPixel to wallBottomPixel
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

void		render3DProjectionPlane(int i)
{
	float	perpDistance = g_rays[i].distance * cos(g_rays[i].rayAngle - g_player.rotation_angle);
	float	distanceProjPlane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	float	projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;
	int		wallStripHeight = (int)projectedWallHeight;
	int		wallTopPixel = (WIN_HEIGHT / 2) - (wallStripHeight / 2);
	wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
	int		wallBottomPixel = (WIN_HEIGHT / 2) + (wallStripHeight / 2);
	wallBottomPixel = wallBottomPixel > WIN_HEIGHT ? WIN_HEIGHT : wallBottomPixel;

	draw_ceiling(i, wallTopPixel);
	draw_wall(i, wallTopPixel, wallBottomPixel, wallStripHeight);
	draw_floor(i, wallBottomPixel);
	ft_sprite(i);
}