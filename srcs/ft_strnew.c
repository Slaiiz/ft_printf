/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:45:48 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/26 17:59:21 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*ptr;
	char	*tmp;

	if ((ptr = malloc(size)) == NULL)
		return ((char*)NULL);
	tmp = ptr;
	while (size--)
		*ptr++ = '\0';
	return (tmp);
}
