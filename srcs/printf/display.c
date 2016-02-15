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
** TODO: Properly prefix decimal numbers
*/

static void		include_prefix(t_buffer *buf, t_format *in, int skip, char *pre)
{
	size_t	len;

	len = ft_strlen(pre);
	skip += len;
	if (in->prec == MISSING && (in->flags & ZPAD) && !(in->flags & NEGF))
	{
		pad_buffer(buf, in, skip, MISSING);
		write_to_buffer(buf, PREPEND, len, pre);
	}
	else
	{
		write_to_buffer(buf, PREPEND, len, pre);
		pad_buffer(buf, in, skip, MISSING);
	}
}

void		display_as_dec(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if (in->conv & CONV_UINT)
		out = ft_uitoa64(arg);
	else if (in->conv & CONV_OCT)
		out = ft_uitoa_base64(arg, 8);
	else
		out = ft_itoa64(arg);
	if (out == NULL)
		return ;
	len = ft_strlen(out);
	if (in->prec == MISSING || arg)
		write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, MISSING, len);
	if ((in->flags & ALT) && (in->conv & CONV_OCT))
		include_prefix(buf, in, len, "0");
	else if ((in->flags & SIGN) && *out != '-')
		include_prefix(buf, in, len, "+");
	else if ((in->flags & BLANK) && *out != '-')
		include_prefix(buf, in, len, " ");
	else
		pad_buffer(buf, in, len, MISSING);
	free(out);
}

void		display_as_hex(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_uitoa_base64(arg & in->modif, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	if (in->conv & CONV_HEXU)
		ft_strupcase(out);
	if (in->prec == MISSING || arg)
		write_to_buffer(buf, APPEND, len, out);
	if ((in->flags & ALT) && arg)
	{
		pad_buffer(buf, in, MISSING, len);
		if (in->conv & CONV_HEXU)
			include_prefix(buf, in, len, "X0");
		else
			include_prefix(buf, in, len, "x0");
	}
	else
		pad_buffer(buf, in, len, len);
}

void		display_as_ptr(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if (arg == 0)
		out = "(null)";
	else if ((out = ft_uitoa_base64(arg & in->modif, 16)) == NULL)
		return ;
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, len, out);
	pad_buffer(buf, in, len, len);
	free(out);
}

void		display_as_str(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if (in->conv & (CONV_CHAR | CONV_WCHAR))
	{
		out = (char*)&arg;
		if (in->conv & CONV_CHAR)
			write_to_buffer(buf, APPEND, sizeof(char), out);
		else if (in->conv & CONV_WCHAR)
			write_to_buffer(buf, APPEND, sizeof(wchar_t), out);
		pad_buffer(buf, in, 1, MISSING);
		return ;
	}
	out = arg == 0 ?"(null)" : (char*)arg;
	len = ft_strlen(out);
	if (in->prec != MISSING)
		len = ft_min(in->prec, len);
	if (in->conv & CONV_STR)
		write_to_buffer(buf, APPEND, sizeof(char) * len, out);
	else if (in->conv & CONV_WSTR)
		write_to_buffer(buf, APPEND, sizeof(wchar_t) * len, out);
	if (arg == 0)
		buf->written -= 2;
	pad_buffer(buf, in, len, MISSING);
}
