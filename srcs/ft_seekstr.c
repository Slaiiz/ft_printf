/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seekstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/19 16:51:00 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/19 16:51:00 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_seekstr(const char **a, const char *b)
{
	const char	*str;
	int			len;

	str = *a;
	while (*b != '\0')
		if (*str++ != *b++)
			return (0);
	len = (int)(str - *a);
	*a = str;
	return (len);
}
