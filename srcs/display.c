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

static void	insert_padding(t_buffer *buf, t_format *in, size_t sskip, size_t zskip)
{
	int	mode;

	printf("sskip = %li\n", sskip);
	mode = PREPEND;
	if (in->flags & FLAG_NEGF)
		mode = APPEND;
	while (in->precision-- > zskip)
	{
		write_to_buffer(buf, APPEND, "0", 1);
		sskip++;
	}
	while (in->fieldwidth-- > sskip)
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
	if (in->flags & FLAG_ALT)
		write_to_buffer(buf, APPEND, "0x", 2);
	insert_padding(buf, in, 2 * (in->flags & FLAG_ALT) + len, len);
	write_to_buffer(buf, APPEND, out, len);
	return ;
}

/*
void		display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	return ;
}

void		display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	return ;
}
*/
