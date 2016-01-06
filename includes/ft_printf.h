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

# define FLAG_ALT	0x00000001
# define FLAG_ZPAD	0x00000002
# define FLAG_BLANK	0x00000004
# define FLAG_SIGN	0x00000008
# define FLAG_NEGF	0x0000000C

# define APPEND		0x00000001
# define PREPEND	0x00000002

typedef struct	s_buffer
{
	char		*data;
	size_t		size;
}				t_buffer;

int				ft_printf(const char *format, ...);
int				parse_flags(const char **s);
#endif
