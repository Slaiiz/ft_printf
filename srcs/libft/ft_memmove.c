/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:02:33 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/25 16:33:24 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		direction;
	void	*tmp;

	tmp = dst;
	if (dst > src)
	{
		direction = -1;
		dst += len - 1;
		src += len - 1;
	}
	else
		direction = 1;
	while (len--)
	{
		*((unsigned char*)dst) = *((unsigned char*)src);
		dst += direction;
		src += direction;
	}
	return (tmp);
}
