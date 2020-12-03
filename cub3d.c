 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:11:18 by aabounak          #+#    #+#             */
/*   Updated: 2020/11/09 05:13:45 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	g_c;

void		castHorzRay(float rayAngle)
{
	///////////////////////////////////////////
	// HORIZONTAL RAY-GRID INTERSECTION CODE //
	///////////////////////////////////////////

	g_ray.foundHorzWallHit = FALSE;

	// Find the y-coordinate of the closest horizontal grid intersection
	g_ray.yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	g_ray.yintercept += g_ray.isRayFacingDown ? TILE_SIZE : 0;
	
	// Find the x-coordinate of the closest horizontal grid intersection
	g_ray.xintercept = g_player.x + (g_ray.yintercept - g_player.y) / tan(rayAngle);

	// Calculate the increment xstep and ystep
	g_ray.ystep = TILE_SIZE;
	g_ray.ystep *= g_ray.isRayFacingUp ? -1 : 1;

	g_ray.xstep = g_ray.ystep / tan(rayAngle);
	g_ray.xstep *= (g_ray.isRayFacingLeft && g_ray.xstep > 0) ? -1 : 1;
	g_ray.xstep *= (g_ray.isRayFacingRight && g_ray.xstep < 0) ? -1 : 1; 

	g_ray.nextHorzTouchX = g_ray.xintercept;
	g_ray.nextHorzTouchY = g_ray.yintercept;

	// Increment xstep and ystep until we find a wall
	while (g_ray.nextHorzTouchX >= 0 && g_ray.nextHorzTouchX < WIN_WIDTH && 
	g_ray.nextHorzTouchY >= 0 && g_ray.nextHorzTouchY < WIN_HEIGHT)
	{
		g_ray.xToCheck = g_ray.nextHorzTouchX;
		g_ray.yToCheck = g_ray.nextHorzTouchY + (g_ray.isRayFacingUp ? -1 : 0);
		if (wall_collision(g_ray.xToCheck, g_ray.yToCheck) == 1)	// If wall is found
		{
			g_ray.foundHorzWallHit = TRUE;
			g_ray.horzWallHitX = g_ray.nextHorzTouchX;
			g_ray.horzWallHitY = g_ray.nextHorzTouchY;
			g_ray.horzWallContent = g_mapread[(int)floor(g_ray.yToCheck / TILE_SIZE)][(int)floor(g_ray.xToCheck / TILE_SIZE)];
			break ;
		}
		else
		{
			g_ray.nextHorzTouchX += g_ray.xstep;
			g_ray.nextHorzTouchY += g_ray.ystep;
		}
	}
}

void		castVertRay(float rayAngle)
{
	///////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE ////
	///////////////////////////////////////////

	g_ray.foundVertWallHit = FALSE;

	// Find the x-coordinate of the closest VERTICAL grid intersection
	g_ray.xintercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	g_ray.xintercept += g_ray.isRayFacingRight ? TILE_SIZE : 0;
	
	// Find the y-coordinate of the closest VERTICAL grid intersection
	g_ray.yintercept = g_player.y + (g_ray.xintercept - g_player.x) * tan(rayAngle);

	// Calculate the increment xstep and ystep
	g_ray.xstep = TILE_SIZE;
	g_ray.xstep *= g_ray.isRayFacingLeft ? -1 : 1;

	g_ray.ystep = g_ray.xstep * tan(rayAngle);
	g_ray.ystep *= (g_ray.isRayFacingUp && g_ray.ystep > 0) ? -1 : 1;
	g_ray.ystep *= (g_ray.isRayFacingDown && g_ray.ystep < 0) ? -1 : 1; 

	g_ray.nextVertTouchX = g_ray.xintercept;
	g_ray.nextVertTouchY = g_ray.yintercept;

	// Increment xstep and ystep until we find a wall
	while (g_ray.nextVertTouchX >= 0 && g_ray.nextVertTouchX < WIN_WIDTH &&
	g_ray.nextVertTouchY >= 0 && g_ray.nextVertTouchY < WIN_HEIGHT)
	{
		g_ray.xToCheck = g_ray.nextVertTouchX + (g_ray.isRayFacingLeft ? -1 : 0);
		g_ray.yToCheck = g_ray.nextVertTouchY;
		if (wall_collision(g_ray.xToCheck, g_ray.yToCheck) == 1)	// Found a wall
		{
			g_ray.foundVertWallHit = TRUE;
			g_ray.vertWallHitX = g_ray.nextVertTouchX;
			g_ray.vertWallHitY = g_ray.nextVertTouchY;
			g_ray.vertWallContent = g_mapread[(int)floor(g_ray.yToCheck / TILE_SIZE)][(int)floor(g_ray.xToCheck / TILE_SIZE)];
			break ;
		}
		else
		{
			g_ray.nextVertTouchX += g_ray.xstep;
			g_ray.nextVertTouchY += g_ray.ystep;
		}
	}
}

void		castAllRays()
{
	int		stripId = 0;
	float	rayAngle = g_player.rotation_angle - RAD(30);

	g_rays = malloc(sizeof(t_rays) * NUM_RAYS);
	rayAngle = normalize_angle(rayAngle);
	ft_bzero(&g_ray, sizeof(t_ray));

	while (stripId < NUM_RAYS)
	{
		g_ray.isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
		g_ray.isRayFacingUp = !g_ray.isRayFacingDown;

		g_ray.isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
		g_ray.isRayFacingLeft = !g_ray.isRayFacingRight;
				
		castVertRay(rayAngle);
		castHorzRay(rayAngle);

		// Calculate both Horz and Vert hit distances and choose the smallest one
		g_ray.horzHitDistance = (g_ray.foundHorzWallHit)
		? distanceBetweenPoints(g_player.x, g_player.y, g_ray.horzWallHitX, g_ray.horzWallHitY)
		: INT32_MAX;
		g_ray.vertHitDistance = (g_ray.foundVertWallHit)
		? distanceBetweenPoints(g_player.x, g_player.y, g_ray.vertWallHitX, g_ray.vertWallHitY)
		: INT32_MAX;

		g_rays[stripId].distance = (g_ray.horzHitDistance < g_ray.vertHitDistance) ? g_ray.horzHitDistance : g_ray.vertHitDistance;
		g_rays[stripId].wallHitX = (g_ray.horzHitDistance < g_ray.vertHitDistance) ? g_ray.horzWallHitX : g_ray.vertWallHitX;
		g_rays[stripId].wallHitY = (g_ray.horzHitDistance < g_ray.vertHitDistance) ? g_ray.horzWallHitY : g_ray.vertWallHitY;
		g_rays[stripId].wallHitContent = (g_ray.horzHitDistance < g_ray.vertHitDistance) ? g_ray.horzWallContent : g_ray.vertWallContent;
		g_rays[stripId].wasHitVertical = (g_ray.vertHitDistance < g_ray.horzHitDistance) ? TRUE : FALSE;
		g_rays[stripId].rayAngle = rayAngle;
		g_rays[stripId].isRayFacingDown = g_ray.isRayFacingDown;
		g_rays[stripId].isRayFacingUp = g_ray.isRayFacingUp;
		g_rays[stripId].isRayFacingLeft = g_ray.isRayFacingLeft;
		g_rays[stripId].isRayFacingRight = g_ray.isRayFacingRight;
	
		rayAngle += RAD(RAD((FOV_ANGLE) / NUM_RAYS));	// Incrementing the ray after each ray casted
		rayAngle = normalize_angle(rayAngle);
		// draw_line(g_player.x, g_player.y, g_rays[stripId].wallHitX, g_rays[stripId].wallHitY, 0xFFFFFF);
		render3DProjectionPlane(stripId); // Rendering 3D after each ray casted
		stripId++;
	}
	ft_sprite();
	// draw_map();
}

int		main(void)
{
	g_sprite_count = 0;
	read_file();
	init_player();

	g_player.rotation_speed = (float)ROTATION_SPEED;
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	g_mlx.data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);

	init_tex();
	printf("%d\n", g_sprite_count);
	mlx_loop_hook(g_mlx.mlx_ptr, loop_key, 0);
	mlx_loop(g_mlx.mlx_ptr);
	return (0);
}
