/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:38:29 by vchesnea          #+#    #+#             */
/*   Updated: 2016/01/19 16:38:29 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_output_color(const char **in)
{
	static char	*colors[8 + 1];
	static char	*output;
	int			index;

	if (colors[8] == NULL)
	{
		colors[0] = "black";
		colors[1] = "red";
		colors[2] = "green";
		colors[3] = "yellow";
		colors[4] = "blue";
		colors[5] = "magenta";
		colors[6] = "cyan";
		colors[7] = "white";
		colors[8] = (void*)1;
		output = ft_strdup("\033[30m");
	}
	index = -1;
	while (++index < 8)
		if (ft_seekstr(in, colors[index]))
			output[3] = index + '0';
	return (output);
}
