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

void		pad_buffer(t_buffer *buf, t_format *in, size_t spa, size_t zpa)
{
	int	mode;

	mode = PREPEND;
	if (in->flags & FLAG_NEGF && ~(in->conversion & (CONV_HEXU | CONV_HEXL)))
		mode = APPEND;
	if (!(in->conversion & (CONV_STR | CONV_WSTR)))
	{
		while (in->precision > zpa)
		{
			write_to_buffer(buf, mode, 1, "0");
			in->precision--;
			spa++;
		}
	}
	while (in->fieldwidth > spa)
	{
		if (in->flags & FLAG_ZPAD && ~(in->flags & (FLAG_ALT | FLAG_NEGF)))
			write_to_buffer(buf, mode, 1, "0");
		else
			write_to_buffer(buf, mode, 1, " ");
		in->fieldwidth--;
	}
	return ;
}

void		display_as_dec(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		base;
	int		len;

	base = 10;
	if (in->conversion & CONV_OCT)
		base = 8;
	if (in->conversion & (CONV_UINT | CONV_OCT))
		if ((out = ft_uitoa_base64(arg & in->modifier, base)) == NULL)
			return ;
	if ((out = ft_itoa_base64(arg & in->modifier, base)) == NULL)
		return ;
	len = ft_strlen(out);
	if (in->flags & FLAG_SIGN && *out != '-' && len++)
		write_to_buffer(buf, APPEND, 1, "+");
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
	return ;
}

void		display_as_hex(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_uitoa_base64(arg & in->modifier, 16)) == NULL)
		return ;
	if (in->conversion & CONV_HEXU)
		ft_strupcase(out);
	len = ft_strlen(out);
	if (in->flags & FLAG_ALT && arg != 0)
	{
		write_to_buffer(buf, APPEND, len, out);
		pad_buffer(buf, in, len + 2, len);
		if (in->conversion & CONV_HEXU)
			write_to_buffer(buf, PREPEND, 2, "X0");
		else
			write_to_buffer(buf, PREPEND, 2, "x0");
		return ;
	}
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
	return ;
}

void		display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_uitoa_base64(arg, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, 2, "0x");
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len + 2, len);
	return ;
}

void		display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	int		size;
	int		len;

	len = 1;
	size = sizeof(char);
	if (in->conversion & CONV_CHAR)
		write_to_buffer(buf, APPEND, 1, (char*)&arg);
	else if (in->conversion & CONV_WCHAR)
		size = sizeof(wchar_t);
	else if (in->conversion & CONV_WSTR)
	{
		size = sizeof(wchar_t);
		len = ft_wstrlen((wchar_t*)arg);
	}
	else if (in->conversion & CONV_STR)
		len = ft_strlen((char*)arg);
	write_to_buffer(buf, APPEND, size * len, (char*)arg);
	pad_buffer(buf, in, len, len);
	return ;
}
