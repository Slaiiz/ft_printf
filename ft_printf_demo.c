/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_demo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 14:25:09 by vchesnea          #+#    #+#             */
/*   Updated: 2016/03/07 14:25:12 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <termios.h>

struct termios	attro;
struct termios	attrn;

static void	toggle_terminal(int flags)
{
	attrn.c_lflag ^= flags;
	tcsetattr(0, TCSANOW, &attrn);
}

static void	inform_user(void)
{
	short	c;
	char	buffer[32];

	ft_printf("\x1b[%d;%dH{{red;bu}}Drawing {{green}}is {{yellow}}FUN{{eoc}}!!",
		45, 0);
	ft_printf("\x1b[%d;%dH{{cyan;bx}}Pick an attribute: %s | %s | %s | %s\n",
		20, 8, "bold", "underline", "italic", "blink");
	ft_printf("\x1b[%d;%dH\x1b{{red;}}Warning:{{eoc;}} %s\n",
		21, 8, "italic may be imcompatible with your terminal emulator");
	ft_bzero(buffer, sizeof(char) * 32);
	c = 0x0000;
	while (read(0, (char*)&c, 1) > 0)
	{
		if (c == 0x0a)
			break ;
		ft_strlcat(buffer, (char*)&c, 32);
	}
	if (!ft_strcmp(ft_strlowcase(buffer), "bold"))
		ft_printf("{{magenta;b}}");
	else if (!ft_strcmp(ft_strlowcase(buffer), "underline"))
		ft_printf("{{magenta;u}}");
	else if (!ft_strcmp(ft_strlowcase(buffer), "italic"))
		ft_printf("{{magenta;i}}");
	else if (!ft_strcmp(ft_strlowcase(buffer), "blink"))
		ft_printf("{{magenta;x}}");
}

static void	setup_session(void)
{
	tcgetattr(0, &attro);
	ft_memcpy(&attrn, &attro, sizeof(struct termios));
	toggle_terminal(ICANON);
	ft_printf("#!clear^");
	inform_user();
	toggle_terminal(ECHO);
}

static void	reset_session(void)
{
	tcsetattr(0, TCSANOW, &attrn);
	ft_printf("#!clear^");
}

int			main(void)
{
	char	c;

	setup_session();
	while (read(0, &c, 1) > 0)
	{
		if (c == 0x1b)
		{
			ft_printf("##!left");
			read(0, &c, 1);
			if (c == 0x5b)
			{
				read(0, &c, 1);
				if (c == 0x41)
					ft_printf("#!up");
				else if (c == 0x43)
					ft_printf("#!right^");
				else if (c == 0x42)
					ft_printf("#!down^");
				else if (c == 0x44)
					ft_printf("#!left^");
			}
		}
	}
	reset_session();
	return (0);
}
