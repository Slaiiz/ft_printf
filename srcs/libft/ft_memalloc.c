/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:17:01 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/26 17:50:53 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ptr;
	void	*tmp;

	if ((ptr = malloc(size)) == NULL)
		return (NULL);
	tmp = ptr;
	while (size--)
		*((unsigned char*)ptr++) = '\0';
	return (tmp);
}
