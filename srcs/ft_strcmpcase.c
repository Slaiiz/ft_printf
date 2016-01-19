/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:32:43 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/02 18:26:06 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmpcase(const char *s1, const char *s2)
{
	while (*s1 != '\0')
	{
		if ((*s1 & -33) == (*s2 & -33))
		{
			s1++;
			s2++;
			continue ;
		}
		break ;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
