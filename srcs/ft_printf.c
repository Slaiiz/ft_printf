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
#include <stdio.h>

void		flush_to_stdout(t_buffer *in)
{
	int	index;

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
	t_format	format;

	ft_bzero(&format, sizeof(t_format));
	get_flags(&format, s);
	get_precision(&format, s);
	get_modifier(&format, s, &arg);
	get_conversion(&format, s);
	if (format->conversion & (CONV_OCT | CONV_INT | CONV_UINT))
		display_as_decimal(in, &format, arg);
	else if (format->conversion & (CONV_HEXL | CONV_HEXU))
		display_as_hexadecimal(in, &format, arg);
	else if (format->conversion & CONV_PTR)
		display_as_pointer(in, &format, arg);
	else if (format->conversion & (CONV_CHAR | CONV_STR | CONV_WSTR))
		display_as_string(in, &format, arg);
	return ;
}

void		write_to_buffer(t_buffer *in, int mode, char *s)
{
	int	index;

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
		*(in->data + 0) = *s++;
	}
	else if (mode & APPEND)
		*(in->data + index) = *s++;
	if (*s)
		write_to_buffer(in, mode, s);
	return ;
}

int			ft_printf(const char *format, ...)
{
	int				written;
	static t_buffer	buffer;
	va_list			argp;

	written = 0;
	va_start(argp, format);
	while (*format != '\0')
	{
		if (*format == '%')
			format_argument(&buffer, &format, va_arg(argp, size_t));
		else
			write_to_buffer(&buffer, APPEND, format);
		format++;
	}
	flush_to_stdout(&buffer);
	return (written);
}
