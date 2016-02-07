/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:28:38 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/02 12:15:08 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa_base64(unsigned long n, int base)
{
	char			digits[64];
	unsigned int	index;
	unsigned int	count;
	char			*out;

	base = ft_min(ft_max(base, 2), 16);
	count = 0;
	while (1)
	{
		digits[count++] = "0123456789abcdef"[n % base];
		if ((n = n / base) == 0)
			break ;
	}
	if ((out = ft_memalloc(count + 1)) == NULL)
		return (NULL);
	index = 0;
	while (count--)
		*(out + index++) = digits[count];
	return (out);
}
