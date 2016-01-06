/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:49:26 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/03 16:08:30 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		number;
	char	sign;

	while (ft_isblank(*str))
		str++;
	if (*str == '+')
	{
		sign = +1;
		str++;
	}
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else
		sign = +1;
	number = 0;
	while (ft_isdigit(*str))
		number = number * 10 + *str++ - '0';
	return (number * sign);
}
