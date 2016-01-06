/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:46:54 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/27 17:21:22 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*out;
	t_list	*prev;
	t_list	*curr;

	if (lst == NULL || (out = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	*out = *f(lst);
	prev = out;
	while ((lst = lst->next) != NULL)
	{
		if ((curr = malloc(sizeof(t_list))) == NULL)
			return (NULL);
		*curr = *f(lst);
		prev->next = curr;
		prev = curr;
	}
	return (out);
}
