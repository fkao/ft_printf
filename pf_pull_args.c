/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_pull_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:19:29 by fkao              #+#    #+#             */
/*   Updated: 2017/05/22 16:26:20 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_attr	*pf_signed_conversion(t_attr *mod, va_list ap)
{
	short	shrt;
	char	hhd;

	if (mod->spec == 'd')
	{
		if (mod->length == 'l')
			mod->nbr = va_arg(ap, long);
		else if (mod->length == 'h')
		{
			shrt = (short)va_arg(ap, int);
			mod->nbr = (long)shrt;
		}
		else if (mod->length == 'H')
		{
			hhd = (char)va_arg(ap, int);
			mod->nbr = (long)hhd;
		}
		else if (!mod->length)
			mod->nbr = (long)va_arg(ap, int);
	}
	return (mod);
}

t_attr	*pf_unsigned_convs(t_attr *mod, va_list ap)
{
	unsigned short	unsh;
	unsigned char	uchr;

	mod = pf_signed_conversion(mod, ap);
	if (mod->spec == 'o' || mod->spec == 'u' || mod->spec == 'x')
	{
		if (mod->length == 'l')
			mod->unlo = (unsigned long)va_arg(ap, unsigned long);
		else if (mod->length == 'h')
		{
			unsh = (unsigned short)va_arg(ap, unsigned int);
			mod->unlo = (unsigned long)unsh;
		}
		else if (mod->length == 'H')
		{
			uchr = (unsigned char)va_arg(ap, unsigned int);
			mod->unlo = (unsigned long)uchr;
		}
		else if (!mod->length)
			mod->unlo = (unsigned long)va_arg(ap, unsigned int);
	}
	return (mod);
}

void	pf_wide_characters(t_attr *mod, va_list ap)
{
	wchar_t	*tmp;

	mod->wstr = va_arg(ap, wchar_t*);
	tmp = mod->wstr;
	while (*tmp)
	{
		if (*tmp <= 0x7F)
			mod->count += 1;
		else if (*tmp <= 0x7FF)
			mod->count += 2;
		else if (*tmp <= 0xFFFF)
			mod->count += 3;
		else if (*tmp <= 0x10FFFF)
			mod->count += 4;
		tmp++;
	}
	pf_width_correction(mod);
	ft_putwstr(mod->wstr, mod->count);
	pf_put_left(mod);
}

void	ft_putwstr(wchar_t *str, size_t len)
{
	size_t	i;

	i = 0;
	while (*str && i < len)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		if (i <= len)
			ft_putwchar(*str++);
	}
}

void	ft_putwchar(wchar_t chr)
{
	if (chr <= 0x7F)
		ft_putchar(chr);
	else if (chr <= 0x7FF)
	{
		ft_putchar((chr >> 6) + 0xC0);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0xFFFF)
	{
		ft_putchar((chr >> 12) + 0xE0);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0x10FFFF)
	{
		ft_putchar((chr >> 18) + 0xF0);
		ft_putchar(((chr >> 12) & 0x3F) + 0x80);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
}
