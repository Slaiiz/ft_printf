/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/06 13:52:17 by vchesnea          #+#    #+#             */
/*   Updated: 2016/02/19 12:07:19 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	format_argument(t_buffer *in, const char **s, va_list argp)
{
	t_format	format;

	ft_bzero(&format, sizeof(t_format));
	get_flags(&format, s);
	get_precision(&format, s);
	get_modifier(&format, s);
	get_conversion(&format, s);
	if (format.conv & STRING)
		display_as_str(in, &format, va_arg(argp, size_t));
	else if (format.conv & (CHEXL | CHEXU))
		display_as_hex(in, &format, sign_extend(&format, va_arg(argp, size_t)));
	else if (format.conv & (CUINT | COCT))
		display_as_dec(in, &format, va_arg(argp, size_t));
	else if (format.conv & NUMERIC)
		display_as_dec(in, &format, sign_extend(&format, va_arg(argp, size_t)));
	else if (format.conv & POINTER)
		display_as_ptr(in, &format, va_arg(argp, size_t));
	else
	{
		write_to_buffer(in, APPEND, 1, (*s)++);
		pad_buffer(in, &format, 1, 1);
	}
}

int			flush_to_stdout(t_buffer *in)
{
	int	len;

	len = in->len;
	if (len < 1 || in->data == NULL)
		return (0);
	write(in->fd, in->data, len);
	in->written += len;
	in->len = 0;
	return (len);
}

void		pad_buffer(t_buffer *buf, t_format *in, int fpad, int ppad)
{
	int		mode;
	char	*style;

	mode = PREPEND;
	if (in->flags & NEGF)
		mode = APPEND;
	style = in->conv & STRING ? " " : "0";
	while (ppad >= 0 && in->prec > ppad)
	{
		write_to_buffer(buf, PREPEND, 1, style);
		if (!(in->conv & STRING))
			in->field--;
		in->prec--;
	}
	style = !(in->flags & ZPAD) || (in->flags & NEGF)
		|| (in->prec != -1 && (in->conv & NUMERIC)) ? " " : "0";
	while (fpad >= 0 && in->field > fpad)
	{
		write_to_buffer(buf, mode, 1, style);
		in->field--;
	}
}

void		write_to_buffer(t_buffer *in, int mode, int len, const char *s)
{
	char	*new;

	if (in->size < (in->len + len))
	{
		if ((new = malloc(sizeof(char) * (in->size + len + 32))) == NULL)
			return ;
		if (in->data != NULL)
		{
			ft_memcpy(new, in->data, in->len);
			free(in->data);
		}
		in->size += len + 32;
		in->data = new;
	}
	if (mode & PREPEND)
	{
		ft_memmove(in->data + len, in->data, in->len);
		ft_strncpy(in->data, s, len);
	}
	else if (mode & APPEND)
		ft_strncpy(in->data + in->len, s, len);
	in->len += len;
}

int			ft_printf(const char *format, ...)
{
	va_list		argp;
	t_buffer	buffer;

	ft_bzero(&buffer, sizeof(t_buffer));
	va_start(argp, format);
	buffer.fd = 1;
	while (*format != '\0')
	{
		parse_extras(&buffer, &format);
		if (!ft_seekstr(&format, "%"))
		{
			if (*format)
				write_to_buffer(&buffer, APPEND, 1, format++);
		}
		else
		{
			flush_to_stdout(&buffer);
			format_argument(&buffer, &format, argp);
		}
	}
	flush_to_stdout(&buffer);
	if (buffer.size)
		free(buffer.data);
	return (buffer.written);
}
