# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 16:52:41 by fhuang            #+#    #+#              #
#    Updated: 2018/02/10 18:26:50 by fhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Editable =====
LIBDIR	:=	lib/
NAME	:=	$(addprefix $(LIBDIR), libft.a)
# ====================

# ===== Standard =====
CC		:=	clang -pipe
CFLAGS	:=	-Wall -Wextra -Werror -g3
SRCDIR	:=	src/
OBJDIR	:=	obj/
INCDIR	:=	include/
PRINTFDIR	:=	ft_printf/
SRC		:=	btree_apply_infix.c		\
			btree_apply_prefix.c	\
			btree_apply_suffix.c	\
			btree_create_node.c		\
			btree_insert_data.c		\
			btree_level_count.c		\
			btree_search_data.c		\
			ft_abs.c				\
			ft_atoi.c				\
			ft_atoi_base.c			\
			ft_atol.c				\
			ft_bzero.c				\
			ft_count_words.c		\
			ft_dynam_append.c		\
			ft_dynam_destroy.c		\
			ft_dynam_new.c			\
			ft_dynam_trim.c			\
			ft_exit.c				\
			ft_intabndup.c			\
			ft_isacharinstring.c	\
			ft_isalnum.c			\
			ft_isalpha.c			\
			ft_isascii.c			\
			ft_isdigit.c			\
			ft_isint.c				\
			ft_isprint.c			\
			ft_isspace.c			\
			ft_isstrdigit.c			\
			ft_isstrempty.c			\
			ft_iswhitespace.c		\
			ft_itoa.c				\
			ft_itoa_base.c			\
			ft_lstadd.c				\
			ft_lstaddend.c			\
			ft_lstdel.c				\
			ft_lstdelone.c			\
			ft_lstiter.c			\
			ft_lstlen.c				\
			ft_lstmap.c				\
			ft_lstnew.c				\
			ft_memalloc.c			\
			ft_memccpy.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_memcpy.c				\
			ft_memdel.c				\
			ft_memdup.c				\
			ft_memmove.c			\
			ft_memset.c				\
			ft_nbrlen.c				\
			ft_nbrlen_base.c		\
			ft_power_pos.c			\
			ft_putchar.c			\
			ft_putchar_fd.c			\
			ft_putendl.c			\
			ft_putendl_fd.c			\
			ft_putendlcol.c			\
			ft_putnbr.c				\
			ft_putnbr_fd.c			\
			ft_putnbrendl.c			\
			ft_putstr.c				\
			ft_putstr_fd.c			\
			ft_putstrcol.c			\
			ft_str3cat.c			\
			ft_strcat.c				\
			ft_strchange.c			\
			ft_strchr.c				\
			ft_strclr.c				\
			ft_strcmp.c				\
			ft_strcpy.c				\
			ft_strdel.c				\
			ft_strdelchar.c			\
			ft_strdup.c				\
			ft_strequ.c				\
			ft_strequ_case.c		\
			ft_strinsert.c			\
			ft_striter.c			\
			ft_striteri.c			\
			ft_strjoin.c			\
			ft_strjoin_free.c		\
			ft_str3join.c		\
			ft_strlcat.c			\
			ft_strlen.c				\
			ft_strmap.c				\
			ft_strmapi.c			\
			ft_strncat.c			\
			ft_strncmp.c			\
			ft_strncpy.c			\
			ft_strndup.c			\
			ft_strnequ.c			\
			ft_strnew.c				\
			ft_strnstr.c			\
			ft_strrchr.c			\
			ft_strreplace.c			\
			ft_strsplit.c			\
			ft_strfind_c.c			\
			ft_strstr.c				\
			ft_strsub.c				\
			ft_strtrim.c			\
			ft_strupper.c			\
			ft_tabatoi.c			\
			ft_tabfree.c			\
			ft_tablen.c				\
			ft_tabndup.c			\
			ft_tabprint.c			\
			ft_tolower.c			\
			ft_toupper.c			\
			ft_trim_c.c				\
			ft_wcslen.c				\
			get_distance.c			\
			get_next_line.c			\
			read_stdin.c
OBJ		:=	$(SRC:%.c=$(OBJDIR)%.o)
INC		:=	-I./$(INCDIR)
CACHEF	:=	.cache_exists
# ====================

# ====== Colors ======
CLEAR		= "\033[2K"
UP			= "\033[A"
EOC			= "\033[0;0m"
BLACK		= "\033[0;30m"
GREY		= "\033[1;30m"
RED			= "\033[0;31m"
GREEN		= "\033[0;32m"
YELLOW		= "\033[0;33m"
BLUE		= "\033[0;34m"
PURPLE		= "\033[0;35m"
CYAN		= "\033[0;36m"
WHITE		= "\033[0;37m"
B_WHITE		= "\033[1;37m"
# ====================

EXEC			:= $(addprefix $(LIBDIR), $(NAME))
CACHEF			:=	.cache_exists

.PHONY: clean fclean re all ft_printf

all: ft_printf $(NAME)

$(NAME): $(OBJ)
	@echo $(B_WHITE)" → libft"$(EOC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(CACHEF)
	@$(CC) $(CFLAGS) -c  $< -o $@ $(INC)
	@printf $(B_WHITE)"•"$(EOC)

$(CACHEF):
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@test -d $(LIBDIR) || mkdir $(LIBDIR)
	@test -d $(CACHEF) || touch $(CACHEF)

ft_printf:
	@make -C $(PRINTFDIR)

clean:
	@rm -rf $(OBJDIR) $(CACHEF)
	@make clean -C $(PRINTFDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(PRINTFDIR)

re: fclean all
