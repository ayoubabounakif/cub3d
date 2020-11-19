/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 01:29:50 by aabounak          #+#    #+#             */
/*   Updated: 2020/11/19 04:46:11 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_c;		// If c == 8 only then init map

// HELPER FUNCTIONS

int		all_n(char *s)
{
	int		i;

	i = -1;
	if (!s)
		return (0);
	s = ft_strtrim(s + 1, "\t");
	while (s[++i])
		if (s[i] < 48 || s[i] > 57)
			return (0);
	return (1);
}

void	ft_exit(char *msg)
{
	ft_putstr_fd(msg, 1);
	exit(-1);
}

int		ft_strlendoubleptr(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	check_comma(char *buffer)
{
	int		comma;

	comma = 0;
	while (*buffer)
	{
		if (*buffer == ',')
		{
			comma++;
			if (comma > 2)
				ft_exit("Error\nYou can't use more than 2 commas!\n");
		}
		buffer++;
	}
}

// THIS FUNCTION CHECKS FOR NO AND WE
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

// THIS FUNCTION CHECK FOR SO EA AND SPRIT
int		check_so_ea_s(char *buffer)
{
	if (buffer[0] == 'E')
	{
		if (buffer[1] == 'A')
			return (0);
		else
			ft_exit("Eroor\nInvalid name in EA texture!\n");
	}
	else if (buffer[0] == 'S')
	{
		if (buffer[1] == 'O')
			return (1);
		else if (buffer[1] == ' ' || buffer[1] == '\t')
			return (2);
		else
			ft_exit("Eroor\nInvalid name in SO or SP texture!\n");
	}
	return (3);
}

// THIS FUNCTION STORE THE PATHS OF NO WE SO EA AND SPRITE
void		store_paths(char *buffer)
{
	if (check_no_we(buffer) == 0)
		g_data.paths.no = ft_strtrim(buffer + 3, "\t");
	else if (check_no_we(buffer) == 1)
		g_data.paths.we = ft_strtrim(buffer + 3, "\t");
	if (check_so_ea_s(buffer) == 0)
		g_data.paths.so = ft_strtrim(buffer + 3, "\t");
	else if (check_so_ea_s(buffer) == 1)
		g_data.paths.ea = ft_strtrim(buffer + 3, "\t");
	else if (check_so_ea_s(buffer) == 2)
		g_data.paths.s = ft_strtrim(buffer + 2, "\t");
	g_c++;
}

// RESOLUTION FUNCTION
int		resolution(char *buffer)
{
	char	**arr;

	arr = ft_split(buffer, ' ');
	if (ft_strlendoubleptr(arr) != 2)
	{
		ft_exit("Error\nWrong number of arguments in Resolution!\n");
		return (-1);
	}
	g_data.win_width = ft_atoi(arr[0]);
	g_data.win_height = ft_atoi(arr[1]);
	g_c++;
	return (0);
}

// FLOOR FUNCTION
void		ft_floor(char *buffer, t_color *floor_rgb)
{
	char	**arr;

	buffer = ft_strtrim(buffer + 1, "\t");
	check_comma(buffer);
	arr = ft_split(buffer, ',');
	if (all_n(arr[0]) && all_n(arr[1]) && all_n(arr[2]) && !arr[3])
	{
		if (ft_atoi(arr[0]) >= 0 && ft_atoi(arr[0]) < 256 && ft_atoi(arr[1]) >= 0 &&
			ft_atoi(arr[1]) < 256 && ft_atoi(arr[2]) >= 0 && ft_atoi(arr[2]) < 256)
		{
			floor_rgb->r = ft_atoi(arr[0]);
			floor_rgb->g = ft_atoi(arr[1]);
			floor_rgb->b = ft_atoi(arr[2]);
		}
		else
			ft_exit("Error\nInvalid floor RGB values!\n");
	}
	else
		ft_exit("Error\nInvalid floor RGB values!\n");
	g_c++;
}

// CEILING FUNCTION
void		ft_ceiling(char *buffer, t_color *ceiling_rgb)
{
	char	**arr;

	buffer = ft_strtrim(buffer + 1, "\t");
	check_comma(buffer);
	arr = ft_split(buffer, ',');
	if (all_n(arr[0]) && all_n(arr[1]) && all_n(arr[2]) && !arr[3])
	{
		if (ft_atoi(arr[0]) >= 0 && ft_atoi(arr[0]) < 256 && ft_atoi(arr[1]) >= 0 &&
			ft_atoi(arr[1]) < 256 && ft_atoi(arr[2]) >= 0 && ft_atoi(arr[2]) < 256)
		{
			ceiling_rgb->r = ft_atoi(arr[0]);
			ceiling_rgb->g = ft_atoi(arr[1]);
			ceiling_rgb->b = ft_atoi(arr[2]);
		}
		else
			ft_exit("Error\nInvalid ceiling RGB values!\n");
	}
	else
		ft_exit("Error\nInvalid ceiling RGB values!\n");
	g_c++;
}

void		check(char *buffer, t_color *floor_rgb, t_color *ceiling_rgb)
{
	int		i;

	i = 0;
	if (buffer[i] == 'R' && (buffer[++i] == ' ' || buffer[++i] == '\t'))
		resolution(&buffer[i]);
	else if (buffer[i] == 'N' || buffer[i] == 'S' || buffer[i] == 'W' || buffer[i] == 'E')
		store_paths(&buffer[i]);
	else if (buffer[i] == 'F' && (buffer[++i] == ' ' || buffer[++i] == '\t'))
		ft_floor(&buffer[i], floor_rgb);
	else if (buffer[i] == 'C' && (buffer[++i] == ' ' || buffer[++i] == '\t'))
		ft_ceiling(&buffer[i], ceiling_rgb);
}

// MAIN
void		read_file()
{
	int		fd;
	char	*buffer;
	int		n;
	t_color	floor_rgb;
	t_color	ceiling_rgb;

	g_c = 0;
	n = 1;
	buffer = NULL;
	fd = open("map.cub", O_RDONLY);
	while (n != 0)
	{
		n = get_next_line(fd, &buffer);
		check(buffer, &floor_rgb, &ceiling_rgb);
		ft_lstadd_back(&g_file, ft_lstnew(buffer));
	}
	check_map();

	// printf("Height -> %d\n", g_data.win_height);
	// printf("Width -> %d\n", g_data.win_width);
	// printf("NO -> %s\n", g_data.paths.no);
	// printf("SO -> %s\n", g_data.paths.so);
	// printf("WE -> %s\n", g_data.paths.we);
	// printf("EA -> %s\n", g_data.paths.ea);
	// printf("Sprite -> %s\n", g_data.paths.s);
	// printf("Floor -> %d %d %d\n", floor_rgb.r, floor_rgb.g, floor_rgb.b);
	// printf("Ceiling -> %d %d %d\n", ceiling_rgb.r, ceiling_rgb.g, ceiling_rgb.b);

	free(buffer);
}