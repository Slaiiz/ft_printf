/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/02 13:37:38 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/02 13:37:38 by vchesnea         ###   ########.fr       */
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

# define CONV_INT	0x001
# define CONV_STR	0x002
# define CONV_WSTR	0x004
# define CONV_PTR	0x008
# define CONV_OCT	0x010
# define CONV_UINT	0x020
# define CONV_HEXL	0x040
# define CONV_HEXU	0x080
# define CONV_CHAR	0x100
# define CONV_WCHAR	0x200

# define APPEND		1
# define PREPEND	2

# define PRECISION	1
# define FIELDWIDTH	2

# define MISSING	-1
# define INVALID	-2

typedef struct	s_buffer
{
	size_t		len;
	size_t		size;
	char		*data;
}				t_buffer;

typedef struct	s_format
{
	intmax_t	fd;
	char		flags;
	size_t		modifier;
	int			precision;
	int			fieldwidth;
	short		conversion;
}				t_format;

int				ft_printf(const char *format, ...);
void			write_to_buffer(t_buffer *in, int mode, int len, const char *s);
void			get_flags(t_format *out, const char **s);
void			get_precision(t_format *out, const char **s);
void			get_modifier(t_format *out, const char **s);
void			get_conversion(t_format *out, const char **s);
void			pad_buffer(t_buffer *buf, t_format *in, int fpad, int ppad);
void			display_as_dec(t_buffer *buf, t_format *in, size_t arg);
void			display_as_hex(t_buffer *buf, t_format *in, size_t arg);
void			display_as_ptr(t_buffer *buf, t_format *in, size_t arg);
void			display_as_str(t_buffer *buf, t_format *in, size_t arg);
char			*parse_extras(const char **format);

#endif
