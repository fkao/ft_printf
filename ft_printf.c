/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 11:12:30 by fkao              #+#    #+#             */
/*   Updated: 2017/05/22 19:42:06 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

void	pf_print_unsigned(t_attr *mod, va_list ap)
{
	char	*tmp;

	if (mod->spec == 'u')
		mod->str = ft_ultoa_base(mod->unlo, 10);
	if (mod->spec == 'o')
		mod->str = ft_ultoa_base(mod->unlo, 8);
	if (mod->spec == 'x')
	{
		mod->str = ft_ultoa_base(mod->unlo, 16);
		if (mod->caps && (tmp = mod->str))
			while (*tmp)
			{
				*tmp = ft_toupper(*tmp);
				tmp++;
			}
	}
	if (mod->spec == 's')
		mod->str = va_arg(ap, char*);
	if (mod->spec == 'p')
		mod->str = ft_ultoa_base(mod->unlo, 16);
	mod->count = ft_strlen(mod->str);
	pf_width_correction(mod);
	ft_putstr(mod->str);
	pf_put_left(mod);
}

void	pf_print_singlechar(t_attr *mod, va_list ap)
{
	wchar_t	wchr;

	if (mod->length == 'l' && mod->spec == 'c' && MB_CUR_MAX != 1)
	{
		wchr = (wchar_t)va_arg(ap, wint_t);
		if (wchr <= 0x7F)
			mod->count = 1;
		else if (wchr <= 0x7FF)
			mod->count = 2;
		else if (wchr <= 0xFFFF)
			mod->count = 3;
		else if (wchr <= 0x10FFFF)
			mod->count = 4;
	}
	else
	{
		if (mod->spec == 'c')
			wchr = (char)va_arg(ap, int);
		if (mod->spec == '%')
			wchr = '%';
		mod->count = 1;
	}
	pf_width_correction(mod);
	ft_putwchar(wchr);
	pf_put_left(mod);
}

t_attr	*pf_print_specifiers(char *fmt, va_list ap)
{
	t_attr	*mod;

	mod = pf_organize_length(fmt);
	mod = pf_unsigned_convs(mod, ap);
	if (mod->spec == 's')
	{
		if (mod->length != 'l')
			pf_print_unsigned(mod, ap);
		if (mod->length == 'l')
			pf_wide_characters(mod, ap);
	}
	if (mod->spec == 'd')
	{
		mod->count = (int)ft_countul_base(ft_toabsl(mod->nbr), 10);
		pf_width_correction(mod);
		ft_putnbrul(ft_toabsl(mod->nbr));
		pf_put_left(mod);
	}
	if (mod->spec == '%' || mod->spec == 'c')
		pf_print_singlechar(mod, ap);
	if (mod->spec == 'u' || mod->spec == 'o' || mod->spec == 'x' ||
		mod->spec == 'p')
		pf_print_unsigned(mod, ap);
	return (mod);
}

void	pf_print_nospec(char *fmt, va_list ap)
{
	t_attr	*mod;
	char	c;
	int		i;

	mod = pf_print_specifiers(fmt, ap);
	if (!mod->spec)
	{
		c = ' ';
		if (mod->zero)
			c = '0';
		while (*fmt)
		{
			if (!pf_ismodifier(*fmt))
				break ;
			fmt++;
		}
		i = 0;
		if ((mod->width > 0) && !mod->dash)
			while (i++ < (mod->width - 1))
				ft_putchar(c);
		ft_putchar(*fmt);
		if ((mod->width > 0) && mod->dash)
			while (i++ < (mod->width - 1))
				write(1, " ", 1);
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	char	*tmp;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			i = 0;
			while (pf_ismodifier(format[i]))
				i++;
			tmp = ft_strsub(format, 0, i + 1);
			pf_print_nospec(tmp, ap);
			format += i;
		}
		else
			write(1, &*format, 1);
		format++;
	}
	va_end(ap);
	return (0);
}
