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

static int	seek_string(const char **a, const char *b)
{
	const char	*str;
	int			len;

	str = *a;
	while (*b != '\0')
		if (*str++ != *b++)
			return (0);
	len = (int)(str - *a);
	*a = str;
	return (len);
}

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
		out->precision = ft_atoi(*s);
	}
	*s = data;
	return ;
}

void		get_modifier(t_format *out, const char **s)
{
	if (seek_string(s, "hh"))
		out->modifier = 0x00000000000000FF;
	else if (seek_string(s, "h"))
		out->modifier = 0x000000000000FFFF;
	else if (seek_string(s, "ll"))
		out->modifier = 0xFFFFFFFFFFFFFFFF;
	else if (seek_string(s, "l"))
		out->modifier = 0xFFFFFFFFFFFFFFFF;
	else if (seek_string(s, "j"))
		out->modifier = 0x00000000FFFFFFFF;
	else if (seek_string(s, "z"))
		out->modifier = 0xFFFFFFFFFFFFFFFF;
	else
		out->modifier = 0xFFFFFFFFFFFFFFFF;
	return ;
}

void		get_conversion(t_format *out, const char **s)
{
	if (seek_string(s, "s"))
		out->conversion = CONV_STR;
	else if (seek_string(s, "S"))
		out->conversion = CONV_WSTR;
	else if (seek_string(s, "p"))
		out->conversion = CONV_PTR;
	else if (seek_string(s, "d")
		|| seek_string(s, "D")
		|| seek_string(s, "i"))
		out->conversion = CONV_INT;
	else if (seek_string(s, "o")
		|| seek_string(s, "O"))
		out->conversion = CONV_OCT;
	else if (seek_string(s, "u")
		|| seek_string(s, "U"))
		out->conversion = CONV_UINT;
	else if (seek_string(s, "x"))
		out->conversion = CONV_HEXL;
	else if (seek_string(s, "X"))
		out->conversion = CONV_HEXU;
	else if (seek_string(s, "c")
		|| seek_string(s, "C"))
		out->conversion = CONV_CHAR;
	return ;
}
