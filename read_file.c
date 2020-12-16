/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 01:29:50 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/16 12:33:26 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		g_c;

void		resolution(char *buffer)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split(buffer, ' ');
	if (!ft_isnum(str[0]) || !ft_isnum(str[1]))
		ft_exit("Error\nLetters or negative value!\n");
	if (ft_strlendoubleptr(str) != 2)
		ft_exit("Error\nWrong number of arguments in Resolution!\n");
	else
	{
		g_data.win_width = (ft_atoi(str[0]) > 2560) ? 2560 : ft_atoi(str[0]);
		g_data.win_height = (ft_atoi(str[1]) > 1440) ? 1440 : ft_atoi(str[1]);
		g_c++;
	}
}

void		ft_floor(char *buffer)
{
	char	**str;

	str = ft_split(buffer, ',');
	buffer = ft_strtrim(buffer + 1, "\t");
	check_comma(buffer);
	if (all_n(str[0]) && all_n(str[1]) && all_n(str[2]) && !str[3])
	{
		if (ft_atoi(str[0]) >= 0 && ft_atoi(str[0]) < 256
			&& ft_atoi(str[1]) >= 0 && ft_atoi(str[1]) < 256
			&& ft_atoi(str[2]) >= 0 && ft_atoi(str[2]) < 256)
		{
			g_floor_rgb.r = ft_atoi(str[0]);
			g_floor_rgb.g = ft_atoi(str[1]);
			g_floor_rgb.b = ft_atoi(str[2]);
		}
		else
			ft_exit("Error\nInvalid floor RGB values!\n");
	}
	else
		ft_exit("Error\nInvalid floor RGB values!\n");
	g_c += 27;
}

void		ft_ceiling(char *buffer)
{
	char	**str;

	str = ft_split(buffer, ',');
	buffer = ft_strtrim(buffer + 1, "\t");
	check_comma(buffer);
	if (all_n(str[0]) && all_n(str[1]) && all_n(str[2]) && !str[3])
	{
		if (ft_atoi(str[0]) >= 0 && ft_atoi(str[0]) < 256
			&& ft_atoi(str[1]) >= 0 &&
			ft_atoi(str[1]) < 256 && ft_atoi(str[2]) >= 0
			&& ft_atoi(str[2]) < 256)
		{
			g_ceiling_rgb.r = ft_atoi(str[0]);
			g_ceiling_rgb.g = ft_atoi(str[1]);
			g_ceiling_rgb.b = ft_atoi(str[2]);
		}
		else
			ft_exit("Error\nInvalid ceiling RGB values!\n");
	}
	else
		ft_exit("Error\nInvalid ceiling RGB values!\n");
	g_c += 72;
}

void		check(char *buf)
{
	int		i;

	i = 0;
	while (buf[i] == ' ')
		i++;
	if (buf[i] == 'R' && buf[i + 1] == 'R')
		ft_exit("Error\nMultiple R!");
	if ((buf[i] == 'C' && buf[i + 1] == 'C')
		|| (buf[i] == 'F' && buf[i + 1] == 'F'))
		ft_exit("Error\nMultiple C or F!");
	else if (buf[i] == 'R' && (buf[++i] == ' ' || buf[++i] == '\t'))
		resolution(&buf[i]);
	else if (buf[i] == 'N' || buf[i] == 'S' || buf[i] == 'W' || buf[i] == 'E')
		store_paths(&buf[i]);
	else if (buf[i] == 'F' && (buf[++i] == ' ' || buf[++i] == '\t'))
		ft_floor(&buf[i]);
	else if (buf[i] == 'C' && (buf[++i] == ' ' || buf[++i] == '\t'))
		ft_ceiling(&buf[i]);
	else if (g_c > 150)
		ft_exit("Error\nSomething is being repeated or Invalid line!\n");
	else if ((ft_isalpha(buf[i])
	|| ((ft_isalpha(buf[i]) || ft_isdigit(buf[i])) && g_c != 150)))
		ft_exit("Error\nInvalid line!\n");
}

void		read_file(int argc, char **argv)
{
	int		fd;
	char	*buffer;
	int		n;

	g_c = 0;
	n = 1;
	fd = arg_test(argc, argv);
	buffer = NULL;
	while (n != 0)
	{
		n = get_next_line(fd, &buffer);
		check(buffer);
		ft_lstadd_back(&g_file, ft_lstnew(buffer));
		free(buffer);
	}
	if (is_notmap_init() == 1)
		ft_exit("Error\nInvalid file!\n");
	if (g_c == 150)
		check_map();
}
