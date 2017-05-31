/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 19:00:56 by fkao              #+#    #+#             */
/*   Updated: 2017/05/30 19:40:15 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	pf_isolate_width(char *str)
{
	while (*str)
	{
		if (pf_isspecifier(*str))
			g_attr.spec = *str;
		if (*str == '.')
		{
			g_attr.dot = ft_isdigit(str[1]) ? ft_atoi(str + 1) : 0;
			g_attr.prec = (g_attr.dot) ? 0 : 1;
			str += ft_isdigit(str[1]) ? (ft_countint(g_attr.dot)) : 0;
		}
		else if (*str > '0' && *str <= '9')
		{
			g_attr.width = ft_atoi(str);
			str += (ft_countint(g_attr.width) - 1);
		}
		else if (*str == '0')
			g_attr.zero = 1;
		str++;
	}
	if (g_attr.spec == 'i')
		g_attr.spec = 'd';
}

void	pf_standardize_specs(char *str)
{
	pf_isolate_width(str);
	if (ft_isupper(g_attr.spec))
	{
		g_attr.spec = ft_tolower(g_attr.spec);
		if (g_attr.spec == 'x')
			g_attr.caps = 1;
		else
			g_attr.length = 'l';
	}
	if (g_attr.spec == 's' || g_attr.spec == 'c')
		while (*str)
		{
			if (*str == 'l')
			{
				if (str[1] == 'l')
					str++;
				else
					g_attr.length = 'l';
			}
			str++;
		}
}

void	pf_parse_attributes(char *str)
{
	pf_standardize_specs(str);
	while (*str)
	{
		if (*str == ' ')
			if (g_attr.spec == 'd')
				g_attr.space = 1;
		if (*str == '+')
			if (g_attr.spec == 'd')
				g_attr.cross = 1;
		if (*str == '#')
			if (g_attr.spec == 'o' || g_attr.spec == 'x')
				g_attr.hash = 1;
		if (*str == '-')
			g_attr.dash = 1;
		str++;
	}
}

void	pf_organize_length(char *str)
{
	pf_parse_attributes(str);
	while (*str && (g_attr.spec != 's' && g_attr.spec != 'c'))
	{
		if (*str == 'l' || *str == 'j' || *str == 'z')
			g_attr.length = 'l';
		if (*str == 'h' && g_attr.length != 'l')
		{
			if (str[1] == 'h' && g_attr.length != 'h')
			{
				g_attr.length = 'H';
				str++;
			}
			else
				g_attr.length = 'h';
		}
		str++;
	}
}

void	pf_width_correction(void)
{
	if (g_attr.spec == 'd' || g_attr.spec == 'u')
	{
		if (g_attr.nbr < 0 || g_attr.cross || (g_attr.space && !g_attr.width))
			g_attr.width -= 1;
		pf_put_sign();
	}
	if (g_attr.spec == 'o' || g_attr.spec == 'x' || g_attr.spec == 'p')
	{
		if (g_attr.spec == 'o' && g_attr.hash && g_attr.unlo)
			g_attr.width -= 1;
		if ((g_attr.spec == 'x' && g_attr.hash && g_attr.unlo) ||
			g_attr.spec == 'p')
			g_attr.width -= 2;
		pf_put_hash();
	}
	if (g_attr.spec == 's' || g_attr.spec == 'c' || g_attr.spec == '%')
	{
		if (g_attr.dot && (g_attr.dot < g_attr.count) && g_attr.spec == 's')
		{
			g_attr.count = g_attr.dot;
			g_attr.str = ft_strsub(g_attr.str, 0, g_attr.dot);
		}
		g_attr.dot = 0;
		pf_put_width();
	}
}
