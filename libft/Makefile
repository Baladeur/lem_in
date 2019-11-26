# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myener <myener@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 17:52:34 by myener            #+#    #+#              #
#    Updated: 2019/11/26 18:57:46 by myener           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

NAME	=	libft.a

SRCDIR	:=	./
OBJDIR	:=	./objs

SRCS	=	ft_abs.c 						\
			ft_atoi.c 						\
			ft_atoll.c 						\
			ft_baselen.c 					\
			ft_bzero.c 						\
			ft_floatmod.c 					\
			ft_free_join.c 					\
			ft_hexlen.c 					\
			ft_intlen.c 					\
			ft_isalpha.c 					\
			ft_isdigit.c 					\
			ft_isalnum.c 					\
			ft_isascii.c 					\
			ft_isprint.c 					\
			ft_isblank.c 					\
			ft_itoa.c						\
			ft_itoa_base.c					\
			ft_itoc.c						\
			ft_linelen.c					\
			ft_lltoa.c						\
			ft_lstnew.c 					\
			ft_lstdelone.c 					\
			ft_lstdel.c 					\
			ft_lstadd.c 					\
			ft_lstiter.c 					\
			ft_lstmap.c						\
			ft_memmove.c 					\
			ft_memcpy.c 					\
			ft_memset.c 					\
			ft_memchr.c 					\
			ft_memalloc.c 					\
			ft_memccpy.c 					\
			ft_memcmp.c 					\
			ft_memdel.c 					\
			ft_octlen.c 					\
			ft_putendl.c 					\
			ft_putchar.c 					\
			ft_putstr.c 					\
			ft_putchar_fd.c 				\
			ft_putendl_fd.c 				\
			ft_putnbr.c 					\
			ft_putnbr_fd.c 					\
			ft_putnbr_base.c				\
			ft_putunbr_base.c 				\
			ft_putstr_fd.c 					\
			ft_putnbr_long.c 				\
			ft_putunbr_long.c 				\
			ft_strchr.c						\
			ft_strnew.c 					\
			ft_strrchr.c 					\
			ft_strdup.c 					\
		   	ft_strcat.c 					\
			ft_strcpy.c 					\
	 		ft_strncat.c 					\
			ft_strncpy.c 					\
			ft_strcmp.c 					\
			ft_strlen.c 					\
			ft_strncmp.c 					\
			ft_strlcat.c 					\
			ft_strdel.c 					\
			ft_strclr.c 					\
			ft_striter.c 					\
			ft_striteri.c 					\
			ft_strmap.c 					\
			ft_strmapi.c 					\
			ft_strequ.c 					\
			ft_strnequ.c 					\
			ft_strstr.c 					\
			ft_strnstr.c 					\
			ft_strsub.c 					\
			ft_strjoin.c 					\
			ft_strtrim.c 					\
			ft_strsplit.c 					\
			ft_toupper.c 					\
			ft_tolower.c 					\
			ft_strndup.c 					\
			ft_strnlen.c 					\
			ft_uintlen.c 					\
			get_next_line.c 				\
			tab_free.c		 				\
			rounder.c 						\
			ft_printf/cleaner.c 			\
			ft_printf/dispatcher.c 			\
			ft_printf/finalizer.c 			\
			ft_printf/float_tools.c 		\
			ft_printf/ft_printf.c 			\
			ft_printf/parser.c 				\
			ft_printf/parser_helper.c 		\
			ft_printf/printer.c 			\
			ft_printf/typeis_int.c 			\
			ft_printf/typeis_char.c 		\
			ft_printf/typeis_unsign.c 		\
			ft_printf/typeis_str.c 			\
			ft_printf/typeis_ptr.c 			\
			ft_printf/typeis_octal.c 		\
			ft_printf/typeis_hexl.c 		\
			ft_printf/typeis_hexu.c 		\
			ft_printf/typeis_perc.c 		\
			ft_printf/typeis_float.c


OBJS	:=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS	:=	$(addprefix $(SRCDIR)/,$(SRCS))

CFLAGS	=	-Wall -Werror -Wextra -I ./ -I ft_printf

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\e[36m Creating: \e[32m$(NAME)\n"
	@ar -rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[34m Compiling: \e[0m$< -> $@\n"
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) -c $< -o $@

clean :
	@printf "\e[34m Cleaning libft:	\e[0m$(OBJDIR)\e[0m\n"
	@rm -rf $(OBJDIR)

fclean : clean
	@printf "\e[36m Removing: \e[32m$(NAME)\e[0m\n"
	@rm -rf $(NAME)

re : fclean all
