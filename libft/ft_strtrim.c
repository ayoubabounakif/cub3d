/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:05:07 by aabounak          #+#    #+#             */
/*   Updated: 2019/10/22 22:57:22 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*display(char const *s1, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * ((end + 1) - start) + 1)))
		return (0);
	while (start < (end + 1))
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	if (!s1)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	end = ft_strlen(s1);
	while (s1[start])
	{
		if (0 == (ft_strchr(set, s1[start])))
			break ;
		start++;
	}
	while (s1[end] != s1[start])
	{
		if (0 == (ft_strchr(set, s1[end])))
			break ;
		end--;
	}
	return (display(s1, start, end));
}
