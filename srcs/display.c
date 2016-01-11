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

static void	insert_padding(t_buffer *buf, t_format *in, size_t ssk, size_t zsk)
{
	int	mode;

	mode = PREPEND;
	if (in->flags & FLAG_NEGF)
		mode = APPEND;
	while (in->precision-- > zsk)
	{
		write_to_buffer(buf, APPEND, "0", 1);
		ssk++;
	}
	while (in->fieldwidth-- > ssk)
	{
		if (in->flags & FLAG_ZPAD && !(in->flags & FLAG_ALT))
			write_to_buffer(buf, mode, "0", 1);
		else
			write_to_buffer(buf, mode, " ", 1);
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
	if ((out = ft_itoa_base64(arg, base)) == NULL)
		return ;
	len = ft_strlen(out);
	insert_padding(buf, in, ft_strlen(buf->data), len);
	return ;
}

void		display_as_hex(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_itoa_base64(arg, 16)) == NULL)
		return ;
	if (in->conversion & CONV_HEXU)
		ft_strupcase(out);
	len = ft_strlen(out);
	if (in->flags & FLAG_ALT && arg != 0)
		write_to_buffer(buf, APPEND, "0x", 2);
	insert_padding(buf, in, ft_strlen(buf->data) + len, len);
	write_to_buffer(buf, APPEND, out, len);
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
	write_to_buffer(buf, APPEND, out, len);
	return ;
}

void		display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	if (in->conversion & CONV_CHAR)
	{
		write_to_buffer(buf, APPEND, (char*)arg, 1);
		return ;
	}
	write_to_buffer(buf, APPEND, (char*)arg, ft_strlen((char*)arg));
	return ;
}
