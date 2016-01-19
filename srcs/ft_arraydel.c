/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 12:46:13 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/09 12:51:41 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arraydel(void **array)
{
	void	**tmp;

	tmp = *array;
	while (*array != NULL)
		free(*array++);
	free(tmp);
	return ;
}
