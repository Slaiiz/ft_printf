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

void		pad_buffer(t_buffer *buf, t_format *in, int fpad, int ppad)
{
	int		mode;

	mode = PREPEND;
	if (in->flags & FLAG_NEGF)
		mode = APPEND;
	while (ppad >= 0 && in->precision > ppad)
	{
		write_to_buffer(buf, PREPEND, 1, "0");
		in->fieldwidth--;
		in->precision--;
	}
	while (fpad >= 0 && in->fieldwidth > fpad)
	{
		if ((in->flags & FLAG_ZPAD))
		{
			if ((in->conversion & (CONV_OCT | CONV_UINT | CONV_INT
				| CONV_HEXU | CONV_HEXL) && in->precision != MISSING)
				|| in->flags & FLAG_NEGF)
				write_to_buffer(buf, mode, 1, " ");
			else
				write_to_buffer(buf, mode, 1, "0");
		}
		else
			write_to_buffer(buf, mode, 1, " ");
		in->fieldwidth--;
	}
}

void		display_as_dec(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		base;
	int		len;

	if (in->conversion & (CONV_UINT | CONV_OCT))
	{
		base = 10;
		if (in->conversion & CONV_OCT)
			base = 8;
		if ((out = ft_uitoa_base64(arg & in->modifier, base)) == NULL)
			return ;
	}
	else if ((out = ft_itoa_base64(arg & in->modifier, 10)) == NULL)
		return ;
	len = ft_strlen(out);
	if (in->flags & FLAG_SIGN && *out != '-' && len++)
		write_to_buffer(buf, APPEND, 1, "+");
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
	free(out);
	return ;
}

void		display_as_hex(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_uitoa_base64(arg & in->modifier, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	if (in->conversion & CONV_HEXU)
		ft_strupcase(out);
	if ((in->flags & FLAG_ALT) && (arg & in->modifier))
	{
		write_to_buffer(buf, APPEND, len, out);
		if (in->flags & FLAG_ZPAD && !(in->flags & FLAG_NEGF))
		{
			pad_buffer(buf, in, len + 2, MISSING);
			write_to_buffer(buf, PREPEND, 2, "x0");
			pad_buffer(buf, in, MISSING, len);
		}
		else
		{
			write_to_buffer(buf, PREPEND, 2, "x0");
			pad_buffer(buf, in, len + 2, len);
		}
		return ;
	}
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
}

void		display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_uitoa_base64(arg & in->modifier, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
}

void		display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	int		len;

	if (in->conversion & (CONV_CHAR | CONV_WCHAR))
	{
		len = 1;
		if (in->conversion & CONV_CHAR)
			write_to_buffer(buf, APPEND, sizeof(char), (char*)arg);
		else
			write_to_buffer(buf, APPEND, sizeof(wchar_t), (char*)arg);
	}
	else
	{
		len = ft_strlen((char*)arg);
		if (in->conversion & CONV_STR)
			write_to_buffer(buf, APPEND, len, (char*)arg);
	}
	pad_buffer(buf, in, len, len);
}
