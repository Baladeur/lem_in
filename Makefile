# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 19:31:14 by myener            #+#    #+#              #
#    Updated: 2020/06/02 18:42:34 by tferrieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCDIR	:=	./srcs
OBJDIR	:=	./objs

SRCS_NAME =	dispatcher.c \
			elist_tools.c \
			free_tools.c \
			init_tools.c \
			lem_in_tools.c \
			main.c \
			matrix_tools.c \
			parser.c \
			overlap_handler.c \
			suurballe.c \
			path_tools.c \
			queue_tools.c \
			troubleshooter.c

FLAGS =	 -Wall -Wextra -Werror -I srcs/libft

OBJS	:=	$(addprefix $(OBJDIR)/,$(SRCS_NAME:.c=.o))
SRCS	:=	$(addprefix $(SRCDIR)/,$(SRCS_NAME))

LIBFT = srcs/libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) srcs/includes/lem_in.h
	@printf "\e[36m Creating: \e[32m$(NAME)\e[0m\n"
	@gcc $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C srcs/libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[34m Compiling: \e[0m$< -> $@\n"
	@mkdir -p $(dir $@)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@printf "\e[34m Cleaning lem_in:	\e[0m$(OBJDIR)\e[0m\n"
	@rm -f $(OBJ) $@
	@rm -rf $(OBJDIR)
	@make clean -C srcs/libft

fclean: clean
	@printf "\e[36m Removing: \e[0m"
	@printf "\e[32mlem_in \e[0m\n"
	@rm -f $(NAME) $@
	@rm -rf srcs/libft/libft.a

re: fclean all

.PHONY: all, clean, fclean, re