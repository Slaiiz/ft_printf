/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:34:55 by vchesnea          #+#    #+#             */
/*   Updated: 2015/12/04 11:22:31 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	printaddr(void *addr)
{
	size_t	len;

	len = 8 - ft_nbrlen((int)addr, 16);
	while (len--)
		ft_putchar('0');
	ft_putnbr_base((int)addr, 16);
	return ;
}

static void	printbyte(void **addr, int n)
{
	size_t	len;

	ft_putstr(" ");
	while (n--)
	{
		ft_putchar(' ');
		len = 2 - ft_nbrlen(**(int**)addr & 0xFF, 16);
		while (len--)
			ft_putchar('0');
		ft_putnbr_base(**(int**)addr & 0xFF, 16);
		(*addr)++;
	}
	return ;
}

static void	printascii(void **addr, int n)
{
	int	byte;

	ft_putstr("  ");
	while (n--)
	{
		byte = **(int**)addr & 0xFF;
		if (ft_isprint(byte))
			ft_putchar(byte);
		else
			ft_putchar('.');
		(*addr)++;
	}
	return ;
}

static void	printpad(char c, int n)
{
	while (n--)
	{
		ft_putchar(c);
		ft_putchar(c);
		ft_putchar(c);
	}
	return ;
}

void		ft_printmem(void *addr, size_t len)
{
	void	*bak;

	bak = addr;
	while (len >= 16)
	{
		printaddr(addr);
		printbyte(&addr, 16);
		printascii(&bak, 16);
		ft_putchar('\n');
		len -= 16;
	}
	if (len > 0)
	{
		printaddr(addr);
		printbyte(&addr, len);
		printpad(' ', 16 - len);
		printascii(&bak, len);
	}
	ft_putchar('\n');
	return ;
}
