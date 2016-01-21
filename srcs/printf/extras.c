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

/*
** BONUS !
*/

static char	*get_output_color(const char **in)
{
	static char	*colors[10];
	static char	*output;
	int			index;

	if (output == NULL)
	{
		colors[0] = "black";
		colors[1] = "red";
		colors[2] = "green";
		colors[3] = "yellow";
		colors[4] = "blue";
		colors[5] = "magenta";
		colors[6] = "cyan";
		colors[7] = "white";
		colors[8] = "pouet";
		colors[9] = "eoc";
		output = ft_strdup("\033[3*m");
	}
	index = -1;
	while (++index < 8)
		if (ft_seekstr(in, colors[index]))
			break ;
	output[3] = 9;
	if (index < 8)
		output[3] = index;
	return (output);
}

static char	*get_font_modifier(const char **in)
{
	static char	*output;
	int			flags;

	if (output != NULL)
		free(output);
	output = ft_memalloc(sizeof(char) * 10);
	ft_strncat(output, "\033[", 2);
	flags = 0x00000000;
	while (ft_isalpha(**in))
	{
		if (ft_seekstr(in, "b") && !(flags & 0x1) && (flags |= 0x1))
			ft_strncat(output, "1;", 2);
		if (ft_seekstr(in, "i") && !(flags & 0x2) && (flags |= 0x2))
			ft_strncat(output, "3;", 2);
		if (ft_seekstr(in, "u") && !(flags & 0x4) && (flags |= 0x4))
			ft_strncat(output, "4;", 2);
		else
			(*in)++;
	}
	if (flags)
		ft_strncat(output, "m\0", 2);
	return (output);
}

char		*parse_extras(const char **format)
{
	static char	*output;
	char		*tmp;

	if (output != NULL)
		free(output);
	output = get_output_color(format);
	if (**format != ';')
	{
		tmp = output;
		output = NULL;
		return (tmp);
	}
	(*format)++;
	output = ft_strjoin(output, get_font_modifier(format));
	return (output);
}
