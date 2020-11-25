/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:24:52 by aabounak          #+#    #+#             */
/*   Updated: 2020/11/20 22:58:16 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	getfirstchar(char *buffer)
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

char	*spacer(char *buf, int biglen)
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
	while (buf[j])
	{
		str[i] = buf[j];
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

void	check_map()
{
	t_list	*temp;
	t_list	*temp2;
	char	*content;

	g_sizeofmap = 0;
	g_biglen = 0;
	temp = g_file;
	content = NULL;
	while (temp)
	{
		content = temp->content;
		if (getfirstchar(content))
		{
			g_sizeofmap++;
			if (ft_strlen(content) > (size_t)g_biglen)
				g_biglen = ft_strlen(content);
		}
		temp = temp->next;
	}
	g_biglen += 2;
	g_sizeofmap += 2;
	g_mapread = (char **)malloc(sizeof(char *) * (g_sizeofmap + 1));
	g_mapread[0] = space_filler(g_biglen);
	temp2 = g_file;
	content = NULL;

	int     i = 1;
	while (temp2)
	{
		content = temp2->content;
		if (getfirstchar(content))
		{
			g_mapread[i] = spacer(content, g_biglen);
			i++;
		}
		temp2 = temp2->next;
	}
	g_mapread[i] = space_filler(g_biglen);
	i++;
	g_mapread[i] = NULL;
}