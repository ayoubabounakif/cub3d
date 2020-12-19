/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_pcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:10:13 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/19 13:06:48 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

extern int	g_c;

int		tex_validity(char *buffer, int k)
{
	while (buffer[k])
	{
		if (buffer[k] == '.' || buffer[k] != ' ')
			return (k);
		k++;
	}
	return (k);
}

int		check_no_we(char *buffer)
{
	if (buffer[0] == 'N')
	{
		if (buffer[1] == 'O')
			return (0);
		else
			ft_exit("Error\nInvalid name in NO texture!\n");
	}
	else if (buffer[0] == 'W')
	{
		if (buffer[1] == 'E')
			return (1);
		else
			ft_exit("Error\nInvalid name in WE texture!\n");
	}
	return (2);
}

int		check_so_ea_s(char *buffer)
{
	if (buffer[0] == 'S')
	{
		if (buffer[1] == 'O')
			return (0);
		else if (buffer[1] == ' ' || buffer[1] == '\t')
			return (2);
		else
			ft_exit("Error\nInvalid name in SO or SP texture!\n");
	}
	else if (buffer[0] == 'E')
	{
		if (buffer[1] == 'A')
			return (1);
		else
			ft_exit("Error\nInvalid name in EA texture!\n");
	}
	return (3);
}

void	store_paths(char *buffer)
{
	if (check_no_we(buffer) == 0)
		g_data.paths.no = ft_substr(buffer,
		tex_validity(buffer, 3), ft_strlen(buffer));
	else if (check_so_ea_s(buffer) == 0)
		g_data.paths.so = ft_substr(buffer,
		tex_validity(buffer, 3), ft_strlen(buffer));
	else if (check_no_we(buffer) == 1)
		g_data.paths.we = ft_substr(buffer,
		tex_validity(buffer, 3), ft_strlen(buffer));
	else if (check_so_ea_s(buffer) == 1)
		g_data.paths.ea = ft_substr(buffer,
		tex_validity(buffer, 3), ft_strlen(buffer));
	else if (check_so_ea_s(buffer) == 2)
		g_data.paths.sp = ft_substr(buffer,
		tex_validity(buffer, 2), ft_strlen(buffer));
	g_c += 10;
}
