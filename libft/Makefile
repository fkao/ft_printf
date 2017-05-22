# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/27 11:19:09 by fkao              #+#    #+#              #
#    Updated: 2017/05/18 18:05:59 by fkao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

INCL	= -I libft.h

SRC		= ft_atoi.c ft_itoa.c ft_tolower.c ft_toupper.c ft_toabsl.c\
ft_countint.c ft_countlst.c ft_countstr.c \
ft_islower.c ft_isupper.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_isspace.c \
ft_bzero.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	ft_memset.c ft_memalloc.c ft_memdel.c \
ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strcmp.c \
	ft_strncmp.c ft_strcpy.c ft_strncpy.c ft_strdup.c ft_strlen.c ft_strstr.c \
	ft_strnstr.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
	ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strctrim.c ft_strsplit.c \
	ft_strrev.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstend.c ft_lstiter.c \
	ft_lstmap.c \
ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
	ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c

OBJ		= $(addprefix $(ODIR), $(SRC:.c=.o))
ODIR	= obj/

CC		= gcc
FLAG	= -Wall -Wextra -Werror
RM		= rm -rf

all: $(NAME)

ofile:
	@mkdir -p $(ODIR)

$(ODIR)%.o: %.c
	@$(CC) $(FLAG) $(INCL) -c $< -o $@

$(NAME): ofile $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@$(RM) $(ODIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
