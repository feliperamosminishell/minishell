# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/24 22:53:20 by juan-her          #+#    #+#              #
#    Updated: 2026/01/28 19:53:22 by juan-her         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = minishell
SRCLIBFT = ./libft
LIBFT = $(SRCLIBFT)/libft.a
SRC = main.c loop.c init.c
OBJ_URL = ./obj
OBJ = $(SRC:%.c=$(OBJ_URL)/%.o)
INCLUDE = -I$(SRCLIBFT)
LIBS = -lreadline
RM = rm -rf

all: $(LIBFT) $(NAME)
	@echo "MINISHELL DONE"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L $(SRCLIBFT) -lft -o $(NAME) -lreadline
	@echo "FINISH MINISHELL"

$(LIBFT):
	@$(MAKE) -C $(SRCLIBFT)

$(OBJ_URL):
	@mkdir -p $(OBJ_URL)

$(OBJ_URL)/%.o: %.c | $(OBJ_URL)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(MAKE) -C $(SRCLIBFT) clean
	@$(RM) $(OBJ_URL)
	@echo "Objects deleted."

fclean: clean
	@$(MAKE) -C $(SRCLIBFT) fclean
	@$(RM) $(NAME)
	@echo "Objects deleted."

re: fclean all
	@echo "Has been updated"

.PHONY: all clean fclean re