/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/02 13:37:38 by marvin            #+#    #+#             */
/*   Updated: 2016/00/02 13:37:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define FLAG_ALT	0x01
# define FLAG_ZPAD	0x02
# define FLAG_BLANK	0x04
# define FLAG_SIGN	0x08
# define FLAG_NEGF	0x10

# define APPEND		1
# define PREPEND	2

typedef struct	s_buffer
{
	char		*data;
	size_t		size;
}				t_buffer;

typedef struct	s_format
{
	size_t		fieldwidth;
	size_t		precision;
	char		modifier;
	char		convert;
	char		flags;
}				t_format;

int				ft_printf(const char *format, ...);
void			get_flags(t_format *out, const char **s);
void			get_precision(t_format *out, const char **s);

#endif
