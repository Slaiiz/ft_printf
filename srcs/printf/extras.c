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
	int			index;
	static char	*output;
	static char	*colors[10];

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

	if (output == NULL)
		output = malloc(sizeof(char) * 25);
	ft_bzero(output, 25);
	ft_strcat(output, "\033[22;23;24;25m");
	if (!ft_isalpha(**in))
		return (output);
	ft_strcat(output + sizeof(char) * 14, "\033[");
	while (1)
	{
		if (ft_seekstr(in, "b"))
			ft_strlcat(output, "1", 24);
		else if (ft_seekstr(in, "i"))
			ft_strlcat(output, "3", 24);
		else if (ft_seekstr(in, "u"))
			ft_strlcat(output, "4", 24);
		else if (ft_seekstr(in, "x"))
			ft_strlcat(output, "5", 24);
		if (!ft_isalpha(**in))
			break ;
		ft_strlcat(output, ";", 24);
	}
	return (ft_strcat(output, "m"));
}

static void	process_command(t_buffer *in, const char **format)
{
	if (ft_seekstr(format, "clear"))
		write_to_buffer(in, APPEND, 4, "\x1b[2J");
	else if (ft_seekstr(format, "left"))
		write_to_buffer(in, APPEND, 4, "\x1b[1D");
	else if (ft_seekstr(format, "up"))
		write_to_buffer(in, APPEND, 4, "\x1b[1A");
	else if (ft_seekstr(format, "right"))
		write_to_buffer(in, APPEND, 4, "\x1b[1C");
	else if (ft_seekstr(format, "down"))
		write_to_buffer(in, APPEND, 4, "\x1b[1B");
	else if (ft_seekstr(format, "fd="))
	{
		in->fd = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	ft_seekstr(format, "^");
}

void		parse_extras(t_buffer *in, const char **format)
{
	char	*out;

	while (1)
	{
		if (ft_seekstr(format, "#!"))
			process_command(in, format);
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
