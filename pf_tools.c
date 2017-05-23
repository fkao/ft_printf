/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 18:29:15 by fkao              #+#    #+#             */
/*   Updated: 2017/05/22 16:51:45 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_isspecifier(int c)
{
	return (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' ||
		c == 'X' || c == 'D' || c == 'O' || c == 'U' || c == 's' || c == 'S' ||
		c == 'c' || c == 'C' || c == 'p' || c == '%');
}

int		pf_ismodifier(int c)
{
	return (ft_isdigit(c) || c == ' ' || c == '+' || c == '-' || c == '#' ||
		c == '.' || c == 'h' || c == 'l' || c == 'j' || c == 'z');
}

size_t	ft_countul_base(unsigned long nbr, size_t base)
{
	size_t	i;

	i = 0;
	if (nbr == 0)
		i++;
	while (nbr)
	{
		i++;
		nbr /= base;
	}
	return (i);
}

char	*ft_ultoa_base(unsigned long value, size_t base)
{
	char		*str;
	char		*ptr;
	int			len;
	const char	*t = "0123456789abcdef";

	len = ft_countul_base(value, base);
	str = ft_strnew(len);
	if (value == 0)
		*str = '0';
	ptr = str + len;
	*ptr-- = '\0';
	while (value)
	{
		*ptr = t[value % base];
		value /= base;
		ptr--;
	}
	return (str);
}

void	ft_putnbrul(unsigned long n)
{
	if (n > 9)
	{
		ft_putnbrul(n / 10);
		ft_putnbrul(n % 10);
	}
	else
		ft_putchar(n + '0');
}
