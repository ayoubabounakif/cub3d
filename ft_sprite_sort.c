/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 04:22:04 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/07 13:02:35 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_sprite_sort(void)
{
	
	int			i;
	int			j;
	float		tmp;

	i = 0;
	while (i < g_sprite_count)
	{
		j = 0;
		while (j < g_sprite_count - i - 1)
		{
			if (g_sprite[j]->distance <= g_sprite[j + 1]->distance)
			{
				tmp = g_sprite[j]->distance;
				g_sprite[j]->distance = g_sprite[j + 1]->distance;
				g_sprite[j + 1]->distance = tmp;
			}
			j++;
		}
		i++;
	}
}
