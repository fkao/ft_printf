/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 11:05:46 by fkao              #+#    #+#             */
/*   Updated: 2017/05/30 19:12:28 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <wchar.h>

typedef struct		s_attr
{
	char			*str;
	char			spec;
	int				ret;
	int				width;
	int				space;
	int				zero;
	int				cross;
	int				dash;
	int				hash;
	int				dot;
	int				prec;
	int				length;
	int				count;
	int				caps;
	long			nbr;
	unsigned long	unlo;
}					t_attr;

int					ft_printf(const char *format, ...);
extern t_attr		g_attr;
int					pf_ismodifier(int c);
int					pf_isspecifier(int c);
void				pf_signed_conversion(va_list ap);
void				pf_unsigned_convs(va_list ap);
void				pf_isolate_width(char *str);
void				pf_standardize_specs(char *str);
void				pf_parse_attributes(char *str);
void				pf_organize_length(char *str);
void				pf_width_correction(void);
void				pf_wide_characters(va_list ap);
void				pf_print_unsigned(va_list ap);
void				pf_print_singlechar(va_list ap);
void				pf_put_sign(void);
void				pf_put_hash(void);
void				pf_put_width(void);
void				pf_put_dot(void);
void				pf_put_left(void);
char				*ft_ultoa_base(unsigned long value, size_t base);
size_t				ft_countul_base(unsigned long nbr, size_t base);
void				retint_putchar(char c);
void				retint_putstr(char *s);
void				retint_putwchar(wchar_t chr);
void				retint_putwstr(wchar_t *str, size_t len);
void				retint_putnbrul(unsigned long n);
void				pf_reset_attr(void);
#endif
