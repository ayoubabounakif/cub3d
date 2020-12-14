/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 04:22:04 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/14 10:51:43 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_sprite_sort(void)
{
	
	int			i;
	int			j;
	t_sprite	*tmp;

	i = 0;
	while (i < g_sprite_count)
	{
		j = 0;
		while (j < g_sprite_count - i - 1)
		{
			if (g_sprite[j]->distance <= g_sprite[j + 1]->distance)
			{
				tmp = g_sprite[j];
				g_sprite[j] = g_sprite[j + 1];
				g_sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void		init_sprite(void)
{
	int		i;

	if (!(g_sprite = malloc(sizeof(t_sprite *) * (g_sprite_count + 1))))
		return ;
	i = 0;
	g_vars.rows = 0;
	while (g_vars.rows < ROWS)
	{
		g_vars.cols = 0;
		while (g_vars.cols < COLS)
		{
			if (g_map[g_vars.rows][g_vars.cols] == '2')
			{
				if (!(g_sprite[i] = malloc(sizeof(t_sprite))))
					return ;
				g_sprite[i]->y = (g_vars.rows * TILE_SIZE) + TILE_SIZE / 2;
				g_sprite[i]->x = (g_vars.cols * TILE_SIZE) + TILE_SIZE / 2;
				g_sprite[i]->distance = distanceBetweenPoints(
						g_sprite[i]->y, g_sprite[i]->x,
						g_player.y, g_player.x);
				i++;
			}
			g_vars.cols++;
		}
		g_vars.rows++;
	}
	g_sprite[i] = NULL;
	ft_sprite_sort();
}
