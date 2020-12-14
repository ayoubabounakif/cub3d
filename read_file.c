/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 01:29:50 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/14 18:00:08 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_c;

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

// THIS FUNCTION CHECKS IF THE EVERYTHING'S IS VALID (HARD CODE D zp)
int			tex_validity(char *buffer, int k)
{
	int		i = 0;
	char	*buf = buffer;
	char	*tmp = ft_strtrim(buf + k, "\t");
	while (tmp[i] != '.')
	{
		if (tmp[i] == ' ' || tmp[i] == '\t')
			ft_exit("Error\nSpaces spotted!\n");
		i++;
	}
	ft_strlcpy(tmp, tmp, 9);
	tmp = ft_strtrim(buf + k, "\t");
	tmp = ft_strchr(tmp, '.');
	if (ft_strncmp(tmp, ".xpm", 4) != 0)
		ft_exit("Error\nExtension != .xpm\n");
	tmp = ft_strchr(tmp, 'm');
	i = 1;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == ' ')
			i++;
		else
			ft_exit("Error\nInvalid extension!\n");
	}
	// free(buffer);
	return (0);
}

// THIS FUNCTION STORE THE PATHS OF NO WE SO EA AND SPRITE
void		store_paths(char *buffer)
{
	if (check_no_we(buffer) == 0 && tex_validity(buffer, 3) == 0)
		g_data.paths.no = ft_strtrim(buffer + 3, "\t");
	else if (check_so_ea_s(buffer) == 0 && tex_validity(buffer, 3) == 0)
		g_data.paths.so = ft_strtrim(buffer + 3, "\t");
	else if (check_no_we(buffer) == 1 && tex_validity(buffer, 3) == 0)
		g_data.paths.we = ft_strtrim(buffer + 3, "\t");
	else if (check_so_ea_s(buffer) == 1 && tex_validity(buffer, 3) == 0)
		g_data.paths.ea = ft_strtrim(buffer + 3, "\t");
	else if (check_so_ea_s(buffer) == 2 && tex_validity(buffer, 2) == 0)
		g_data.paths.sp = ft_strtrim(buffer + 2, "\t");
	g_c += 10;
}

// Free that str buffer

// RESOLUTION FUNCTIONs
void		resolution(char *buffer)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split(buffer, ' ');
	while (str[0][i] || str[1][i])
	{
		if (!ft_isdigit(str[0][i]) || !ft_isdigit(str[1][i]))
			ft_exit("Error\nLetters or negative value!\n");
		i++;
	}
	if (ft_strlendoubleptr(str) != 2)
		ft_exit("Error\nWrong number of arguments in Resolution!\n");
	else
	{
		g_data.win_width = (ft_atoi(str[0]) < 2560) ? ft_atoi(str[0]) : 2560;
		g_data.win_height = (ft_atoi(str[1]) < 1440) ? ft_atoi(str[1]) : 1440;
		g_c++;
	}
}

// FLOOR FUNCTION
void		ft_floor(char *buffer)
{
	char	**str;

	str = ft_split(buffer, ',');
	buffer = ft_strtrim(buffer + 1, "\t");
	check_comma(buffer);
	if (all_n(str[0]) && all_n(str[1]) && all_n(str[2]) && !str[3])
	{
		if (ft_atoi(str[0]) >= 0 && ft_atoi(str[0]) < 256 && ft_atoi(str[1]) >= 0 &&
			ft_atoi(str[1]) < 256 && ft_atoi(str[2]) >= 0 && ft_atoi(str[2]) < 256)
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

// CEILING FUNCTION
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
	if (buf[i] == ' ')
		i++;
	if (buf[i] == 'R' && buf[i + 1] == 'R')
		ft_exit("Error\nMultiple R!");
	else if (buf[i] == 'R' && (buf[++i] == ' ' || buf[++i] == '\t'))
		resolution(&buf[i]);
	else if (buf[i] == 'N' || buf[i] == 'S' || buf[i] == 'W' || buf[i] == 'E')
		store_paths(&buf[i]);
	else if (buf[i] == 'F' && (buf[++i] == ' ' || buf[++i] == '\t'))
		ft_floor(&buf[i]);
	else if (buf[i] == 'C' && (buf[++i] == ' ' || buf[++i] == '\t'))
		ft_ceiling(&buf[i]);
	else if (g_c > 150)
		ft_exit("Error\nSomething is being repeated more than once!");
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
	if (g_c == 150)
		check_map();
}
