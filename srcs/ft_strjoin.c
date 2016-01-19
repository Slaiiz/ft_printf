/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 20:01:37 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/26 18:57:59 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	size;
	void			*buf;
	void			*tmp;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if ((buf = malloc(size)) == NULL)
		return (NULL);
	tmp = buf;
	while (size-- && *s1 != '\0')
		*((char*)buf++) = *s1++;
	while (size--)
		*((char*)buf++) = *s2++;
	*(char*)buf = '\0';
	return ((char*)tmp);
}
