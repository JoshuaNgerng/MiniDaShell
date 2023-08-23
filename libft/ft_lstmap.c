/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:31:47 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/17 19:37:40 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: The address of a pointer to a node
f: The address of the fuinction used to iterate on the list
del: The address of the function used to delete the content of the
if needed.
Return: The new list. NULL if the allocation fails
Iterates the list 'lst' and applis the function 'f' on the content of 
each node. Creates a new list resulting of the successive applications 
of the function 'f'. The 'del' function is used to delete the content of a node
if needed
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*elem;

	if (!f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		elem = ft_lstnew(f(lst -> content));
		if (elem == NULL)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, elem);
		lst = lst -> next;
	}
	return (list);
}
