/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/21 15:32:34 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/21 15:32:34 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static void	read_number(const char **in, va_list argp)
{
	const char	*tmp;

	ft_printf("%s -> ", *in);
	tmp = *in;
	while (ft_isdigit(*tmp))
		tmp++;
	if (!(ptrdiff_t)(tmp - *in))
		return ;
	*va_arg(argp, intmax_t*) = ft_atoi(*in);
	ft_printf("%d\n", ft_atoi(*in));
	*in = tmp;
	return ;
}

static void	read_identifier(const char **in, va_list argp)
{
	const char	*tmp;
	ptrdiff_t	len;

	ft_printf("%s -> ", *in);
	tmp = *in;
	while (ft_isalpha(*tmp))
		tmp++;
	if (!(len = (ptrdiff_t)(tmp - *in)))
		return ;
	*va_arg(argp, char**) = ft_strsub(*in, 0, len);
	ft_printf("%s\n", ft_strsub(*in, 0, len));
	*in = tmp;
	return ;
}

int			ft_expect(const char **s, const char *format, ...)
{
	va_list	argp;
	char	c;

	va_start(argp, format);
	while ((c = *format) != '\0')
	{
		if (c == '$' && (c = *++format))
		{
			if (c == 'n')
				read_number(s, argp);
			else if (c == 'i')
				read_identifier(s, argp);
			format++;
			continue ;
		}
		if (**s != c)
			return (0);
		format++;
		(*s)++;
	}
	return (1);
}
