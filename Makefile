# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/08 12:21:04 by fkao              #+#    #+#              #
#    Updated: 2017/05/31 17:56:32 by fkao             ###   ########.fr        #
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

LFILE	= ft_atoi.c ft_isspace.c ft_countint.c ft_isdigit.c ft_isupper.c \
			ft_strdel.c ft_memdel.c ft_strlen.c ft_strnew.c ft_memalloc.c \
			ft_bzero.c ft_memset.c ft_strsub.c ft_strncpy.c ft_toabsl.c \
			ft_tolower.c

LIB		= $(addprefix $(LDIR), $(LFILE))
LDIR	= ./libft/

OFILE	= $(SRC:.c=.o) $(LFILE:.c=.o)
OBJ		= $(addprefix $(ODIR), $(OFILE))
ODIR	= ./obj/

FLAG	= -Wall -Wextra -Werror
RM		= rm -rf

all: $(NAME)

lib:
	@make -C $(LDIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@gcc -c $(FLAG) $(SRC) $(LIB) $(INCL)
	@mv $(OFILE) $(ODIR)

$(NAME): $(ODIR)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@$(RM) $(ODIR)
	@$(RM) $(LDIR)$(ODIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LDIR)libft.a

re: fclean all
