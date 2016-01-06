/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:59:16 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/04 11:02:21 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(int n, int base)
{
	size_t	len;

	base = ft_min(ft_max(base, 2), 16);
	len = 0;
	while (1)
	{
		len++;
		if ((n = n / base) == 0)
			break ;
	}
	return (len);
}
