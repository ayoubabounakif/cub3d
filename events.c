/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:14:26 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 19:22:26 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

extern int	g_save;

void	update(void)
{
	if (g_key.move_straight == 1)
	{
		if (!(wall_collision(g_player.x + cos(g_player.rangle) * 50,
							g_player.y + sin(g_player.rangle) * 50)))
		{
			g_player.y += sin(g_player.rangle) * 7;
			g_player.x += cos(g_player.rangle) * 7;
		}
	}
	if (g_key.move_back == 1)
	{
		if (!(wall_collision(g_player.x - cos(g_player.rangle) * 50,
							g_player.y - sin(g_player.rangle) * 50)))
		{
			g_player.y -= sin(g_player.rangle) * 7;
			g_player.x -= cos(g_player.rangle) * 7;
		}
	}
	if (g_key.left_dir == 1)
		g_player.rangle -= ROTATION_SPEED;
	if (g_key.right_dir == 1)
		g_player.rangle += ROTATION_SPEED;
}

int		deal_key(void)
{
	mlx_destroy_image(g_mlx.mlx_ptr, g_mlx.img_ptr);
	mlx_clear_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	g_mlx.data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &g_mlx.bpp
										, &g_mlx.size_line, &g_mlx.endian);
	cast_rays();
	render_3d();
	ft_sprite();
	if (g_save == 1)
	{
		bmp_save();
		exit(0);
	}
	update();
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
	if (keycode == W_KEY || keycode == UP_ARROW)
		g_key.move_straight = 1;
	if (keycode == S_KEY || keycode == DOWN_ARROW)
		g_key.move_back = 1;
	if (keycode == A_KEY || keycode == LEFT_ARROW)
		g_key.left_dir = 1;
	if (keycode == D_KEY || keycode == RIGHT_ARROW)
		g_key.right_dir = 1;
	return (0);
}

int		key_released(int keycode)
{
	if (keycode == W_KEY || keycode == UP_ARROW)
		g_key.move_straight = 0;
	if (keycode == S_KEY || keycode == DOWN_ARROW)
		g_key.move_back = 0;
	if (keycode == A_KEY || keycode == LEFT_ARROW)
		g_key.left_dir = 0;
	if (keycode == D_KEY || keycode == RIGHT_ARROW)
		g_key.right_dir = 0;
	return (0);
}

int		loop_key(void)
{
	mlx_hook(g_mlx.win_ptr, 2, 0, key_pressed, 0);
	mlx_hook(g_mlx.win_ptr, 3, 0, key_released, 0);
	deal_key();
	return (0);
}
