/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/04 14:11:48 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/04 14:11:48 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int		len;
//	printf("Users: %d | Server: %s\n", 42, "Horizon");
	ft_printf("Users: %d | Server: %s\n", 42, "Horizon");
//	printf("%p\t%02lx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", 0x401000, 42, 63, 92, 0, 0, 255, 254, 12);
	ft_printf("%p\t{red}%02lx {green}%02hhx {blue}%02hhx {magenta}%02hhx {white}%02hhx {cyan}%02hhx {yellow}%02hhx {black}%02hhx\n", 0x401000, 42, 63, 92, 0, 0, 255, 254, 12);
//	printf("%-012s\n", "Hello");
	ft_printf("%-012s\n", "Hello");
//	printf("Hello\n%#7.4hx\nPouet\n", (unsigned short)257);
	ft_printf("Hello\n%#7.4hx\nPouet\n", (unsigned short)257);
//	printf("%04x\n", 255);
	ft_printf("%04x\n", 255);
//	printf("%S\n", "ÓÔØÁˇ‰´„ŒÅÍÎ");
//	printf("%S\n", L"Ø");
	ft_printf("{red}Hel{green}lo wo{blue}rld!{black}\n");
	ft_printf("{red}%.8hX{black}\n", 65535);
	return (0);
}
