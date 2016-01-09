/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:31:50 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/03 11:10:25 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	off;
	char const		*tmp;
	char			*buf;

	if ((start & SIGN_BIT_INT) | (len & SIGN_BIT_INT))
		return (NULL);
	while (start-- && *s != '\0')
		s++;
	tmp = s;
	while (len-- && *s != '\0')
		s++;
	off = ((unsigned int)(s - tmp));
	s = tmp;
	if ((buf = malloc(off + 1)) == NULL)
		return (NULL);
	tmp = buf;
	while (off--)
		*buf++ = *s++;
	*buf = '\0';
	return ((char*)tmp);
}
