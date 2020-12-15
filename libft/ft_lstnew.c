/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:52:12 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 12:56:40 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = NULL;
	if (!(head = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	(head)->content = ft_strdup(content);
	(head)->next = NULL;
	return (head);
}
