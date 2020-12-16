/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:00:33 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/16 16:34:41 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		x_win(void)
{
	mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	exit(0);
	return (0);
}

void	free_map(void)
{
	int		i;

	i = -1;
	while (++i < g_biglen)
		free(g_map[i]);
	free(g_map);
}
