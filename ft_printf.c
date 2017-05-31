/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 11:12:30 by fkao              #+#    #+#             */
/*   Updated: 2017/05/30 19:45:52 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

t_attr	g_attr;

void	pf_print_unsigned(va_list ap)
{
	if (g_attr.spec == 'u')
		g_attr.str = ft_ultoa_base(g_attr.unlo, 10);
	if (g_attr.spec == 'o')
		g_attr.str = ft_ultoa_base(g_attr.unlo, 8);
	if (g_attr.spec == 'x' || g_attr.spec == 'p')
		g_attr.str = ft_ultoa_base(g_attr.unlo, 16);
	if (g_attr.spec == 's')
	{
		g_attr.str = va_arg(ap, char*);
		if (g_attr.str == NULL)
			g_attr.str = "(null)";
	}
	g_attr.count = (g_attr.prec && !g_attr.nbr) ? 0 : ft_strlen(g_attr.str);
	pf_width_correction();
	if (!g_attr.prec || g_attr.nbr)
		retint_putstr(g_attr.str);
	pf_put_left();
}

void	pf_print_singlechar(va_list ap)
{
	wchar_t	wchr;

	if (g_attr.length == 'l' && g_attr.spec == 'c' && MB_CUR_MAX != 1)
	{
		wchr = (wchar_t)va_arg(ap, wint_t);
		if (wchr <= 0x7F)
			g_attr.count = 1;
		else if (wchr <= 0x7FF)
			g_attr.count = 2;
		else if (wchr <= 0xFFFF)
			g_attr.count = 3;
		else if (wchr <= 0x10FFFF)
			g_attr.count = 4;
	}
	else
	{
		if (g_attr.spec == 'c')
			wchr = (char)va_arg(ap, int);
		if (g_attr.spec == '%')
			wchr = '%';
		g_attr.count = 1;
	}
	pf_width_correction();
	retint_putwchar(wchr);
	pf_put_left();
}

void	pf_print_specifiers(char *fmt, va_list ap)
{
	pf_organize_length(fmt);
	pf_unsigned_convs(ap);
	if (g_attr.spec == 's')
	{
		if (g_attr.length != 'l')
			pf_print_unsigned(ap);
		if (g_attr.length == 'l')
			pf_wide_characters(ap);
	}
	if (g_attr.spec == 'd')
	{
		g_attr.count = (g_attr.prec && !g_attr.nbr) ? 0 :
			(int)ft_countul_base(ft_toabsl(g_attr.nbr), 10);
		pf_width_correction();
		if (!g_attr.prec || g_attr.nbr)
			retint_putnbrul(ft_toabsl(g_attr.nbr));
		pf_put_left();
	}
	if (g_attr.spec == '%' || g_attr.spec == 'c')
		pf_print_singlechar(ap);
	if (g_attr.spec == 'u' || g_attr.spec == 'o' || g_attr.spec == 'x' ||
		g_attr.spec == 'p')
		pf_print_unsigned(ap);
}

void	pf_print_nospec(char *fmt, va_list ap)
{
	char	c;
	int		i;

	pf_print_specifiers(fmt, ap);
	if (!g_attr.spec)
	{
		c = (g_attr.zero) ? '0' : ' ';
		while (*fmt)
		{
			if (!pf_ismodifier(*fmt))
				break ;
			fmt++;
		}
		i = 0;
		if ((g_attr.width > 0) && !g_attr.dash)
			while (i++ < (g_attr.width - 1))
				retint_putchar(c);
		retint_putchar(*fmt);
		if ((g_attr.width > 0) && g_attr.dash)
			while (i++ < (g_attr.width - 1))
				retint_putchar(' ');
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	char	*tmp;

	va_start(ap, format);
	g_attr.ret = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			pf_reset_attr();
			i = 0;
			while (pf_ismodifier(format[i]))
				i++;
			tmp = ft_strsub(format, 0, i + 1);
			pf_print_nospec(tmp, ap);
			format += i;
		}
		else
			retint_putchar(*format);
		format++;
	}
	va_end(ap);
	return (g_attr.ret);
}
