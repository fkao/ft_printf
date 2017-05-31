# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/08 12:21:04 by fkao              #+#    #+#              #
#    Updated: 2017/05/24 15:05:43 by fkao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

INCL	= -I./libft \
			-I ft_printf.h

SFILE	= ft_printf.c \
			pf_check_format.c \
			pf_print_flags.c \
			pf_pull_args.c \
			pf_put_retint.c \
			pf_tools.c
SRC		= $(addprefix $(SDIR), $(SFILE))
SDIR	= ./

LFILE	= ft_atoi.c ft_countint.c ft_isdigit.c ft_isupper.c ft_memalloc.c \
			ft_putchar.c ft_putstr.c ft_strlen.c ft_strnew.c ft_strsub.c \
			ft_toabsl.c ft_tolower.c ft_toupper.c ft_bzero.c ft_isspace.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_strncpy.c ft_memset.c \
			ft_memdel.c ft_strdel.c
LIB		= $(addprefix $(LDIR), $(LFILE))
LDIR	= ./libft/

OFILE	= $(SRC:.c=.o) $(LFILE:.c=.o)
OBJ		= $(addprefix $(ODIR), $(OFILE))
ODIR	= ./obj/

FLAG	= -Wall -Wextra -Werror
RM		= rm -rf

all: $(NAME)

$(ODIR):
	@mkdir -p $(ODIR)
	@gcc -c $(FLAG) $(SRC) $(LIB) $(INCL)
	@mv $(OFILE) $(ODIR)

$(NAME): $(ODIR)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@$(RM) $(ODIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
