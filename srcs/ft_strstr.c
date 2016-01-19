/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 14:48:30 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/03 16:17:25 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *s1, char const *s2)
{
	const char	*pos;
	const char	*bak;
	char		c;

	bak = s2;
	pos = s1;
	if (*s2 == '\0')
		return ((char*)s1);
	while ((c = *s1++) != '\0')
	{
		if (c == *s2)
		{
			if (s2++ == bak)
				pos = s1 - 1;
			if (*s2 == '\0')
				return ((char*)pos);
		}
		else
		{
			s1 = pos + 1;
			s2 = bak;
			pos = s1;
		}
	}
	return (NULL);
}
