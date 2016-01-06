/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 12:28:02 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/02 15:22:04 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	nextrep(char **str, char c)
{
	while (**str != '\0' && **str != c)
		(*str)++;
	return (**str);
}

static void	nextwrite(char **dst, char **src)
{
	while (**src != '\0')
		*(*dst)++ = *(*src)++;
	return ;
}

static void	writeback(char *str, char *bak, char **rep, char c)
{
	char	*off;

	off = bak;
	while (nextrep(&bak, c) != '\0')
	{
		*bak++ = '\0';
		nextwrite(&str, &off);
		nextwrite(&str, rep++);
		off = bak;
	}
	nextwrite(&str, &off);
	*str = '\0';
	return ;
}

char		*ft_chrrep(char *str, char c, char **rep)
{
	unsigned int	index;
	unsigned int	size;
	char			*bak;

	bak = str;
	index = 0;
	size = 0;
	while (nextrep(&str, c) != '\0')
	{
		size += ft_strlen(rep[index++]);
		str++;
	}
	size += ft_strlen(bak) - index;
	if ((str = malloc(size + 1)) == NULL)
		return (NULL);
	writeback(str, bak, rep, c);
	return (str);
}
