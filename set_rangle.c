/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rangle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:42:12 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/14 19:29:24 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_rangle(char player_pos)
{
	if (player_pos == 'N')
		g_player.rangle = RAD(270);
	else if (player_pos == 'S')
		g_player.rangle = RAD(90);
	else if (player_pos == 'W')
		g_player.rangle = RAD(180);
	else if (player_pos == 'E')
		g_player.rangle = RAD(360);
}
