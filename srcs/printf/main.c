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

static int	flush_to_stdout(t_buffer *in)
{
	int		len;

	len = in->len;
	if (len < 1 || in->data == NULL)
		return (0);
	write(in->fd, in->data, len);
	in->written += len;
	in->len = 0;
	return (len);
}

static void	format_argument(t_buffer *in, const char **s, size_t arg)
{
	t_format	format;

	ft_bzero(&format, sizeof(t_format));
	get_flags(&format, s);
	get_precision(&format, s);
	get_modifier(&format, s);
	get_conversion(&format, s);
	if (format.conversion & STRING)
		display_as_str(in, &format, arg);
	else if (format.conversion & (CONV_HEXL | CONV_HEXU))
		display_as_hex(in, &format, sign_extend(&format, arg));
	else if (format.conversion & NUMERIC)
		display_as_dec(in, &format, sign_extend(&format, arg));
	else if (format.conversion & POINTER)
		display_as_ptr(in, &format, arg);
	else if (**s == '%')
	{
		write_to_buffer(in, APPEND, 1, *s++);
		return (pad_buffer(in, &format, 1, 1));
	}
}

void		write_to_buffer(t_buffer *in, int mode, int len, const char *s)
{
	char	*new;

	while (len-- && *s)
	{
		if (in->len == in->size)
		{
			if ((new = malloc(sizeof(char) * (in->size + 32))) == NULL)
				return ;
			if (in->data != NULL)
			{
				ft_memcpy(new, in->data, in->len);
				free(in->data);
			}
			in->data = new;
			in->size += 32;
		}
		if (mode & PREPEND)
		{
			ft_memmove(in->data + 1, in->data, in->len++);
			*(in->data + 0) = *s++;
		}
		else if (mode & APPEND)
			*(in->data + in->len++) = *s++;
	}
}

int			ft_printf(const char *format, ...)
{
	char			*output;
	t_buffer		buffer;
	va_list			argp;

	ft_bzero(&buffer, sizeof(t_buffer));
	va_start(argp, format);
	while (*format != '\0')
	{
		if (*format == '{' && ++format)
		{
			output = parse_extras(&format);
			if (*format == '}' && ++format)
				write_to_buffer(&buffer, APPEND, ft_strlen(output), output);
		}
		else if (*format == '%' && ++format)
		{
			flush_to_stdout(&buffer);
			format_argument(&buffer, &format, va_arg(argp, size_t));
		}
		else
			write_to_buffer(&buffer, APPEND, 1, format++);
	}
	flush_to_stdout(&buffer);
	return (buffer.written);
}
