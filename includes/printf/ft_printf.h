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

# define ALT	0x01
# define ZPAD	0x02
# define BLANK	0x04
# define SIGN	0x08
# define NEGF	0x10

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

# define NUMERIC	0x1000
# define STRING		0x2000
# define POINTER	0x4000

# define APPEND		1
# define PREPEND	2

# define PRECISION	1
# define FIELDWIDTH	2

# define MISSING	-1

typedef struct	s_buffer
{
	int			fd;
	size_t		len;
	size_t		size;
	char		*data;
	size_t		written;
}				t_buffer;

typedef struct	s_format
{
	char		flags;
	size_t		modif;
	int			prec;
	int			field;
	short		conv;
}				t_format;

int				ft_printf(const char *format, ...);
void			write_to_buffer(t_buffer *in, int mode, int len, const char *s);
void			get_flags(t_format *out, const char **s);
void			get_precision(t_format *out, const char **s);
void			get_modifier(t_format *out, const char **s);
void			get_conversion(t_format *out, const char **s);
size_t			sign_extend(t_format *format, size_t arg);
void			pad_buffer(t_buffer *buf, t_format *in, int fpad, int ppad);
void			display_as_dec(t_buffer *buf, t_format *in, size_t arg);
void			display_as_hex(t_buffer *buf, t_format *in, size_t arg);
void			display_as_ptr(t_buffer *buf, t_format *in, size_t arg);
void			display_as_str(t_buffer *buf, t_format *in, size_t arg);
void			parse_extras(t_buffer *buf, const char **format);

#endif
