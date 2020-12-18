/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:42:41 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/18 19:07:59 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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

void	init_rays(void)
{
	if (!(g_rays = malloc(sizeof(t_rays) * (WIN_WIDTH))))
		return ;
}

void	init_sprite(void)
{
	int		spt_id;

	spt_id = 0;
	if (!(g_sprite = malloc(sizeof(t_sprite *) * (g_sprite_count + 1))))
		return ;
	while (spt_id < g_sprite_count)
	{
		if (!(g_sprite[spt_id] = malloc(sizeof(t_sprite))))
			return ;
		if (!(g_sprite[spt_id]->ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr,
		g_data.paths.sp, &g_sprite[spt_id]->width, &g_sprite[spt_id]->height)))
			ft_exit("Error\nSprite texture file not valid\n");
		g_sprite[spt_id]->data = (int *)mlx_get_data_addr(g_sprite[spt_id]->ptr,
		&g_sprite[spt_id]->bpp,
		&g_sprite[spt_id]->size_line,
		&g_sprite[spt_id]->endian);
		spt_id++;
	}
	g_sprite[spt_id] = NULL;
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
	g_tex.offset_x = 0;
	g_tex.offset_y = 0;
	g_tex.dist_ftop = 0;
	g_tex.color = 0;
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.no,
	&g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_texnorth = (int *)mlx_get_data_addr(g_tex.ptr,
	&g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.so,
	&g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_texsouth = (int *)mlx_get_data_addr(g_tex.ptr,
	&g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.we,
	&g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_texwest = (int *)mlx_get_data_addr(g_tex.ptr,
	&g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.ea,
	&g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_texeast = (int *)mlx_get_data_addr(g_tex.ptr,
	&g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
}
