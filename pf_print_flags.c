/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:20:45 by fkao              #+#    #+#             */
/*   Updated: 2017/05/30 19:50:21 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	pf_put_sign(void)
{
	if ((g_attr.zero && !g_attr.dot) || g_attr.width <= 0 ||
		(g_attr.dot >= g_attr.width))
	{
		if (g_attr.nbr < 0)
			retint_putchar('-');
		else if (g_attr.nbr >= 0)
		{
			if (g_attr.cross)
				retint_putchar('+');
			else if (g_attr.space)
				retint_putchar(' ');
		}
		pf_put_width();
		pf_put_dot();
	}
	else
	{
		pf_put_width();
		if (g_attr.nbr < 0)
			retint_putchar('-');
		else if (g_attr.nbr >= 0 && g_attr.cross)
			retint_putchar('+');
		pf_put_dot();
	}
}

void	pf_put_hash(void)
{
	if (g_attr.hash && g_attr.zero)
	{
		if (g_attr.spec == 'o' && (g_attr.unlo > 0 || g_attr.prec))
			retint_putchar('0');
		if (g_attr.spec == 'x' && g_attr.unlo > 0)
		{
			if (g_attr.caps)
				retint_putstr("0X");
			else
				retint_putstr("0x");
		}
	}
	pf_put_width();
	if (g_attr.hash && !g_attr.zero)
	{
		if (g_attr.spec == 'o' && (g_attr.unlo > 0 || g_attr.prec))
			retint_putchar('0');
		else if (g_attr.caps && g_attr.unlo > 0)
			retint_putstr("0X");
		else if (g_attr.spec == 'p'|| g_attr.unlo > 0)
			retint_putstr("0x");
	}
	pf_put_dot();
}

void	pf_put_width(void)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	if (g_attr.zero && ((g_attr.spec != 's' && (g_attr.dot < g_attr.count)) ||
		(g_attr.spec == 's' && (g_attr.dot <= g_attr.count))))
		c = '0';
	if (!g_attr.dash && (g_attr.width > g_attr.dot))
	{
		if (g_attr.dot > g_attr.count)
			while (i++ < (g_attr.width - g_attr.dot))
				retint_putchar(c);
		if (g_attr.dot <= g_attr.count)
			while (i++ < (g_attr.width - g_attr.count))
				retint_putchar(c);
	}
}

void	pf_put_dot(void)
{
	int	i;

	i = 0;
	while (i++ < (g_attr.dot - g_attr.count))
		retint_putchar('0');
}

void	pf_put_left(void)
{
	int	i;

	i = 0;
	if (g_attr.dot > g_attr.count)
		g_attr.dot -= g_attr.count;
	else if (g_attr.dot <= g_attr.count)
		g_attr.dot = 0;
	if ((g_attr.width > 0) && g_attr.dash)
		while (i++ < (g_attr.width - g_attr.count - g_attr.dot))
			retint_putchar(' ');
}
