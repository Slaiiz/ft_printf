/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:52:53 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/03 13:50:13 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	const char	*tmp;
	void		*buf;

	if ((buf = malloc(ft_strlen(s) + 1)) == NULL)
		return (NULL);
	tmp = buf;
	while (*s != '\0')
	{
		*((char*)buf) = f((unsigned int)((void*)buf - (void*)tmp), *s++);
		buf++;
	}
	return ((char*)tmp);
}
