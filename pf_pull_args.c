/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_pull_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:19:29 by fkao              #+#    #+#             */
/*   Updated: 2017/05/30 18:34:02 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_signed_conversion(va_list ap)
{
	short	shrt;
	char	hhd;

	if (g_attr.spec == 'd')
	{
		if (g_attr.length == 'l')
			g_attr.nbr = va_arg(ap, long);
		else if (g_attr.length == 'h')
		{
			shrt = (short)va_arg(ap, int);
			g_attr.nbr = (long)shrt;
		}
		else if (g_attr.length == 'H')
		{
			hhd = (char)va_arg(ap, int);
			g_attr.nbr = (long)hhd;
		}
		else if (!g_attr.length)
			g_attr.nbr = (long)va_arg(ap, int);
	}
}

void	pf_unsigned_convs(va_list ap)
{
	unsigned short	unsh;
	unsigned char	uchr;

	pf_signed_conversion(ap);
	if (g_attr.spec == 'o' || g_attr.spec == 'u' || g_attr.spec == 'x')
	{
		if (g_attr.length == 'l')
			g_attr.unlo = (unsigned long)va_arg(ap, unsigned long);
		else if (g_attr.length == 'h')
		{
			unsh = (unsigned short)va_arg(ap, unsigned int);
			g_attr.unlo = (unsigned long)unsh;
		}
		else if (g_attr.length == 'H')
		{
			uchr = (unsigned char)va_arg(ap, unsigned int);
			g_attr.unlo = (unsigned long)uchr;
		}
		else if (!g_attr.length)
			g_attr.unlo = (unsigned long)va_arg(ap, unsigned int);
	}
	if (g_attr.spec == 'p')
		g_attr.unlo = (unsigned long)va_arg(ap, void*);
}

void	pf_wide_characters(va_list ap)
{
	wchar_t	*wstr;
	wchar_t	*tmp;

	wstr = va_arg(ap, wchar_t*);
	tmp = wstr;
	while (*tmp)
	{
		if (*tmp <= 0x7F)
			g_attr.count += 1;
		else if (*tmp <= 0x7FF)
			g_attr.count += 2;
		else if (*tmp <= 0xFFFF)
			g_attr.count += 3;
		else if (*tmp <= 0x10FFFF)
			g_attr.count += 4;
		tmp++;
	}
	pf_width_correction();
	retint_putwstr(wstr, g_attr.count);
	pf_put_left();
}
