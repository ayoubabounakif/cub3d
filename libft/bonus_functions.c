/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:33:02 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/13 11:50:29 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
	This function allocates (with malloc(3)) and returns a new
	element. The variable ’content’ is initialized
	with the value of the parameter ’content’. The
	variable ’next’ is initialized to NULL.
*/

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

/*
	DESCRIPTION
		Adding an item to the beginning of the list (pushing to the list)

	ALGORITHM
		1 - Create a new item and set its value
		2 - Put on the new item's next the previous head
		3 - Set the head of the list to be our new item

	This will effectively create a new head to the list with a new value,
	and keep the rest of the list linked to it.

	Since we use a function to do this operation,
	we want to be able to modify the head variable.
	To do this, we must pass a pointer to the pointer variable (a double pointer)
	so we will be able to modify the pointer itself.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

/*
	Counts the number of elements in a list.
*/

int		ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/*
	Returns the last element of the list.
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (current == NULL) // Return NULL if list is empty
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

/*
	This function Adds the element ’new’ at the end of the list.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

/*
	This function takes as parameter an element
	and frees the memory of the element4s content using the function 'del'
	given as a parameter and free the element.
	The memory of 'next' must not be freed
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{	
	if (lst)
		(*del)(lst->content);
	free(lst);
}

/*
	Deletes and frees the given element and every successor
	of that element, using the function 'del' and free(3).
	Finally, the pointer to the list must be set to NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		ft_lstdelone(tmp, (*del));
		*lst = (*lst)->next;
	}
	(*del)(*lst);
	*lst = NULL;
}

/*
	Iterates the list ’lst’ and applies the function
	’f’ to the content of each element.
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
