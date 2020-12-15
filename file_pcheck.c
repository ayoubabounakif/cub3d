/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_pcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:10:13 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 19:22:32 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

extern int	g_c;
static int	g_i;
static char	*g_buf;
static char	*g_tmp;

// Spaghetti but works (￣▽￣) ( ͡° ͜ʖ ͡°)
int		tex_validity(char *buffer, int k)
{
	g_i = 0;
	g_buf = buffer;
	g_tmp = ft_strtrim(g_buf + k, "\t");
	while (g_tmp[g_i] != '.')
	{
		if (g_tmp[g_i] == ' ' || g_tmp[g_i] == '\t')
			ft_exit("Error\nSpaces or wrong path names!\n");
		g_i++;
	}
	ft_strlcpy(g_tmp, g_tmp, 9);
	g_tmp = ft_strtrim(g_buf + k, "\t");
	g_tmp = ft_strchr(g_tmp, '.');
	if (ft_strncmp(g_tmp, ".xpm", 4) != 0)
		ft_exit("Error\nExtension != .xpm\n");
	g_tmp = ft_strchr(g_tmp, 'm');
	g_i = 1;
	while (g_tmp[g_i] != '\0')
	{
		if (g_tmp[g_i] == ' ')
			g_i++;
		else
			ft_exit("Error\nInvalid extension!\n");
	}
	return (0);
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
