/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:32:10 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/29 15:46:19 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*curr;

	while (*alst != NULL)
	{
		del((*alst)->content, (*alst)->content_size);
		curr = (*alst)->next;
		free(*alst);
		*alst = curr;
	}
	*alst = NULL;
	return ;
}
