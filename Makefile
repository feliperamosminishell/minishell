# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/24 22:53:20 by juan-her          #+#    #+#              #
#    Updated: 2026/03/18 16:43:23 by juan-her         ###   ########.fr        #
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

MAIN_SRCS	= main.c \
				loop.c

# Archivos fuente - Expand
EXPAND_SRCS = expand.c \
				expand_quotes.c

# Archivos fuente - Error
ERROR_SRCS = error_handling.c \

# Archivos fuente - Lexer
LEXER_SRCS = check_str.c \
				check_str2.c \
				handle_word.c \
				lexer.c

# Archivos fuente - Parsing
PARSING_SRCS = add_cnt.c \
				add_cnt_2.c \
				parse.c

# Archivos fuente - Builtins
BUILTINS_SRCS = builtin_echo.c \
				builtin_pwd.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_export_no_args.c \
				builtin_export_with_args.c \
				builtin_unset.c \
				builtin_cd.c \
				handler_builtin.c

# Archivos fuente - Utils
UTILS_SRCS	= env_utils.c \
				export_utils.c \
				free_nodes.c \
				new_nodes.c \
				ft_freelist.c \
				utils.c

# Archivos fuente - Executor
REDIR_SRCS	= get_next_line.c \
				set_redir.c

# Archivos fuente - Executor
EXEC_SRCS	= exec.c \
				executor.c
# Archivos fuente - Executor
SIG_SRCS	= signal.c

# Construcción de rutas completas
SRCS		= $(addprefix $(SRC_DIR)/, $(MAIN_SRCS)) \
				$(addprefix $(SRC_DIR)/parsing/, $(PARSING_SRCS)) \
				$(addprefix $(SRC_DIR)/builtins/, $(BUILTINS_SRCS)) \
				$(addprefix $(SRC_DIR)/utils/, $(UTILS_SRCS)) \
				$(addprefix $(SRC_DIR)/expand/, $(EXPAND_SRCS)) \
				$(addprefix $(SRC_DIR)/lexer/, $(LEXER_SRCS)) \
				$(addprefix $(SRC_DIR)/error/, $(ERROR_SRCS)) \
				$(addprefix $(SRC_DIR)/redirection/, $(REDIR_SRCS)) \
				$(addprefix $(SRC_DIR)/executor/, $(EXEC_SRCS)) \
				$(addprefix $(SRC_DIR)/signals/, $(SIG_SRCS))


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
	@echo Minishell done

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
