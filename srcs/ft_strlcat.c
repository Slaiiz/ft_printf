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
	char	*tmp;

	tmp = dst;
	while (*dst)
	{
		if (size > 0)
			size--;
		dst++;
	}
	while (size > 1 && *src)
	{
		*dst++ = *src++;
		size--;
	}
	if (size)
		*dst = '\0';
	while (*src++)
		dst++;
	return (dst - tmp);
}
