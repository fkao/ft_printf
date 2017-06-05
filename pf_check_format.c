/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 19:00:56 by fkao              #+#    #+#             */
/*   Updated: 2017/05/31 18:56:31 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

void	pf_isolate_width(char *fmt)
{
	while (*fmt)
	{
		if (pf_isspecifier(*fmt))
			g_at.spec = *fmt;
		if (*fmt == '.')
		{
			g_at.prec = ft_isdigit(fmt[1]) ? ft_atoi(fmt + 1) : 0;
			g_at.dot = (g_at.prec) ? 0 : 1;
			fmt += ft_isdigit(fmt[1]) ? (ft_countint(g_at.prec)) : 0;
		}
		else if (*fmt > '0' && *fmt <= '9')
		{
			g_at.width = ft_atoi(fmt);
			fmt += (ft_countint(g_at.width) - 1);
		}
		else if (*fmt == '0')
			g_at.zero = 1;
		fmt++;
	}
	if (g_at.spec == 'i')
		g_at.spec = 'd';
}

void	pf_standardize_specs(char *fmt)
{
	pf_isolate_width(fmt);
	if (ft_isupper(g_at.spec))
	{
		g_at.spec = ft_tolower(g_at.spec);
		if (g_at.spec == 'x')
			g_at.caps = 1;
		else
			g_at.length = 'l';
	}
	if (g_at.spec == 's' || g_at.spec == 'c')
		while (*fmt)
		{
			if (*fmt == 'l')
			{
				if (fmt[1] == 'l')
					fmt++;
				else
					g_at.length = 'l';
			}
			fmt++;
		}
}

void	pf_parse_attributes(char *fmt)
{
	pf_standardize_specs(fmt);
	while (*fmt)
	{
		if (*fmt == ' ')
			if (g_at.spec == 'd')
				g_at.space = 1;
		if (*fmt == '+')
			if (g_at.spec == 'd')
				g_at.cross = 1;
		if (*fmt == '#')
			if (g_at.spec == 'o' || g_at.spec == 'x')
				g_at.hash = 1;
		if (*fmt == '-')
			g_at.dash = 1;
		fmt++;
	}
}

void	pf_organize_length(char *fmt)
{
	pf_parse_attributes(fmt);
	while (*fmt && (g_at.spec != 's' && g_at.spec != 'c'))
	{
		if (*fmt == 'l' || *fmt == 'j' || *fmt == 'z')
			g_at.length = 'l';
		if (*fmt == 'h' && g_at.length != 'l')
		{
			if (fmt[1] == 'h' && g_at.length != 'h')
			{
				g_at.length = 'H';
				fmt++;
			}
			else
				g_at.length = 'h';
		}
		fmt++;
	}
}

void	pf_width_correction(void)
{
	if (g_at.spec == 'd' || g_at.spec == 'u')
	{
		if (g_at.nbr < 0 || g_at.cross || (g_at.space &&
			(!g_at.width || g_at.zero)))
			g_at.width -= 1;
		pf_put_sign();
	}
	if (g_at.spec == 'o' || g_at.spec == 'x' || g_at.spec == 'p')
	{
		if (g_at.spec == 'o' && g_at.hash && g_at.unlo)
			g_at.width -= 1;
		if ((g_at.spec == 'x' && g_at.hash && g_at.unlo) || g_at.spec == 'p')
			g_at.width -= 2;
		pf_put_hash();
	}
	if (g_at.spec == 's' || g_at.spec == 'c' || g_at.spec == '%')
	{
		if (g_at.prec && (g_at.prec < g_at.count) && g_at.spec == 's')
		{
			g_at.count = g_at.prec;
			g_at.out = ft_strsub(g_at.str, 0, g_at.prec);
		}
		g_at.prec = 0;
		pf_put_width();
	}
}
