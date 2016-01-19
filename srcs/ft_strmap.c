/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:24:44 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/26 17:52:39 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	const char	*tmp;
	void		*buf;

	tmp = s;
	while (*s != '\0')
		s++;
	if ((buf = malloc((unsigned int)(s - tmp + 1))) == NULL)
		return (NULL);
	s = tmp;
	tmp = buf;
	while (*s != '\0')
		*((char*)buf++) = f(*s++);
	*((char*)buf) = '\0';
	return ((char*)tmp);
}
