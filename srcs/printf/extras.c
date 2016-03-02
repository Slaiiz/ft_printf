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
	if (index < 10)
		output[3] = index + '0';
	return (output);
}

static char	*get_font_modifier(const char **in)
{
	static char	*output;

	if (output != NULL)
		free(output);
	if ((output = ft_memalloc(sizeof(char) * 25)) == NULL)
		return ("");
	ft_strcat(output, "\033[22;23;24;25m");
	if (!ft_isalpha(**in))
		return (output);
	ft_strcat(output, "\033[");
	while (1)
	{
		if (ft_seekstr(in, "b"))
			ft_strcat(output, "1");
		else if (ft_seekstr(in, "i"))
			ft_strcat(output, "3");
		else if (ft_seekstr(in, "u"))
			ft_strcat(output, "4");
		else if (ft_seekstr(in, "x"))
			ft_strcat(output, "5");
		if (!ft_isalpha(**in))
			break ;
		ft_strcat(output, ";");
	}
	return (ft_strcat(output, "m"));
}

static int	get_file_descriptor(const char **in)
{
	const char	*tmp;
	int			out;

	tmp = *in;
	while (ft_isdigit(**in))
		(*in)++;
	out = ft_atoi(tmp);
	if (!ft_seekstr(in, "**"))
		return (1);
	return (out);
}

void		parse_extras(t_buffer *in, const char **format)
{
	char	*out;

	while (1)
	{
		if (ft_seekstr(format, "**fd:"))
		{
			flush_to_stdout(in);
			in->fd = get_file_descriptor(format);
		}
		else if (ft_seekstr(format, "{{"))
		{
			out = get_output_color(format);
			if (ft_seekstr(format, ";"))
			{
				out = ft_strjoin(out, get_font_modifier(format));
				if (ft_seekstr(format, "}}"))
					write_to_buffer(in, APPEND, ft_strlen(out), out);
				free(out);
			}
			else if (ft_seekstr(format, "}}"))
				write_to_buffer(in, APPEND, ft_strlen(out), out);
		}
		else
			break ;
	}
}
