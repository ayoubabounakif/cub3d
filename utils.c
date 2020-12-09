/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:07:23 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/09 10:12:56 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void	img_update(int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0
		&& y < WIN_HEIGHT)
		g_mlx.data[(x + (y * WIN_WIDTH))] = color;
}

int		deal_key()
{
	float	new_player_y;
	float	new_player_x;

	if (g_key.move_straight == 1)
	{
		new_player_y = g_player.y + sin(g_player.rotation_angle) * MOVEMENT_SPEED;
		new_player_x = g_player.x + cos(g_player.rotation_angle) * MOVEMENT_SPEED; 
		if (!(wall_collision(new_player_x, new_player_y)))
		{
			g_player.y = new_player_y;
			g_player.x = new_player_x;
		}
	}
	if (g_key.move_back == 1)
	{
		new_player_y = g_player.y - sin(g_player.rotation_angle) * MOVEMENT_SPEED;
		new_player_x = g_player.x - cos(g_player.rotation_angle) * MOVEMENT_SPEED;
		if (!(wall_collision(new_player_x, new_player_y)))
		{
			g_player.y = new_player_y;
			g_player.x = new_player_x;
		}
	}
	if (g_key.move_left == 1)
	{
		new_player_y = g_player.y - sin(g_player.rotation_angle + RAD(90)) * MOVEMENT_SPEED;
		new_player_x = g_player.x - cos(g_player.rotation_angle + RAD(90)) * MOVEMENT_SPEED;
		if (!(wall_collision(new_player_x, new_player_y)))
		{
			g_player.y = new_player_y;
			g_player.x = new_player_x;
		}
	}
	if (g_key.move_right == 1)
	{
		new_player_y = g_player.y + sin(g_player.rotation_angle + RAD(90)) * MOVEMENT_SPEED;
		new_player_x = g_player.x + cos(g_player.rotation_angle + RAD(90)) * MOVEMENT_SPEED;
		if (!(wall_collision(new_player_x, new_player_y)))
		{
			g_player.y = new_player_y;
			g_player.x = new_player_x;
		}
	}
	// CHANGING PITCH (UP DOWN)
	// if (g_key.look_up == 1 && g_3d.pitch <= 360)
	// 	g_3d.pitch += 15;
	// if (g_key.look_down == 1 && g_3d.pitch >= -360)
	// 	g_3d.pitch -= 15;
	if (g_key.left_dir == 1)
		g_player.rotation_angle -= ROTATION_SPEED;
	if (g_key.right_dir == 1)
		g_player.rotation_angle += ROTATION_SPEED;

	mlx_destroy_image(g_mlx.mlx_ptr, g_mlx.img_ptr);
	mlx_clear_window(g_mlx.mlx_ptr, g_mlx.win_ptr);

	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	g_mlx.data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	
	castAllRays();
	render3DProjectionPlane();
	ft_sprite();
	
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	return (0);
}

int		key_pressed(int keycode)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
		exit(0);
	}
    if (keycode == W_KEY)
        g_key.move_straight = 1;
    if (keycode == S_KEY)
        g_key.move_back = 1;
    if (keycode == A_KEY)
        g_key.move_left = 1;
    if (keycode == D_KEY)
        g_key.move_right = 1;
	if (keycode == LEFT_ARROW)
        g_key.left_dir = 1;
    if (keycode == RIGHT_ARROW)
        g_key.right_dir = 1;
    if (keycode == UP_ARROW)
        g_key.look_up = 1;
    if (keycode == DOWN_ARROW)
        g_key.look_down = 1;
	return (0);
}

int		key_released(int keycode)
{
    if (keycode == W_KEY)
        g_key.move_straight = 0;
    if (keycode == S_KEY)
        g_key.move_back = 0;
    if (keycode == A_KEY)
        g_key.move_left = 0;
    if (keycode == D_KEY)
        g_key.move_right = 0;
	if (keycode == LEFT_ARROW)
        g_key.left_dir = 0;
    if (keycode == RIGHT_ARROW)
        g_key.right_dir = 0;
    if (keycode == UP_ARROW)
        g_key.look_up = 0;
    if (keycode == DOWN_ARROW)
        g_key.look_down = 0;
    return (0);
}

int		loop_key()
{
    mlx_hook(g_mlx.win_ptr, 2, 0, key_pressed, 0);
    mlx_hook(g_mlx.win_ptr, 3, 0, key_released, 0);
    deal_key();
    return (0);
}