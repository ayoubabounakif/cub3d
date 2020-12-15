/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:11:18 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 19:22:23 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	store_data(int strip_id, float ray_angle)
{
	g_ray.horz_hit_dist = (g_ray.fhorz_hit)
	? distance_bpts(g_player.x, g_player.y, g_ray.horz_hit_x, g_ray.horz_hit_y)
	: (float)INT32_MAX;
	g_ray.vert_hit_dist = (g_ray.fvert_hit)
	? distance_bpts(g_player.x, g_player.y, g_ray.vert_hit_x, g_ray.vert_hit_y)
	: (float)INT32_MAX;
	g_rays[strip_id].distance = (g_ray.horz_hit_dist < g_ray.vert_hit_dist)
		? g_ray.horz_hit_dist : g_ray.vert_hit_dist;
	g_rays[strip_id].wall_hit_x = (g_ray.horz_hit_dist < g_ray.vert_hit_dist)
		? g_ray.horz_hit_x : g_ray.vert_hit_x;
	g_rays[strip_id].wall_hit_y = (g_ray.horz_hit_dist < g_ray.vert_hit_dist)
		? g_ray.horz_hit_y : g_ray.vert_hit_y;
	g_rays[strip_id].was_hit_vert = (g_ray.vert_hit_dist < g_ray.horz_hit_dist)
		? TRUE : FALSE;
	g_rays[strip_id].ray_angle = ray_angle;
	g_rays[strip_id].isray_down = ray_angle > 0 && ray_angle < M_PI;
	g_rays[strip_id].isray_up = !(ray_angle > 0 && ray_angle < M_PI);
	g_rays[strip_id].isray_right = ray_angle < H_PI || ray_angle > PI_H;
	g_rays[strip_id].isray_left = !(ray_angle < H_PI || ray_angle > PI_H);
}

void	cast_rays(void)
{
	int		strip_id;
	float	ray_angle;

	if (!(g_rays = malloc(sizeof(t_rays) * (WIN_WIDTH))))
		return ;
	strip_id = 0;
	ray_angle = g_player.rangle - RAD(30);
	ray_angle = normalize_angle(ray_angle);
	while (strip_id < WIN_WIDTH)
	{
		g_ray.isray_down = ray_angle > 0 && ray_angle < M_PI;
		g_ray.isray_up = !g_ray.isray_down;
		g_ray.isray_right = ray_angle < H_PI || ray_angle > PI_H;
		g_ray.isray_left = !g_ray.isray_right;
		cast_horz(ray_angle);
		cast_vert(ray_angle);
		store_data(strip_id, ray_angle);
		ray_angle = normalize_angle(ray_angle);
		ray_angle += FOV_ANGLE / WIN_WIDTH;
		strip_id++;
	}
}

int		main(int ac, char **av)
{
	read_file(ac, av);
	init_player();
	init_mlx();
	init_tex();
	mlx_loop_hook(g_mlx.mlx_ptr, loop_key, 0);
	mlx_loop(g_mlx.mlx_ptr);
	free_map();
	return (0);
}
