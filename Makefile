# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 19:31:14 by myener            #+#    #+#              #
#    Updated: 2020/03/09 15:49:24 by tferrieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

SRCDIR	:=	./srcs
OBJDIR	:=	./objs

SRCS_NAME =	adj_matrix.c \
			dir_gaps.c \
			free_tools.c \
			output.c \
			queue_tools.c \
			allpath.c \
			dir_matrix.c \
			init_tools.c \
			parser.c \
			troubleshooter.c \
			ant_tools.c \
			dispatcher.c \
			main.c \
			path_tools.c \
			branch_tools.c \
			elist_tools.c \
			matrix_tools.c \
			pathfinder.c

FLAGS =	 -Wall -Wextra -Werror -I srcs/libft

OBJS	:=	$(addprefix $(OBJDIR)/,$(SRCS_NAME:.c=.o))
SRCS	:=	$(addprefix $(SRCDIR)/,$(SRCS_NAME))

LIBFT = srcs/libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) srcs/includes/lem_in.h
	@printf "\e[36m Creating: \e[32m$(NAME)\n"
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