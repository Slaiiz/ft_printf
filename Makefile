NAME  =	libftprintf.a
CC    =	gcc
CFLAGS=	-Wall -Wextra -Werror
SRCS  =	ft_printf.c	utilities.c
OBJS  =	$(subst .c,.o,$(SRCS))

all: libft.a $(NAME)

nolibft: $(NAME)

libft.a:
	cd srcs/;\
	make -C libft/ re

$(NAME):
	cd srcs/;\
	$(CC) $(CFLAGS) -I ../includes/ -I libft/includes/ -c $(SRCS);\
	$(CC) $(CFLAGS) -I ../includes/ -I libft/includes/ -L libft/ test.c $(OBJS) -lft

clean:
	cd srcs/;\
	rm -f $(OBJS);\
	make -C libft/ clean

fclean: clean
	rm -f $(NAME);\
	make -C srcs/libft/ fclean

re: fclean all

.PHONY: all nolibft clean fclean re
