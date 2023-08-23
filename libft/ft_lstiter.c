/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:18:27 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/17 18:45:11 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: the address of a pointer to a node
f: the address of the function used to iterate on the list
Iterates the list 'lst' and applies the function 'f' on the content 
of each node
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*list;

	list = lst;
	while (list != NULL)
	{
		f(list -> content);
		list = list -> next;
	}
}
