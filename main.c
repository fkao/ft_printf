/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 19:43:57 by fkao              #+#    #+#             */
/*   Updated: 2017/06/19 15:36:58 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <limits.h>

int		ft_printf(const char *format, ...);

int		main(void)
{
	setlocale(LC_ALL, "");
	printf("%x\n", LONG_MIN - 1);
	printf("%C\n", L'猫');
	printf("%s\n", "printf:");
	printf("\treturn: %d\n", printf("%15.4S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B"));
	ft_printf("%s\n", "ft_printf:");
	ft_printf("\treturn: %d\n", ft_printf("%15.4S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B"));
	return (0);
}
