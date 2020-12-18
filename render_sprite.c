/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 05:24:27 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/18 18:50:50 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	render_sprite(int k, int x_fs, int y_fs, int sp_size)
{
	int		i;
	int		j;
	int		color;

	i = -1;
	while (++i < sp_size)
	{
		if (x_fs + i < 0 || x_fs + i > WIN_WIDTH)
			continue ;
		if (x_fs + i < WIN_WIDTH)
			if (g_rays[x_fs + i].distance < g_sprite[k]->distance)
				continue ;
		j = -1;
		while (++j < sp_size)
		{
			if (y_fs + j < 0 || y_fs + j > WIN_HEIGHT)
				continue ;
			color = g_sprite[k]->data[g_sprite[k]->width * (j *
					g_sprite[k]->height / sp_size) +
					(i * g_sprite[k]->width / sp_size)];
			if (color)
				img_update(x_fs + i, y_fs + j, color);
		}
	}
}

void	ft_sprite_traits(int i)
{
	float	x_offset;
	float	y_offset;
	float	sp_angle;
	float	sp_size;

	g_player.rangle = normalize_angle(g_player.rangle);
	sp_angle = atan2(-g_player.y + (g_sprite[i]->y),
							-g_player.x + (g_sprite[i]->x));
	while (sp_angle - g_player.rangle > M_PI)
		sp_angle -= TWO_PI;
	while (sp_angle - g_player.rangle < -M_PI)
		sp_angle += TWO_PI;
	sp_size = (WIN_WIDTH / g_sprite[i]->distance * TILE_SIZE);
	x_offset = (sp_angle - g_player.rangle) /
		RAD(60) * WIN_WIDTH + (WIN_WIDTH / 2 - sp_size / 2);
	y_offset = (WIN_HEIGHT / 2 - sp_size / 2);
	render_sprite(i, x_offset, y_offset, sp_size);
}

void	ft_sprite(void)
{
	int		i;

	update_sprite();
	i = -1;
	while (++i < g_sprite_count)
		ft_sprite_traits(i);
}
