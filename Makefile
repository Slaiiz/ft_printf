CC        =	gcc
CFLAGS    =	-Wall -Wextra -Werror
NAME      =	libftprintf.a
SRCS      =	ft_atoi.c			ft_bzero.c		ft_isalnum.c		ft_isalpha.c	ft_isascii.c\
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
			ft_strcmpcase.c		ft_seekstr.c	ft_expect.c			ft_wstrlen.c	ft_uitoa.c\
			ft_uitoa64.c		ft_uitoa_base.c	ft_uitoa_base64.c
SRCSOBJ  := $(subst .c,.o,$(SRCS:	= ))
PRINTF    =	main.c				extras.c		display.c			utilities.c
PRINTFOBJ:= $(subst .c,.o,$(PRINTF:	= ))
vpath %.o objs

help:
	@echo "\033[33;41mAvailable rules:\033[0m\n\
	\033[30;43mhelp     \033[0m\n\
	\033[30;43mall      \033[0m\n\
	\033[30;43mclean    \033[0m\n\
	\033[30;43mfclean   \033[0m\n\
	\033[30;43mre       \033[0m\n\
	\033[30;43mrenolibft\033[0m\n"

all: ft_printf.o $(NAME)

$(NAME): $(SRCSOBJ)
	cd objs;\
	ar -r ../$@ $(SRCSOBJ) ft_printf.o

ft_printf.o:
	cd srcs/printf;\
	$(CC) $(CFLAGS) -I ../../includes -I ../../includes/printf -c $(PRINTF);\
	mv $(PRINTFOBJ) ../../objs;\
	cd ../../objs;\
	ld -r -o ft_printf.o $(PRINTFOBJ);\

clean:
	cd objs;\
	rm -f $(SRCSOBJ) $(PRINTFOBJ) ft_printf.o;\

fclean: clean
	rm -f $(NAME)

renolibft:
	cd objs;\
	rm -f $(PRINTFOBJ) ft_printf.o;
	make ft_printf.o;\
	cd objs;\
	ar -r ../$(NAME) ft_printf.o

re: fclean all

%.o:
	@cd srcs;\
	echo "Compiling $@";\
	$(CC) $(CFLAGS) -I ../includes -I ../includes/printf -c $(subst .o,.c,$@);\
	mv $@ ../objs

.PHONY: help all nolibft clean fclean re
