/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 18:31:12 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/26 17:53:52 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	const char	*tmp;
	int			len;

	tmp = s1;
	while (n-- && *s1 != '\0')
		s1++;
	len = (int)(s1 - tmp);
	if ((s1 = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	*((char*)(s1 + len)) = '\0';
	while (len-- > 0)
		*((char*)(s1 + len)) = *((const char*)(tmp + len));
	return ((char*)s1);
}
