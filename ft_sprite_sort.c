/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 04:22:04 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/05 14:41:17 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_sprite_sort(int n)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - i - 1)
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
