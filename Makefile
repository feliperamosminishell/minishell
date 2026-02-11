# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/24 22:53:20 by juan-her          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2026/02/08 06:12:15 by juan-her         ###   ########.fr        #
=======
#    Updated: 2026/02/04 16:40:41 by goramos-         ###   ########.fr        #
>>>>>>> main
#                                                                              #
# **************************************************************************** #

NAME		= minishell
<<<<<<< HEAD
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

# Archivos fuente - Expand
EXPAND_SRCS = expand.c \

# Archivos fuente - Lexer
LEXER_SRCS = check_str.c \
				check_str2.c \
				lexer.c

# Archivos fuente - Parsing
PARSING_SRCS = add_cnt.c \
				parse.c
=======

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
>>>>>>> main

# Archivos fuente - Builtins
BUILTINS_SRCS = builtin_echo.c \
				builtin_pwd.c \
				builtin_env.c

# Archivos fuente - Utils
UTILS_SRCS	= env_utils.c \
<<<<<<< HEAD
				free_nodes.c \
				new_nodes.c
=======
				ft_freelist.c \
				utils.c
>>>>>>> main

# Construcción de rutas completas
SRCS		= $(addprefix $(SRC_DIR)/, $(MAIN_SRCS)) \
				$(addprefix $(SRC_DIR)/parsing/, $(PARSING_SRCS)) \
				$(addprefix $(SRC_DIR)/builtins/, $(BUILTINS_SRCS)) \
<<<<<<< HEAD
				$(addprefix $(SRC_DIR)/utils/, $(UTILS_SRCS)) \
				$(addprefix $(SRC_DIR)/expand/, $(EXPAND_SRCS)) \
				$(addprefix $(SRC_DIR)/lexer/, $(LEXER_SRCS))
=======
				$(addprefix $(SRC_DIR)/utils/, $(UTILS_SRCS))
>>>>>>> main

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