/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:25:32 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/03 17:34:40 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*start;
	char	*end;
	char	tmp;

	end = str + ft_strlen(str) - 1;
	start = str;
	while (start <= end)
	{
		tmp = *start;
		*start++ = *end;
		*end-- = tmp;
	}
	return (str);
}
