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

/*
** TODO: Properly prefix negative numbers
*/

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
	int		sign;
	char	*out;
	int		len;

	if (in->conv & CUINT)
		out = ft_uitoa64(arg);
	else if (in->conv & COCT)
		out = ft_uitoa_base64(arg, 8);
	else
		out = ft_itoa64(arg);
	sign = ft_seekstr((const char**)&out, "-");
	len = in->prec != 1 && !arg ? 0 : ft_strlen(out);
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
	char	*out;
	int		len;

	out = ft_uitoa_base64(arg & in->modif, 16);
	len = in->prec != 1 && !arg ? 0 : ft_strlen(out);
	if (in->conv & CHEXU)
		ft_strupcase(out);
	if (in->prec == -1 || arg)
		write_to_buffer(buf, APPEND, len, out);
	if ((in->flags & ALT) && arg)
		prepad_prefix(buf, in, len, (in->conv & CHEXU) ? "X0" : "x0");
	else
		pad_buffer(buf, in, len, len);
	free(out);
}

void			display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	out = arg == 0 ? "(null)" : ft_uitoa_base64(arg & in->modif, 16);
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
	free(out);
}

void			display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if (in->conv & (CCHAR | CWCHAR))
	{
		out = (char*)&arg;
		if (in->conv & CCHAR)
			write_to_buffer(buf, APPEND, sizeof(char), out);
		else if (in->conv & CWCHAR)
			write_to_buffer(buf, APPEND, sizeof(wchar_t), out);
		pad_buffer(buf, in, 1, -1);
		return ;
	}
	out = arg == 0 ? "(null)" : (char*)arg;
	len = ft_strlen(out);
	if (in->prec != -1)
		len = ft_min(in->prec, len);
	if (in->conv & CSTR)
		write_to_buffer(buf, APPEND, sizeof(char) * len, out);
	else if (in->conv & CWSTR)
		write_to_buffer(buf, APPEND, sizeof(wchar_t) * len, out);
	if (arg == 0)
		buf->written -= 2;
	pad_buffer(buf, in, len, -1);
}
