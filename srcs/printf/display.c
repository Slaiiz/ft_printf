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

static void		prepad_prefix(t_buffer *buf, t_format *in, int skip, char *pre)
{
	size_t	len;

	pad_buffer(buf, in, -1, skip);
	len = ft_strlen(pre);
	skip += len;
	if (in->prec == -1 && (in->flags & ZPAD) && !(in->flags & NEGF))
	{
		pad_buffer(buf, in, skip, -1);
		write_to_buffer(buf, PREPEND, len, pre);
		return ;
	}
	write_to_buffer(buf, PREPEND, len, pre);
	pad_buffer(buf, in, skip, -1);
}

void			display_as_dec(t_buffer *buf, t_format *in, size_t arg)
{
	int		len;
	int		sign;
	char	*out;

	if (in->conv & CUINT)
		out = ft_uitoa64(arg & in->modif);
	else if (in->conv & COCT)
		out = ft_uitoa_base64(arg & in->modif, 8);
	else
		out = ft_itoa64(arg);
	sign = ft_seekstr((const char**)&out, "-");
	len = in->prec == -1 || arg ? ft_strlen(out) : 0;
	write_to_buffer(buf, APPEND, len, out);
	if ((in->conv & COCT) && (in->flags & ALT))
		prepad_prefix(buf, in, len, "0");
	else if ((in->conv & CINT) && (in->flags & SIGN) && !sign)
		prepad_prefix(buf, in, len, "+");
	else if ((in->conv & CINT) && (in->flags & BLANK) && !sign)
		prepad_prefix(buf, in, len, " ");
	else
		prepad_prefix(buf, in, len, sign ? "-" : "");
	if (sign)
		out--;
	free(out);
}

void			display_as_hex(t_buffer *buf, t_format *in, size_t arg)
{
	int		len;
	char	*out;

	out = ft_uitoa_base64(arg & in->modif, 16);
	len = in->prec == -1 || arg ? ft_strlen(out) : 0;
	if (in->conv & CHEXU)
		ft_strupcase(out);
	if (in->prec == -1 || arg)
		write_to_buffer(buf, APPEND, len, out);
	if ((in->flags & ALT) && arg)
		prepad_prefix(buf, in, len, (in->conv & CHEXU) ? "0X" : "0x");
	else
		pad_buffer(buf, in, len, len);
	free(out);
}

void			display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	int		len;
	char	*out;

	out = ft_uitoa_base64(arg, 16);
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, len, out);
	prepad_prefix(buf, in, len, "0x");
	free(out);
}

void			display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	int		len;
	char	*out;

	if (in->conv & (CCHAR | CWCHAR))
	{
		out = (char*)&arg;
		write_to_buffer(buf, APPEND, sizeof(char), out);
		pad_buffer(buf, in, 1, -1);
		return ;
	}
	out = arg == 0 ? "(null)" : (char*)arg;
	len = ft_strlen(out);
	if (in->prec != -1)
		len = ft_min(in->prec, len);
	write_to_buffer(buf, APPEND, sizeof(char) * len, out);
	pad_buffer(buf, in, len, -1);
}
