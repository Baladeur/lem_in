# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myener <myener@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 19:31:14 by myener            #+#    #+#              #
#    Updated: 2019/11/20 19:33:09 by myener           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

SRCDIR	:=	./
OBJDIR	:=	./objs

SRCS_NAME =

FLAGS =	 -Wall -Wextra -Werror -I libft

OBJS	:=	$(addprefix $(OBJDIR)/,$(SRCS_NAME:.c=.o))

SRCS	:=	$(addprefix $(SRCDIR)/,$(SRCS_NAME))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) lem_in.h
	@printf "\e[36m Creating: \e[32m$(NAME)\n"
	@gcc $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[34m Compiling: \e[0m$< -> $@\n"
	@mkdir -p $(dir $@)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@printf "\e[34m Cleaning lem_in:	\e[0m$(OBJDIR)\e[0m\n"
	@rm -f $(OBJ) $@
	@rm -rf $(OBJDIR)
	@make clean -C libft

fclean: clean
	@printf "\e[36m Removing: \e[0m"
	@printf "\e[32mlem_in \e[0m\n"
	@rm -f $(NAME) $@
	@rm -rf libft/libft.a

re: fclean all

.PHONY: all, clean, fclean, re