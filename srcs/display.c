/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/09 17:12:03 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/09 17:12:03 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	display_as_decimal(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		base;

	if (in->conversion & (CONV_INT | CONV_UINT))
		base = 10;
	else if (in->conversion & CONV_OCT)
		base = 8;
	if ((out = ft_itoa_base64(arg, base)) == NULL)
		return ;
}

void	display_as_hexadecimal(t_buffer *buf, t_format *in, size_t arg)
{
	char	*out;
	int		len;

	if ((out = ft_itoa_base64(arg, 16)) == NULL)
		return ;
	if (in->conversion & CONV_HEXL)
		ft_strlowcase(out);
	else
		ft_strupcase(out);
	len = ft_strlen(out);
	write_to_buffer(buf, APPEND, "0x");

}

void	display_as_pointer(t_buffer *buf, t_format *in, size_t arg)
{

}

void	display_as_string(t_buffer *buf, t_format *in, size_t arg)
{

}
