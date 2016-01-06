/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/06 13:52:17 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/06 13:52:17 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flush_to_stdout(t_buffer *in)
{
	int		index;

	index = (int)((char*)ft_memchr(in->data, '\0', in->size) - in->data);
	if (index < 0 || in->data == NULL)
		return ;
	write(1, in->data, index);
	while (index--)
		*(in->data + index) = '\0';
	write(1, "\n", 1);
	return ;
}

void		format_argument(t_buffer *in, const char **s, size_t arg)
{
	int	flags;

	flags = parse_flags(s);
	return ;
}

void		write_to_buffer(t_buffer *in, int mode, char c)
{
	int		index;

	index = (int)((char*)ft_memchr((void*)in->data, '\0', in->size) - in->data);
	if (index < 0 || in->data == NULL)
	{
		if (in->data != NULL)
			free(in->data);
		in->size += 32;
		if ((in->data = ft_memalloc(sizeof(char) * in->size)) == NULL)
			return ;
	}
	if (mode & PREPEND)
	{
		ft_memmove(in->data + 1, in->data, index);
		*(in->data + 0) = c;
	}
	else if (mode & APPEND)
		*(in->data + index) = c;
	return ;
}

int			ft_printf(const char *format, ...)
{
	int				written;
	static t_buffer	buffer;
	va_list			argp;
	char			ch;

	written = 0;
	va_start(argp, format);
	while ((ch = *format++))
	{
		if (ch == '%')
		{
			flush_to_stdout(&buffer);
			format_argument(&buffer, &format, va_arg(size_t, argp));
		}
		else
			write_to_buffer(&buffer, APPEND, ch);
	}
	return (written);
}