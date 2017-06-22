# gcc -Wformat=0 -c	main.c pf_tools.c ft_printf.c pf_check_format.c pf_print_flags.c pf_pull_args.c -I./libft -I./ft_printf.h
# gcc				main.o pf_tools.o ft_printf.o pf_check_format.o pf_print_flags.o pf_pull_args.o -L./libft -lft
# make re
gcc -Wformat=0 main.c -L./ -lftprintf
./a.out
rm -rf *.o a.out
