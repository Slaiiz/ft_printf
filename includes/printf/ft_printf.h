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
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define FLAG_ALT	0x01
# define FLAG_ZPAD	0x02
# define FLAG_BLANK	0x04
# define FLAG_SIGN	0x08
# define FLAG_NEGF	0x10

# define CONV_INT	0x0001
# define CONV_STR	0x0002
# define CONV_WSTR	0x0004
# define CONV_PTR	0x0008
# define CONV_OCT	0x0010
# define CONV_UINT	0x0020
# define CONV_HEXL	0x0040
# define CONV_HEXU	0x0080
# define CONV_CHAR	0x0100
# define CONV_WCHAR	0x0200

# define APPEND		1
# define PREPEND	2

# define PRECISION	1
# define FIELDWIDTH	2

typedef struct	s_buffer
{
	char		*data;
	size_t		size;
	size_t		len;
}				t_buffer;

typedef struct	s_format
{
	size_t		fieldwidth;
	size_t		precision;
	size_t		modifier;
	short		conversion;
	char		flags;
	intmax_t	fd;
}				t_format;

int				ft_printf(const char *format, ...);
void			write_to_buffer(t_buffer *in, int mode, int len, const char *s);
void			pad_buffer(t_buffer *buf, t_format *in, size_t spa, size_t zpa);
void			get_flags(t_format *out, const char **s);
void			get_precision(t_format *out, const char **s);
void			get_modifier(t_format *out, const char **s);
void			get_conversion(t_format *out, const char **s);
void			display_as_dec(t_buffer *buf, t_format *in, size_t arg);
void			display_as_hex(t_buffer *buf, t_format *in, size_t arg);
void			display_as_ptr(t_buffer *buf, t_format *in, size_t arg);
void			display_as_str(t_buffer *buf, t_format *in, size_t arg);
char			*parse_extras(const char **format);

#endif
