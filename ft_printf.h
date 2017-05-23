/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 11:05:46 by fkao              #+#    #+#             */
/*   Updated: 2017/05/22 18:33:13 by fkao             ###   ########.fr       */
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
	int				width;
	int				space;
	int				zero;
	int				cross;
	int				dash;
	int				hash;
	int				dot;
	int				length;
	int				count;
	int				caps;
	long			nbr;
	unsigned long	unlo;
}					t_attr;

int					ft_printf(const char *format, ...);
int					pf_ismodifier(int c);
int					pf_isspecifier(int c);
t_attr				*pf_signed_conversion(t_attr *mod, va_list ap);
t_attr				*pf_unsigned_convs(t_attr *mod, va_list ap);
t_attr				*pf_isolate_width(char *str);
t_attr				*pf_standardize_specs(char *str);
t_attr				*pf_parse_attributes(char *str);
t_attr				*pf_organize_length(char *str);
void				pf_width_correction(t_attr *mod);
void				pf_put_sign(t_attr *mod);
void				pf_put_hash(t_attr *mod);
void				pf_put_width(t_attr *mod);
void				pf_put_dot(t_attr *mod);
void				pf_put_left(t_attr *mod);
void				ft_putnbrul(unsigned long n);
char				*ft_ultoa_base(unsigned long value, size_t base);
size_t				ft_countul_base(unsigned long nbr, size_t base);
void				ft_putwchar(wchar_t chr);
void				ft_putwstr(wchar_t *str, size_t len);
void				pf_wide_characters(t_attr *mod, va_list ap);
#endif
