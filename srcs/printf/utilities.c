/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/06 14:55:05 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/06 14:55:05 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_flags(t_format *out, const char **s)
{
	char	flags;
	char	ch;

	flags = 0x00;
	while ((ch = **s) != '\0')
	{
		if (ch == '#')
			flags |= FLAG_ALT;
		else if (ch == '0')
			flags |= FLAG_ZPAD;
		else if (ch == '+')
			flags |= FLAG_SIGN;
		else if (ch == '-')
			flags |= FLAG_NEGF;
		else if (ch == ' ')
			flags |= FLAG_BLANK;
		else
			break ;
		(*s)++;
	}
	out->flags = flags;
}

void		get_precision(t_format *out, const char **s)
{
	const char	*data;

	data = *s;
	while (ft_isdigit(*data))
		data++;
	out->fieldwidth = ft_atoi(*s);
	if (*data == '.')
	{
		*s = ++data;
		while (ft_isdigit(*data))
			data++;
		if (data != *s)
			out->precision = ft_atoi(*s);
		else
			out->precision = 0;
	}
	else
		out->precision = MISSING;
	*s = data;
}

/*
** HACK:
** Bit shift operations would overflow. Though that was the whole point of the
** trick it makes the compiler spit out errors. This is not a portable solution.
*/

void		get_modifier(t_format *out, const char **s)
{
	if (ft_seekstr(s, "hh"))
		out->modifier = 0x00000000000000ff;
	else if (ft_seekstr(s, "h"))
		out->modifier = 0x000000000000ffff;
	else if (ft_seekstr(s, "ll"))
		out->modifier = 0xffffffffffffffff;
	else if (ft_seekstr(s, "l"))
		out->modifier = 0xffffffffffffffff;
	else if (ft_seekstr(s, "j"))
		out->modifier = 0xffffffffffffffff;
	else if (ft_seekstr(s, "z"))
		out->modifier = 0xffffffffffffffff;
	else
		out->modifier = 0x00000000ffffffff;
}

void		get_conversion(t_format *out, const char **s)
{
	if (ft_seekstr(s, "s"))
		out->conversion = CONV_STR | STRING;
	else if (ft_seekstr(s, "S"))
		out->conversion = CONV_WSTR | STRING;
	else if (ft_seekstr(s, "p"))
		out->conversion = CONV_PTR | POINTER;
	else if (ft_seekstr(s, "d")
		|| ft_seekstr(s, "D")
		|| ft_seekstr(s, "i"))
		out->conversion = CONV_INT | NUMERIC;
	else if (ft_seekstr(s, "o")
		|| ft_seekstr(s, "O"))
		out->conversion = CONV_OCT | NUMERIC;
	else if (ft_seekstr(s, "u")
		|| ft_seekstr(s, "U"))
		out->conversion = CONV_UINT | NUMERIC;
	else if (ft_seekstr(s, "x"))
		out->conversion = CONV_HEXL | NUMERIC;
	else if (ft_seekstr(s, "X"))
		out->conversion = CONV_HEXU | NUMERIC;
	else if (ft_seekstr(s, "c"))
		out->conversion = CONV_CHAR | STRING;
	else if (ft_seekstr(s, "C"))
		out->conversion = CONV_WCHAR | STRING;
}

/*
** Invert the sign of the number, taking advantage of two's complement
** in the subtraction. The number regains its original sign with extra
** bits at the end of the process.
*/

size_t		sign_extend(t_format *in, size_t arg)
{
	size_t	sign;

	sign = (in->modifier + 1) >> 1;
	return (((arg & in->modifier) ^ sign) - sign);
}
