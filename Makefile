# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/24 22:53:20 by juan-her          #+#    #+#              #
#    Updated: 2026/02/03 01:02:34 by goramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = minishell
SRCLIBFT = ./libft
LIBFT = $(SRCLIBFT)/libft.a
SRC = main.c loop.c expand.c lexer.c check_str.c src/builtins/builtin_echo.c src/builtins/builtin_pwd.c
OBJ = obj/main.o obj/loop.o obj/expand.o obj/lexer.o obj/check_str.o obj/builtin_echo.o obj/builtin_pwd.o
INCLUDE = -I$(SRCLIBFT)
LIBS = -lreadline
RM = rm -rf

VPATH = . src/builtins

all: $(LIBFT) $(NAME)
	@echo "MINISHELL DONE"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L $(SRCLIBFT) -lft -o $(NAME) -lreadline
	@echo "FINISH MINISHELL"

$(LIBFT):
	@$(MAKE) -C $(SRCLIBFT)

obj:
	@mkdir -p obj

obj/%.o: %.c | obj
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(MAKE) -C $(SRCLIBFT) clean
	@$(RM) obj
	@echo "Objects deleted."

fclean: clean
	@$(MAKE) -C $(SRCLIBFT) fclean
	@$(RM) $(NAME)
	@echo "Objects deleted."

re: fclean all
	@echo "Has been updated"

.PHONY: all clean fclean re
