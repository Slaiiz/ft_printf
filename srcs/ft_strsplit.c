/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:21:46 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/27 14:55:21 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	locatenext(char const **src, char c)
{
	char const	*tmp;
	char const	*adr;

	adr = *src;
	while (*adr == c)
		adr++;
	if (*adr == '\0')
	{
		*src = (char const*)NULL;
		return (0);
	}
	tmp = adr;
	while (*adr != c && *adr != '\0')
	{
		adr++;
	}
	*src = adr;
	return ((unsigned int)(adr - tmp));
}

char				**ft_strsplit(char const *s, char c)
{
	unsigned int	index;
	unsigned int	cells;
	unsigned int	size;
	char			**out;
	char const		*tmp;

	cells = 0;
	tmp = s;
	while (locatenext(&s, c) != 0)
		cells++;
	if ((out = malloc((cells + 1) * sizeof(char*))) == NULL)
		return (NULL);
	out[cells] = NULL;
	index = 0;
	s = tmp;
	while (cells--)
	{
		size = locatenext(&s, c);
		if ((out[index] = malloc(sizeof(char) * (size + 1))) == NULL)
			return (NULL);
		ft_memcpy(out[index], s - size, size);
		out[index++][size] = '\0';
	}
	return ((char**)out);
}
