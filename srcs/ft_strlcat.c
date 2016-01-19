/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:43:35 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/03 18:26:42 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*tmp;
	long		off;

	tmp = src;
	off = (long)dst;
	while (size-- > 0 && *dst != '\0')
		dst++;
	off = (long)dst - off;
	while (*src != '\0')
	{
		if ((int)size-- > 0)
			*dst++ = *src;
		src++;
	}
	if (size == 0)
		*dst = '\0';
	return ((size_t)(src - tmp + off));
}
