/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:42:41 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/04 04:44:06 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initiating my player position
// so that it spawns on the right x,y axis where 'P' is written

void	set_rotation_angle(char player_pos)
{
	if (player_pos == 'N')
		g_player.rotation_angle = RAD(270);
	else if (player_pos == 'S')
		g_player.rotation_angle = RAD(90);
	else if (player_pos == 'W')
		g_player.rotation_angle = RAD(180);
	else if (player_pos == 'E')
		g_player.rotation_angle = RAD(360);
}

void		init_player(void)
{
	g_vars.rows = 0;
	while (g_vars.rows < ROWS)
	{
		g_vars.cols = 0;
		while (g_vars.cols < COLS)
		{
			if (g_mapread[g_vars.rows][g_vars.cols] == 'N' ||
				g_mapread[g_vars.rows][g_vars.cols] == 'S' ||
				g_mapread[g_vars.rows][g_vars.cols] == 'W' ||
				g_mapread[g_vars.rows][g_vars.cols] == 'E')
			{
				set_rotation_angle(g_mapread[g_vars.rows][g_vars.cols]);
				g_player.y = g_vars.rows * TILE_SIZE + 32;
				g_player.x = g_vars.cols * TILE_SIZE + 32;
			}
			else if (g_mapread[g_vars.rows][g_vars.cols] == '2')
				g_sprite_count++;
			g_vars.cols++;
		}
		g_vars.rows++;
	}
}

void		init_sprite(void)
{
	int		i;

	g_sprite = malloc(sizeof(t_sprite *) * (g_sprite_count + 1));
	i = 0;
	g_vars.rows = 0;
	while (g_vars.rows < ROWS)
	{
		g_vars.cols = 0;
		while (g_vars.cols < COLS)
		{
			if (g_mapread[g_vars.rows][g_vars.cols] == '2')
			{
				g_sprite[i] = malloc(sizeof(t_sprite));
				g_sprite[i]->y = (g_vars.rows + 0.5) * (float)TILE_SIZE;
				g_sprite[i]->x = (g_vars.cols + 0.5) * (float)TILE_SIZE;
				g_sprite[i]->distance = distanceBetweenPoints(g_sprite[i]->x, g_sprite[i]->y,
						g_player.x, g_player.y);
				i++;
			}
			g_vars.cols++;
		}
		g_vars.rows++;
	}
	g_sprite[i] = NULL;
	ft_sprite_sort(i);
}

// Initialising my tex vars because its C
void		init_tex()
{
	g_tex.texOffSetX = 0;
	g_tex.texOffSetY = 0;
	g_tex.distanceFromTop = 0;
	g_tex.texelColor = 0;
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.no, &g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_textnorth = (int *)mlx_get_data_addr(g_tex.ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.so, &g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_textsouth = (int *)mlx_get_data_addr(g_tex.ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.we, &g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_textwest = (int *)mlx_get_data_addr(g_tex.ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
	if (!(g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.ea, &g_tex.img_width, &g_tex.img_height)))
		return (ft_exit("Error\nTexture file not found!\n"));
	g_texteast = (int *)mlx_get_data_addr(g_tex.ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
}
