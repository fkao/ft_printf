/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 11:12:30 by fkao              #+#    #+#             */
/*   Updated: 2017/05/31 19:04:12 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

t_attr	g_at;

void	pf_print_unsigned(va_list ap)
{
	if (g_at.spec == 'u')
		g_at.out = pf_ultoa_base(g_at.unlo, 10);
	if (g_at.spec == 'o')
		g_at.out = pf_ultoa_base(g_at.unlo, 8);
	if (g_at.spec == 'x' || g_at.spec == 'p')
		g_at.out = pf_ultoa_base(g_at.unlo, 16);
	if (g_at.spec == 's')
	{
		g_at.str = (va_arg(ap, char*));
		g_at.out = (g_at.str == NULL) ?
			ft_strnew(5) : ft_strnew(ft_strlen(g_at.str));
		g_at.out = (g_at.str == NULL) ? "(null)" : g_at.str;
	}
	g_at.count = (g_at.dot && !g_at.unlo && g_at.spec != 's')
		? 0 : ft_strlen(g_at.out);
	pf_width_correction();
	if (!g_at.dot || g_at.unlo || g_at.spec == 's')
		retint_putstr(g_at.out);
	pf_put_left();
}

void	pf_print_singlechar(va_list ap)
{
	wchar_t	wchr;

	if (g_at.length == 'l' && g_at.spec == 'c' && MB_CUR_MAX != 1)
	{
		wchr = (wchar_t)va_arg(ap, wint_t);
		if (wchr <= 0x7F)
			g_at.count = 1;
		else if (wchr <= 0x7FF)
			g_at.count = 2;
		else if (wchr <= 0xFFFF)
			g_at.count = 3;
		else if (wchr <= 0x10FFFF)
			g_at.count = 4;
	}
	else
	{
		if (g_at.spec == 'c')
			wchr = (char)va_arg(ap, int);
		if (g_at.spec == '%')
			wchr = '%';
		g_at.count = 1;
	}
	pf_width_correction();
	retint_putwchar(wchr);
	pf_put_left();
}

void	pf_branch_specifiers(va_list ap)
{
	pf_unsigned_convs(ap);
	if (g_at.spec == 's')
	{
		if (g_at.length != 'l')
			pf_print_unsigned(ap);
		if (g_at.length == 'l')
			pf_wide_characters(ap);
	}
	if (g_at.spec == 'd')
	{
		g_at.count = (g_at.dot && !g_at.nbr) ? 0 :
			(int)pf_countul_base(ft_toabsl(g_at.nbr), 10);
		pf_width_correction();
		if (!g_at.dot || g_at.nbr)
			retint_putnbrul(ft_toabsl(g_at.nbr));
		pf_put_left();
	}
	if (g_at.spec == '%' || g_at.spec == 'c')
		pf_print_singlechar(ap);
	if (g_at.spec == 'u' || g_at.spec == 'o' || g_at.spec == 'x' ||
		g_at.spec == 'p')
	{
		pf_print_unsigned(ap);
		ft_strdel(&g_at.out);
	}
}

void	pf_print_nospec(char *fmt, va_list ap)
{
	char	c;
	int		i;

	pf_organize_length(fmt);
	if (!g_at.spec)
	{
		c = (g_at.zero) ? '0' : ' ';
		while (*fmt)
		{
			if (!pf_ismodifier(*fmt))
				break ;
			fmt++;
		}
		i = 0;
		if ((g_at.width > 0) && !g_at.dash)
			while (i++ < (g_at.width - 1))
				retint_putchar(c);
		retint_putchar(*fmt);
		if ((g_at.width > 0) && g_at.dash)
			while (i++ < (g_at.width - 1))
				retint_putchar(' ');
	}
	else
		pf_branch_specifiers(ap);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	char	*tmp;

	va_start(ap, format);
	g_at.ret = 0;
	while (*format)
	{
		if (*format == '%')
		{
			pf_reset_attr();
			i = 1;
			while (pf_ismodifier(format[i]))
				i++;
			tmp = ft_strsub(format, 1, i);
			pf_print_nospec(tmp, ap);
			ft_strdel(&tmp);
			format += i;
		}
		else
			retint_putchar(*format);
		format++;
	}
	va_end(ap);
	return ((int)g_at.ret);
}
