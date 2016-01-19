/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 19:19:09 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/25 16:34:36 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*tmp;

	tmp = dst;
	while (n--)
	{
		*dst++ = *src;
		if (*src != '\0')
			src++;
	}
	return (tmp);
}
