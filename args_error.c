/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:51:26 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/22 14:57:02 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int			g_save;

int			check_name(char *str)
{
	if (ft_strncmp(ft_split(str, '.')[1], "cub", 20))
		return (0);
	if (ft_split(str, '.')[2] != 0)
		return (0);
	return (1);
}

void		fc_error(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (!ft_isdigit(buffer[i]))
		{
			if (buffer[i] == ',')
				i++;
			else
				ft_exit("Error\nFloor Error\n");
		}
		i++;
	}
}

int			arg_test(int argc, char **argv)
{
	int		fd;

	g_save = 0;
	if (argc < 2 || argc > 3)
		ft_exit("Error\nInvalid number of args!\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || !check_name(argv[1]))
		ft_exit("Error\nFile name is invalid!\n");
	if (argv[2])
	{
		if (!(ft_strncmp(argv[2], "--save", 15)))
			g_save = 1;
		else
			ft_exit("Error\nWrong second argument!\n");
	}
	return (fd);
}
