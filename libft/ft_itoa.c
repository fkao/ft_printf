/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:01:33 by fkao              #+#    #+#             */
/*   Updated: 2017/03/06 19:21:30 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	char		*str;
	char		*ptr;
	size_t		len;
	long		nbr;

	nbr = (long)n;
	len = ft_intlen(nbr);
	str = ft_strnew(len);
	if (str)
	{
		ptr = str + len - 1;
		if (nbr < 0)
		{
			*str = '-';
			nbr *= -1;
		}
		while (nbr > 9)
		{
			*ptr-- = '0' + (nbr % 10);
			nbr /= 10;
		}
		*ptr = '0' + nbr;
	}
	return (str);
}
