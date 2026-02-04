# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/24 22:53:20 by juan-her          #+#    #+#              #
#    Updated: 2026/02/04 16:40:41 by goramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
LIBFT_DIR	= libft

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft -lreadline

# Archivos fuente - Main
MAIN_SRCS	= main.c \
				loop.c

# Archivos fuente - Parsing
PARSING_SRCS = lexer.c \
				expand.c \
				check_str.c

# Archivos fuente - Builtins
BUILTINS_SRCS = builtin_echo.c \
				builtin_pwd.c \
				builtin_env.c

# Archivos fuente - Utils
UTILS_SRCS	= env_utils.c \
				ft_freelist.c \
				utils.c

# Construcción de rutas completas
SRCS		= $(addprefix $(SRC_DIR)/, $(MAIN_SRCS)) \
				$(addprefix $(SRC_DIR)/parsing/, $(PARSING_SRCS)) \
				$(addprefix $(SRC_DIR)/builtins/, $(BUILTINS_SRCS)) \
				$(addprefix $(SRC_DIR)/utils/, $(UTILS_SRCS))

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
