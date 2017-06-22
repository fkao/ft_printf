/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 19:43:57 by fkao              #+#    #+#             */
/*   Updated: 2017/06/21 17:32:25 by fkao             ###   ########.fr       */
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
	printf("%s\n", "printf:");
	printf("\treturn: %d\n", printf("%15.4S", L"ĦƐȽĿO™ ŴØɌ ŁƉ"));
	ft_printf("%s\n", "ft_printf:");
	ft_printf("\treturn: %d\n", ft_printf("%15.4S", L"ĦƐȽĿO™ ŴØɌ ŁƉ"));
	return (0);
}
