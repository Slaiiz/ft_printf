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

static void	insert_padding(t_buffer *buf, t_format *in, size_t spa, size_t zpa)
{
	int	mode;

	mode = PREPEND;
	if (in->flags & FLAG_NEGF)
		mode = APPEND;
	while (in->precision > zpa)
	{
		write_to_buffer(buf, mode, 1, "0");
		in->precision--;
		spa++;
	}
	while (in->fieldwidth > spa)
	{
		if (in->flags & FLAG_ZPAD && !(in->flags & (FLAG_ALT | FLAG_NEGF)))
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
	if ((out = ft_itoa_base64(arg & in->modifier, base)) == NULL)
		return ;
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, len, out);
	insert_padding(buf, in, len, len);
	return ;
}

void		display_as_hex(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_itoa_base64(arg & in->modifier, 16)) == NULL)
		return ;
	if (in->conversion & CONV_HEXU)
		ft_strupcase(out);
	len = ft_strlen(out);
	if (in->flags & FLAG_ALT && arg != 0)
	{
		write_to_buffer(buf, APPEND, 2, "0x");
		insert_padding(buf, in, len + 2, len + 2);
		write_to_buffer(buf, APPEND, len, out);
		return ;
	}
	write_to_buffer(buf, APPEND, len, out);
	insert_padding(buf, in, len, len);
	return ;
}

void		display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_itoa_base64(arg, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, 2, "0x");
	write_to_buffer(buf, APPEND, len, out);
	insert_padding(buf, in, len + 2, len);
	return ;
}

void		display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	int		size;
	int		len;

	size = sizeof(char);
	if (in->conversion & (CONV_WCHAR | CONV_WSTR))
		size = sizeof(wchar_t);
	if (in->conversion & (CONV_CHAR | CONV_WCHAR))
	{
		write_to_buffer(buf, APPEND, size * 1, (char*)&arg);
		insert_padding(buf, in, size * 1, 0);
		return ;
	}
	len = ft_strlen((char*)arg);
	write_to_buffer(buf, APPEND, size * len, (char*)arg);
	insert_padding(buf, in, size * len, 0);
	return ;
}
