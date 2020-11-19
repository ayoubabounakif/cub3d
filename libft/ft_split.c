/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:39:17 by aabounak          #+#    #+#             */
/*   Updated: 2019/10/22 19:17:57 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		number_of_words(char *str, char c)
{
	int		nbr;
	int		i;
	int		indicator;

	nbr = 0;
	i = 0;
	indicator = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i] != c)
		{
			if (indicator != 1)
			{
				nbr++;
				indicator = 1;
			}
		}
		else
			indicator = 0;
		i++;
	}
	return (nbr);
}

static int		word_size(char *str, char c)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		length++;
		i++;
	}
	return (length);
}

static void		fill_string(char *str, char *cas, char c)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		cas[i] = str[i];
		i++;
	}
	cas[i] = '\0';
}

static char		**norminette_ez(char *str, char **tab, char c, int indicator)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (str[++i] != '\0')
		if (str[i] != c)
		{
			if (indicator != 1)
			{
				if (!(tab[++j] = malloc(1 + word_size((str + i), c))))
				{
					while (j--)
						free(tab[j]);
					free(tab);
					return (0);
				}
				fill_string(str + i, tab[j], c);
				indicator = 1;
			}
		}
		else
			indicator = 0;
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		indicator;

	str = (char*)s;
	indicator = 0;
	if (!str)
		return (0);
	if (!(tab = malloc((number_of_words(str, c) + 1) * 8)))
		return (0);
	tab = norminette_ez(str, tab, c, indicator);
	tab[number_of_words(str, c)] = 0;
	return (tab);
}
