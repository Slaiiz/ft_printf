/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/09 17:12:03 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/09 17:12:03 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pad_buffer(t_buffer *buf, t_format *in, int fpad, int ppad)
{
	char	*style;
	int		mode;

	mode = PREPEND;
	if (in->flags & FLAG_NEGF)
		mode = APPEND;
	style = in->conversion & STRING ?" ": "0";
	while (ppad >= 0 && in->precision > ppad)
	{
		write_to_buffer(buf, PREPEND, 1, style);
		if (!(in->conversion & STRING))
			in->fieldwidth--;
		in->precision--;
	}
	style = !(in->flags & FLAG_ZPAD) || (in->flags & FLAG_NEGF)
		|| (in->precision != MISSING && (in->conversion & NUMERIC)) ?" " :"0";
	while (fpad >= 0 && in->fieldwidth > fpad)
	{
		write_to_buffer(buf, mode, 1, style);
		in->fieldwidth--;
	}
}

/*
** TODO: Strip sign from output to allow padding.
*/

void	display_as_dec(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if (in->conversion & CONV_UINT)
		out = ft_uitoa64(arg);
	else if (in->conversion & CONV_OCT)
		out = ft_uitoa_base64(arg, 8);
	else
		out = ft_itoa64(arg);
	if (out == NULL)
		return ;
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
	if ((in->flags & FLAG_SIGN) && *out != '-')
		write_to_buffer(buf, PREPEND, 1, "+");
	else if ((in->flags & FLAG_BLANK) && *out != '-')
		write_to_buffer(buf, PREPEND, 1, " ");
	if ((in->flags & FLAG_ALT) && in->conversion & CONV_OCT && len++)
		write_to_buffer(buf, PREPEND, 1, "0");
	free(out);
	return ;
}

void	display_as_hex(t_buffer *buf, t_format *in, size_t arg)
{
	char	*prefix;
	char	*out;
	int		len;

	if ((out = ft_uitoa_base64(arg & in->modifier, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	if (in->conversion & CONV_HEXU)
		ft_strupcase(out);
	write_to_buffer(buf, APPEND, len, out);
	if ((in->flags & FLAG_ALT) && arg > 0)
	{
		pad_buffer(buf, in, MISSING, len);
		prefix = in->conversion & CONV_HEXU ?"X0" :"x0";
		if (!(in->flags & FLAG_ZPAD) || (in->flags & FLAG_NEGF)
			|| (in->precision != MISSING && (in->conversion & NUMERIC)))
		{
			write_to_buffer(buf, PREPEND, 2, prefix);
			pad_buffer(buf, in, len + 2, MISSING);
			return ;
		}
		pad_buffer(buf, in, len + 2, MISSING);
		write_to_buffer(buf, PREPEND, 2, prefix);
		return ;
	}
	pad_buffer(buf, in, len, len);
}

void	display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((arg ) == 0)
		out = "(null)";
	else if ((out = ft_uitoa_base64(arg & in->modifier, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
}

void	display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if (in->conversion & (CONV_CHAR | CONV_WCHAR))
	{
		out = (char*)&arg;
		len = 1;
		if (in->conversion & CONV_CHAR)
			write_to_buffer(buf, APPEND, sizeof(char), out);
		else
			write_to_buffer(buf, APPEND, sizeof(wchar_t), out);
	}
	else
	{
		out = arg == 0 ?"(null)" : (char*)arg;
		len = ft_strlen(out);
		if (in->precision != MISSING)
		{
			in->precision = ft_min(in->precision, len);
			len = in->precision;
		}
		if (in->conversion & CONV_WSTR)
			write_to_buffer(buf, APPEND, sizeof(wchar_t) * len, out);
		else if (in->conversion & CONV_STR)
			write_to_buffer(buf, APPEND, sizeof(char) * len, out);
	}
	pad_buffer(buf, in, ft_strlen(out), len);
}
