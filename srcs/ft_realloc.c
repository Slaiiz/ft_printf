/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 10:54:09 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/07 11:04:39 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*buf;

	if ((buf = malloc(size)) == NULL)
		return (NULL);
	ft_memcpy(buf, ptr, size);
	free(ptr);
	return (buf);
}
