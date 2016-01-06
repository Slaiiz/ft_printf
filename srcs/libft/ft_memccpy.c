/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:01:56 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/26 11:22:19 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	tmp;

	while (n--)
	{
		tmp = *((unsigned char*)src++);
		*((unsigned char*)dst++) = tmp;
		if (tmp == (unsigned char)c)
			return (dst);
	}
	return (void*)NULL;
}
