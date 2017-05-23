/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:20:45 by fkao              #+#    #+#             */
/*   Updated: 2017/05/22 17:00:14 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	pf_put_sign(t_attr *mod)
{
	if ((mod->zero && !mod->dot) || (mod->dot >= mod->width) || mod->width <= 0)
	{
		if (mod->nbr < 0)
			write(1, "-", 1);
		else if (mod->nbr >= 0)
		{
			if (mod->cross)
				write(1, "+", 1);
			else if (mod->space)
				write(1, " ", 1);
		}
		pf_put_width(mod);
		pf_put_dot(mod);
	}
	else
	{
		pf_put_width(mod);
		if (mod->nbr < 0)
			write(1, "-", 1);
		else if (mod->nbr >= 0 && mod->cross)
			write(1, "+", 1);
		pf_put_dot(mod);
	}
}

void	pf_put_hash(t_attr *mod)
{
	if (mod->hash && mod->unlo > 0)
	{
		if (mod->spec == 'o')
			write(1, "0", 1);
		if (mod->spec == 'x')
		{
			if (mod->caps)
				write(1, "0X", 2);
			else
				write(1, "0x", 2);
		}
	}
	pf_put_width(mod);
	if (mod->spec == 'p')
		write(1, "0x", 2);
	pf_put_dot(mod);
}

void	pf_put_width(t_attr *mod)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	if (mod->zero && ((mod->spec != 's' && (mod->dot < mod->count)) ||
		(mod->spec == 's' && (mod->dot <= mod->count))))
		c = '0';
	if (!mod->dash && (mod->width > mod->dot))
	{
		if (mod->dot > mod->count)
			while (i++ < (mod->width - mod->dot))
				ft_putchar(c);
		if (mod->dot <= mod->count)
			while (i++ < (mod->width - mod->count))
				ft_putchar(c);
	}
}

void	pf_put_dot(t_attr *mod)
{
	int		i;

	i = 0;
	while (i++ < (mod->dot - mod->count))
		write(1, "0", 1);
}

void	pf_put_left(t_attr *mod)
{
	int	i;

	i = 0;
	if (mod->dot > mod->count)
		mod->dot -= mod->count;
	else if (mod->dot <= mod->count)
		mod->dot = 0;
	if ((mod->width > 0) && mod->dash)
		while (i++ < (mod->width - mod->count - mod->dot))
			write(1, " ", 1);
}
