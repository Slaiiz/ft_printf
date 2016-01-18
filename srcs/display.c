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
#include <stdio.h>

static void	insert_padding(t_buffer *buf, t_format *in, size_t spa, size_t zpa)
{
	int	mode;

	mode = PREPEND;
	if (in->flags & FLAG_NEGF)
		mode = APPEND;
	while (in->precision > zpa)
	{
		write_to_buffer(buf, APPEND, "0");
		in->precision--;
		spa++;
	}
	while (in->fieldwidth > spa)
	{
		if (in->flags & FLAG_ZPAD && !(in->flags & FLAG_ALT))
			write_to_buffer(buf, mode, "0");
		else
			write_to_buffer(buf, mode, " ");
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
	insert_padding(buf, in, len, len);
	write_to_buffer(buf, APPEND, out);
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
	insert_padding(buf, in, 0, len);
	if (in->flags & FLAG_ALT && arg != 0)
	{
		write_to_buffer(buf, APPEND, "0x");
		len += 2;
	}
	insert_padding(buf, in, len, 0);
	write_to_buffer(buf, APPEND, out);
	return ;
}

void		display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_itoa_base64(arg, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	insert_padding(buf, in, len, len);
	write_to_buffer(buf, APPEND, out);
	return ;
}

void		display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	int	len;

	if (in->conversion & CONV_CHAR)
	{
		write_to_buffer(buf, APPEND, (char*)arg);
		return ;
	}
	len = ft_strlen((char*)arg);
	insert_padding(buf, in, len, 0);
	write_to_buffer(buf, APPEND, (char*)arg);
	return ;
}
