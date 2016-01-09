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
	char	*str
	int		len;

	str = *a;
	while (*b != '\0')
		if (*a++ != *b++)
			return (0);
	len = (int)(a - str);
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
		*s++;
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
	if (*data++ != '.')
		return ;
	*s = data;
	while (ft_isdigit(*data))
		data++;
	out->precision = ft_atoi(*s);
	*s = data;
	return ;
}

void		get_modifier(t_format *out, const char **s, size_t *arg)
{
	char	*data;
	int		len;

	data = *s;
	if ((len = seek_string(s, "hh")) > 0)
		*arg &= (1 << sizeof(char)) - 1;
	else if ((len = seek_string(s, "h")) > 0)
		*arg &= (1 << sizeof(short)) - 1;
	else if ((len = seek_string(s, "ll")) > 0)
		*arg &= (1 << sizeof(long long)) - 1;
	else if ((len = seek_string(s, "l")) > 0)
		*arg &= (1 << sizeof(long)) - 1;
	else if ((len = seek_string(s, "j")) > 0)
		*arg &= (1 << sizeof(intmax_t)) - 1;
	else if ((len = seek_string(s, "z")) > 0)
		*arg &= (1 << sizeof(size_t)) - 1;
	out->modifier = ft_strndup(data, len);
	return ;
}

void		get_conversion(t_format *out, const char **s, size_t *arg)
{

}
