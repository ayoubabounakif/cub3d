/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_spacers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:52:12 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 19:22:42 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char	get_fchar(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == ' ')
			i++;
		else if (buffer[i] == '1' || buffer[i] == '0')
			return (1);
		else
			break ;
		i++;
	}
	return (0);
}

char	*spacer(char *buffer, int biglen)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(str = malloc(sizeof(char) * (biglen + 1))))
		return (0);
	str[i] = ' ';
	i++;
	while (buffer[j])
	{
		str[i] = buffer[j];
		j++;
		i++;
	}
	while (i < biglen)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*space_filler(int biglen)
{
	char	*str;
	int		i;

	if (!(str = malloc(sizeof(char) * (biglen + 1))))
		return (0);
	i = 0;
	while (i < biglen)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}
