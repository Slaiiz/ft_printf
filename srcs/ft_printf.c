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
	if (in->len < 0 || in->data == NULL)
		return ;
	write(1, in->data, in->len);
	in->len = 0;
	return ;
}

void		format_argument(t_buffer *in, const char **s, size_t arg)
{
	t_format	format;

	ft_bzero(&format, sizeof(t_format));
	get_flags(&format, s);
	get_precision(&format, s);
	get_modifier(&format, s);
	get_conversion(&format, s);
	if (format.conversion & (CONV_OCT | CONV_INT | CONV_UINT))
		display_as_dec(in, &format, arg);
	else if (format.conversion & (CONV_HEXL | CONV_HEXU))
		display_as_hex(in, &format, arg);
	else if (format.conversion & CONV_PTR)
		display_as_ptr(in, &format, arg);
	else if (format.conversion & (CONV_CHAR | CONV_STR | CONV_WSTR))
		display_as_str(in, &format, arg);
	return ;
}

void		write_to_buffer(t_buffer *in, int mode, const char *s)
{
	char	*new;

	if (*s == '\0')
		return ;
	if (in->len == in->size)
	{
		if ((new = malloc(sizeof(char) * (in->size + 32))) == NULL)
			return ;
		if (in->data != NULL)
		{
			ft_memcpy(new, in->data, in->size);
			free(in->data);
		}
		in->data = new;
		in->size += 32;
	}
	if (mode & PREPEND)
	{
		ft_memmove(in->data + 1, in->data, in->len);
		*(in->data + 0) = *s;
	}
	else if (mode & APPEND)
		*(in->data + in->len) = *s;
	in->len++;
	write_to_buffer(in, mode, ++s);
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
		if (*format == '%' && ++format)
			format_argument(&buffer, &format, va_arg(argp, size_t));
		else
			write_to_buffer(&buffer, APPEND, format++);
	}
	flush_to_stdout(&buffer);
	return (written);
}
