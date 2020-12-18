/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:47:42 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/18 18:54:07 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		x_win(void)
{
	mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	exit(0);
	return (0);
}

void	free_sprite(void)
{
	int		i;

	i = -1;
	while (++i < g_sprite_count)
		free(g_sprite[i]);
	free(g_sprite);
}

void	free_map(void)
{
	int		i;

	i = -1;
	while (++i < g_biglen)
		free(g_map[i]);
	free(g_map);
}
