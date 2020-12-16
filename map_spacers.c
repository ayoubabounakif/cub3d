/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_spacers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:52:12 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/16 12:13:58 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char	get_fchar(char *buffer)
{
	int		i;
	int		brute_force;

	i = 0;
	brute_force = 0;
	while (buffer[i])
	{
		brute_force = i;
		if (buffer[i] == ' ')
			i = brute_force;
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

int		is_notmap(char *buffer)
{
	int		i;

	i = 0;
	if (buffer[i] != ' ' && buffer[i] != '1')
		return (1);
	while (buffer[i] == ' ')
	{
		if (buffer[i] != '1' && buffer[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int		is_notmap_init(void)
{
	t_list		*temp;

	temp = g_file;
	while (temp)
	{
		if (get_fchar((char *)temp->content))
			break ;
		temp = temp->next;
	}
	while (temp)
	{
		if (is_notmap((char *)temp->content))
			return (1);
		temp = temp->next;
	}
	return (0);
}
