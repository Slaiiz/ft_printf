CC    =	gcc
CFLAGS=	-Wall -Wextra -Werror
NAME  =	libftprintf.a
SRCS  =	ft_atoi.c			ft_bzero.c		ft_isalnum.c		ft_isalpha.c	ft_isascii.c\
		ft_isdigit.c		ft_isprint.c	ft_itoa.c			ft_lstadd.c		ft_lstdel.c\
		ft_lstdelone.c		ft_lstiter.c	ft_lstmap.c			ft_lstnew.c		ft_memalloc.c\
		ft_memccpy.c		ft_memchr.c		ft_memcmp.c			ft_memcpy.c		ft_memdel.c\
		ft_memmove.c		ft_memset.c		ft_putchar.c		ft_putchar_fd.c	ft_putendl.c\
		ft_putendl_fd.c		ft_putnbr.c		ft_putnbr_fd.c		ft_putstr.c		ft_putstr_fd.c\
		ft_strcat.c			ft_strchr.c		ft_strclr.c			ft_strcmp.c		ft_strcpy.c\
		ft_strdel.c			ft_strdup.c		ft_strequ.c			ft_striter.c	ft_striteri.c\
		ft_strjoin.c		ft_strlcat.c  	ft_strlen.c			ft_strmap.c		ft_strmapi.c\
		ft_strncat.c		ft_strncmp.c  	ft_strncpy.c		ft_strnequ.c	ft_strnew.c\
		ft_strnstr.c		ft_strrchr.c  	ft_strsplit.c		ft_strstr.c		ft_strsub.c\
		ft_strtrim.c		ft_tolower.c  	ft_toupper.c		ft_min.c		ft_max.c\
		ft_itoa_base.c		ft_isblank.c  	ft_chrrep.c			ft_strrev.c		ft_rot13.c\
		ft_putnbr_base.c	ft_printmem.c	ft_nbrlen.c			ft_realloc.c	ft_arraydel.c\
		ft_abs.c			ft_strndup.c  	ft_itoa_base64.c	ft_strlowcase.c	ft_strupcase.c\
		ft_strcmpcase.c		ft_seekstr.c
OBJS := $(subst .c,.o,$(subst 	, ,$(SRCS)))
vpath %.o objs

help:
	@echo "\033[41mAvailable rules:\033[49m"
	@echo "\033[43m"
	@echo "help"
	@echo "all"
	@echo "clean"
	@echo "fclean"
	@echo "re"
	@echo "\033[49m"

%.o:
	@cd objs;\
	$(CC) $(CFLAGS) -I ../includes -I ../includes/printf -c ../srcs/$(subst .o,.c,$@)

$(NAME): printf $(OBJS)
	@cd objs;\
	ar -r ../$@ $(OBJS)

printf:
	@cd objs;\
	$(CC) $(CFLAGS) -I ../includes -I ../includes/printf -c $(addprefix ../srcs/printf/,ft_print.c display.c extras.c utilities.c)

all: $(NAME) printf

clean:
	@cd objs;\
	rm -f $(OBJS);\
	make -C libft clean

fclean: clean
	rm -f $(NAME);\
	make -C srcs/libft fclean

re: fclean all

.PHONY: help all nolibft clean fclean re
