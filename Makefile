# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/16 23:26:49 by fhuang            #+#    #+#              #
#    Updated: 2019/03/06 11:22:58 by fhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Editable =====
NAME		:=	ft_ssl
# ====================

# ===== Standard =====
CC			:=	clang -pipe
CFLAGS		:=	-Wall -Wextra -Werror -g3 -fsanitize=address
SRCDIR		:=	src/
OBJDIR		:=	obj/
INCDIR		:=	include/
LIBFT		:=	libft/
LIBDIR		:=	lib/

MD5DIR		:=	md5/
SHADIR		:=	sha/
SHA256DIR	:=	$(SHADIR)sha256/

SRC			:=	main.c									\
				find_command.c							\
				ft_ceil.c								\
				ft_utoa_hex.c							\
				get_commands.c							\
				read_file.c								\
				rotate.c								\
				swap_32.c								\
				$(MD5DIR)md5_do_rounds.c				\
				$(MD5DIR)md5_execute_hash.c				\
				$(MD5DIR)md5_get_shift_amounts.c		\
				$(MD5DIR)md5_get_sinus_constants.c		\
				$(MD5DIR)md5_start.c					\
				$(SHA256DIR)sha256_get_round_constants.c	\
				$(SHA256DIR)sha256_execute_hash.c			\
				$(SHA256DIR)sha256_start.c

OBJ			:=	$(SRC:%.c=$(OBJDIR)%.o)
INC			:=	-I./$(INCDIR) -I./$(LIBFT)$(INCDIR)
LIBPATH		:=	-L./$(LIBFT)$(LIBDIR) -lft
# ====================

# ====== Colors ======
CLEAR		= "\033[2K"
UP			= "\033[A"
EOC			= "\033[0;0m"
BLACK		= "\033[0;30m"
RED			= "\033[0;31m"
GREEN		= "\033[0;32m"
YELLOW		= "\033[0;33m"
BLUE		= "\033[0;34m"
PURPLE		= "\033[0;35m"
CYAN		= "\033[0;36m"
WHITE		= "\033[0;37m"
# ====================

#####

.PHONY: all libft norme clean fclean re

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)$(MD5DIR)
	@mkdir -p $(OBJDIR)$(SHA256DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@printf $(GREEN)"•"$(EOC)

%.c:
	@echo $(RED)"Missing file : $@"$(EOC)

$(NAME): $(OBJ)
	@echo $(GREEN)"\t✓"$(EOC)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBPATH) $(INC)

libft:
	@make -C $(LIBFT)

norme:
	@norminette $(SRCDIR) $(INCDIR) | grep -v Norme -B1 || true
	@norminette $(LIBFT)$(SRCDIR) $(LIBFT)$(INCDIR) | grep -v Norme -B1 || true

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJDIR) $(CACHEF)
	@echo $(YELLOW)"Objects deleted"$(EOC)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo $(YELLOW)"$(NAME) deleted"$(EOC)

re: fclean all
