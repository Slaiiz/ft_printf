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
	while (++index < 10)
		if (ft_seekstr(in, colors[index]))
			break ;
	output[3] = 9 + '0';
	if (index < 8)
		output[3] = index + '0';
	return (output);
}

static char	*get_font_modifier(const char **in)
{
	static char	*output;

	if (output != NULL)
		free(output);
	if ((output = malloc(sizeof(char) * 15)) == NULL)
		return ("");
	ft_strncat(output, "\033[", 2);
	if (!ft_isalpha(**in))
		return (ft_strncat(output, "21;23;24;25m", 12));
	while (1)
	{
		if (ft_seekstr(in, "b"))
			ft_strncat(output, "1", 1);
		else if (ft_seekstr(in, "i"))
			ft_strncat(output, "3", 1);
		else if (ft_seekstr(in, "u"))
			ft_strncat(output, "4", 1);
		else if (ft_seekstr(in, "x"))
			ft_strncat(output, "5", 1);
		if (!ft_isalpha(*(++*in)))
			break ;
		ft_strncat(output, ";", 1);
	}
	return (ft_strncat(output, "m", 1));
}

char		*parse_extras(const char **format)
{
	static char	*output;
	char		*tmp;

	if (output != NULL)
		free(output);
	output = get_output_color(format);
	if (ft_seekstr(format, ";"))
	{
		output = ft_strjoin(output, get_font_modifier(format));
		return (output);
	}
	tmp = output;
	output = NULL;
	return (tmp);
}
