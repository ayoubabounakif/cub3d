/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:07:23 by aabounak          #+#    #+#             */
/*   Updated: 2020/11/09 03:51:22 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (g_player.move_up == 1) // UP
	{
		new_player_y = g_player.y + sin(g_player.rotation_angle) * MOVEMENT_SPEED; // HYPOTENUSE
		new_player_x = g_player.x + cos(g_player.rotation_angle) * MOVEMENT_SPEED; // HYPOTENUSE 
		// Only set new player position if !colliding with the map walls
		if (!(wall_collision(new_player_x, new_player_y)))
		{
			g_player.y = new_player_y;	// Set new player position
			g_player.x = new_player_x;	// Set new player positiom
		}
	}
	if (g_player.move_left == 1) // If 0 or 123 is stroked decrease the rotation angle by rotation speed
		g_player.rotation_angle -= g_player.rotation_speed;
	if (g_player.move_down == 1) // DOWN
	{
		new_player_y = g_player.y - sin(g_player.rotation_angle) * MOVEMENT_SPEED;
		new_player_x = g_player.x - cos(g_player.rotation_angle) * MOVEMENT_SPEED;
		if (!(wall_collision(new_player_x, new_player_y)))
		{
			g_player.y = new_player_y;	// Set player position
			g_player.x = new_player_x;	// Set player position
		}
	}
	if (g_player.move_right == 1)	// If 0 or 124 is stroked increase the rotation angle by rotation speed
		g_player.rotation_angle += g_player.rotation_speed;
	mlx_destroy_image(g_mlx.mlx_ptr, g_mlx.img_ptr);
	mlx_clear_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT); // 800 = width ; 600 = height
	g_mlx.data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	castAllRays();
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	return (0);
}

int		key_pressed(int keycode)
{
	if (keycode == ESC)
		mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	if (keycode == LEFT_ARROW || keycode == A_KEY)
		g_player.move_left = 1;
	if (keycode == RIGHT_ARROW || keycode == D_KEY)
		g_player.move_right = 1;
	if (keycode == DOWN_ARROW || keycode == S_KEY)
		g_player.move_down = 1;
	if (keycode == UP_ARROW || keycode == W_KEY)
		g_player.move_up = 1;
	return (0);
}

int		key_released(int keycode)
{
	if (keycode == LEFT_ARROW || keycode == A_KEY)
        g_player.move_left = 0;
    if (keycode == RIGHT_ARROW || keycode == D_KEY)
        g_player.move_right = 0;
    if (keycode == DOWN_ARROW || keycode == S_KEY)
        g_player.move_down = 0;
    if (keycode == UP_ARROW || keycode == W_KEY)
        g_player.move_up = 0;
    return (0);
}

int		loop_key()
{
    mlx_hook(g_mlx.win_ptr, 2, 0, key_pressed, 0);
    mlx_hook(g_mlx.win_ptr, 3, 0, key_released, 0);
    deal_key();
    return (0);
}