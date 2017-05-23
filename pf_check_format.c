/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 19:00:56 by fkao              #+#    #+#             */
/*   Updated: 2017/05/22 18:26:48 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

t_attr	*pf_isolate_width(char *str)
{
	t_attr	*mod;

	mod = (t_attr*)ft_memalloc(sizeof(*mod));
	while (*str)
	{
		if (pf_isspecifier(*str))
			mod->spec = *str;
		if (ft_isdigit(*str) && str[-1] == '.')
		{
			mod->dot = ft_atoi(str);
			str += (ft_countint(mod->dot) - 1);
		}
		else if (*str > '0' && *str <= '9')
		{
			mod->width = ft_atoi(str);
			str += (ft_countint(mod->width) - 1);
		}
		else if (*str == '0')
			mod->zero = 1;
		str++;
	}
	if (mod->spec == 'i')
		mod->spec = 'd';
	return (mod);
}

t_attr	*pf_standardize_specs(char *str)
{
	t_attr	*mod;

	mod = pf_isolate_width(str);
	if (ft_isupper(mod->spec))
	{
		mod->spec = ft_tolower(mod->spec);
		if (mod->spec == 'x')
			mod->caps = 1;
		else
			mod->length = 'l';
	}
	if (mod->spec == 's' || mod->spec == 'c')
		while (*str)
		{
			if (*str == 'l')
			{
				if (str[1] == 'l')
					str++;
				else
					mod->length = 'l';
			}
			str++;
		}
	return (mod);
}

t_attr	*pf_parse_attributes(char *str)
{
	t_attr	*mod;

	mod = pf_standardize_specs(str);
	while (*str)
	{
		if (*str == ' ')
			if (mod->spec == 'd')
				mod->space = 1;
		if (*str == '+')
			if (mod->spec == 'd')
				mod->cross = 1;
		if (*str == '#')
			if (mod->spec == 'o' || mod->spec == 'x')
				mod->hash = 1;
		if (*str == '-')
			mod->dash = 1;
		str++;
	}
	return (mod);
}

t_attr	*pf_organize_length(char *str)
{
	t_attr	*mod;

	mod = pf_parse_attributes(str);
	while (*str && (mod->spec != 's' && mod->spec != 'c'))
	{
		if (*str == 'l' || *str == 'j' || *str == 'z')
			mod->length = 'l';
		if (*str == 'h' && mod->length != 'l')
		{
			if (str[1] == 'h' && mod->length != 'h')
			{
				mod->length = 'H';
				str++;
			}
			else
				mod->length = 'h';
		}
		str++;
	}
	return (mod);
}

void	pf_width_correction(t_attr *mod)
{
	if (mod->spec == 'd' || mod->spec == 'u')
	{
		if (mod->nbr < 0 || mod->cross || (mod->space && !mod->width))
			mod->width -= 1;
		pf_put_sign(mod);
	}
	if (mod->spec == 'o' || mod->spec == 'x' || mod->spec == 'p' )
	{
		if (mod->spec == 'o' && mod->hash && mod->unlo)
			mod->width -= 1;
		if ((mod->spec == 'x' && mod->hash && mod->unlo) || mod->spec == 'p')
			mod->width -= 2;
		pf_put_hash(mod);
	}
	if (mod->spec == 's' || mod->spec == 'c' || mod->spec == '%')
	{
		if (mod->dot && (mod->dot < mod->count) && mod->spec == 's')
		{
			mod->count = mod->dot;
			mod->str = ft_strsub(mod->str, 0, mod->dot);
		}
		mod->dot = 0;
		pf_put_width(mod);
	}
}
