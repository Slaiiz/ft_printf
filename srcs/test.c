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

int	main(void)
{
	ft_printf("Users: %d | Server: %s\n", 42, "Horizon");
	ft_printf("%p\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", 0x401000, 42, 63, 92, 0, 0, 255, 254, 12);
//	ft_printf("%-012s\n", "Hello");
//	ft_printf("Hello\n%#6.8hx\nPouet\n", (unsigned short)257);
	return (0);
}
