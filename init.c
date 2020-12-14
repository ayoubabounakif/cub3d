/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:42:41 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/14 12:41:40 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	g_j;
static int	g_i;

void	init_mlx(void)
{
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT, "cub3D");
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT);
}

void	init_player(void)
{
	g_j = 0;
	g_sprite_count = 0;
	while (g_j < ROWS)
	{
		g_i = 0;
		while (g_i < COLS)
		{
			if (g_map[g_j][g_i] == 'N' ||
				g_map[g_j][g_i] == 'S' ||
				g_map[g_j][g_i] == 'W' ||
				g_map[g_j][g_i] == 'E')
			{
				set_rangle(g_map[g_j][g_i]);
				g_player.y = (g_j * TILE_SIZE) + TILE_SIZE / 2;
				g_player.x = (g_i * TILE_SIZE) + TILE_SIZE / 2;
			}
			else if (g_map[g_j][g_i] == '2')
				g_sprite_count++;
			g_i++;
		}
		g_j++;
	}
}

void	init_tex(void)
{
	g_tex.texOffSetX = 0;
	g_tex.texOffSetY = 0;
	g_tex.distanceFromTop = 0;
	g_tex.texelColor = 0;
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.no,
	&g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_textnorth = (int *)mlx_get_data_addr(g_tex.ptr,
	&g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.so,
	&g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_textsouth = (int *)mlx_get_data_addr(g_tex.ptr,
	&g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.we,
	&g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_textwest = (int *)mlx_get_data_addr(g_tex.ptr,
	&g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.ea,
	&g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_texteast = (int *)mlx_get_data_addr(g_tex.ptr,
	&g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
}
