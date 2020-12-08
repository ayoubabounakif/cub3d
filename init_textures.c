/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 04:42:41 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/08 10:25:54 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initialise tex struct variables

void		init_tex()
{
	g_tex.texOffSetX = 0;
	g_tex.texOffSetY = 0;
	g_tex.distanceFromTop = 0;
	g_tex.texelColor = 0;

	g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.no, &g_tex.img_width, &g_tex.img_height);
	g_textnorth = (int *)mlx_get_data_addr(g_tex.ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);

	g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.so, &g_tex.img_width, &g_tex.img_height);
	g_textsouth = (int *)mlx_get_data_addr(g_tex.ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);

	g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.we, &g_tex.img_width, &g_tex.img_height);
	g_textwest = (int *)mlx_get_data_addr(g_tex.ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);

	g_tex.ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_data.paths.ea, &g_tex.img_width, &g_tex.img_height);
	g_texteast = (int *)mlx_get_data_addr(g_tex.ptr, &g_mlx.bpp, &g_mlx.size_line, &g_mlx.endian);
}
