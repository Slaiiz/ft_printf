/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/06 14:55:05 by vchesnea          #+#    #+#             */
/*   Updated: 2016/02/19 12:06:56 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_flags(t_format *out, const char **s)
{
	char	ch;
	char	flags;

	flags = 0x00;
	while ((ch = **s) != '\0')
	{
		if (ch == '#')
			flags |= ALT;
		else if (ch == '0')
			flags |= ZPAD;
		else if (ch == '+')
			flags |= SIGN;
		else if (ch == '-')
			flags |= NEGF;
		else if (ch == ' ')
			flags |= BLANK;
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
	out->field = ft_atoi(*s);
	if (*data == '.')
	{
		*s = ++data;
		while (ft_isdigit(*data))
			data++;
		if (data != *s)
			out->prec = ft_atoi(*s);
	}
	else
		out->prec = -1;
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
		out->modif = 0x00000000000000ff;
	else if (ft_seekstr(s, "h"))
		out->modif = 0x000000000000ffff;
	else if (ft_seekstr(s, "ll"))
		out->modif = 0xffffffffffffffff;
	else if (ft_seekstr(s, "l"))
		out->modif = 0xffffffffffffffff;
	else if (ft_seekstr(s, "j"))
		out->modif = 0xffffffffffffffff;
	else if (ft_seekstr(s, "z"))
		out->modif = 0xffffffffffffffff;
	else
		out->modif = 0x00000000ffffffff;
}

void		get_conversion(t_format *out, const char **s)
{
	if (ft_seekstr(s, "s"))
		out->conv = CSTR | STRING;
	else if (ft_seekstr(s, "S"))
		out->conv = CWSTR | STRING;
	else if (ft_seekstr(s, "p"))
		out->conv = CPTR | POINTER;
	else if (ft_seekstr(s, "d")
		|| ft_seekstr(s, "i")
		|| (ft_seekstr(s, "D") && (out->modif = 0xffffffffffffffff)))
		out->conv = CINT | NUMERIC;
	else if (ft_seekstr(s, "o")
		|| (ft_seekstr(s, "O") && (out->modif = 0xffffffffffffffff)))
		out->conv = COCT | NUMERIC;
	else if (ft_seekstr(s, "u")
		|| (ft_seekstr(s, "U") && (out->modif = 0xffffffffffffffff)))
		out->conv = CUINT | NUMERIC;
	else if (ft_seekstr(s, "x"))
		out->conv = CHEXL | NUMERIC;
	else if (ft_seekstr(s, "X"))
		out->conv = CHEXU | NUMERIC;
	else if (ft_seekstr(s, "c"))
		out->conv = CCHAR | STRING;
	else if (ft_seekstr(s, "C"))
		out->conv = CWCHAR | STRING;
}

/*
** Invert the sign of the number, taking advantage of two's complement
** in the subsequent subtraction. The number regains its original sign
** with extra bits at the end of the process.
*/

size_t		sign_extend(t_format *in, size_t arg)
{
	size_t	sign;

	sign = (in->modif + 1) >> 1;
	return (((arg & in->modif) ^ sign) - sign);
}
