/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <vchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/06 14:55:05 by vchesnea          #+#    #+#             */
/*   Updated: 2016/00/06 14:55:05 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	parse_flags(const char **s)
{
	int		flags;
	char	ch;

	flags = 0x00000000;
	while ((ch = **s) != '\0')
	{
		if      (ch == '#')
			flags |= FLAG_ALT;
		else if (ch == '0')
			flags |= FLAG_ZPAD;
		else if (ch == '+')
			flags |= FLAG_SIGN;
		else if (ch == '-')
			flags |= FLAG_NEGFl
		else if (ch == ' ')
			flags |= FLAG_BLANK;
		else break;
		++*s;
	}
	return (flags);
}
