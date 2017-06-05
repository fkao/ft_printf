/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_pull_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:19:29 by fkao              #+#    #+#             */
/*   Updated: 2017/05/31 18:42:31 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_signed_conversion(va_list ap)
{
	short	shrt;
	char	hhd;

	if (g_at.spec == 'd')
	{
		if (g_at.length == 'l')
			g_at.nbr = va_arg(ap, long);
		else if (g_at.length == 'h')
		{
			shrt = (short)va_arg(ap, int);
			g_at.nbr = (long)shrt;
		}
		else if (g_at.length == 'H')
		{
			hhd = (char)va_arg(ap, int);
			g_at.nbr = (long)hhd;
		}
		else if (!g_at.length)
			g_at.nbr = (long)va_arg(ap, int);
	}
}

void	pf_unsigned_convs(va_list ap)
{
	unsigned short	unsh;
	unsigned char	uchr;

	pf_signed_conversion(ap);
	if (g_at.spec == 'o' || g_at.spec == 'u' || g_at.spec == 'x')
	{
		if (g_at.length == 'l')
			g_at.unlo = (unsigned long)va_arg(ap, unsigned long);
		else if (g_at.length == 'h')
		{
			unsh = (unsigned short)va_arg(ap, unsigned int);
			g_at.unlo = (unsigned long)unsh;
		}
		else if (g_at.length == 'H')
		{
			uchr = (unsigned char)va_arg(ap, unsigned int);
			g_at.unlo = (unsigned long)uchr;
		}
		else if (!g_at.length)
			g_at.unlo = (unsigned long)va_arg(ap, unsigned int);
	}
	if (g_at.spec == 'p')
		g_at.unlo = (unsigned long)va_arg(ap, void*);
}

void	pf_wide_characters(va_list ap)
{
	wchar_t	*wstr;

	wstr = va_arg(ap, wchar_t*);
	if (wstr == NULL)
	{
		g_at.count = 5;
		pf_width_correction();
		retint_putstr("(null)");
		pf_put_left();
		return ;
	}
	g_at.count = pf_wstrlen(wstr);
	pf_width_correction();
	retint_putwstr(wstr, g_at.count);
	pf_put_left();
}

void	pf_reset_attr(void)
{
	g_at.spec = 0;
	g_at.width = 0;
	g_at.space = 0;
	g_at.zero = 0;
	g_at.cross = 0;
	g_at.dash = 0;
	g_at.hash = 0;
	g_at.dot = 0;
	g_at.length = 0;
	g_at.count = 0;
	g_at.caps = 0;
}
