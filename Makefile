# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/24 22:53:20 by juan-her          #+#    #+#              #
#    Updated: 2026/02/04 01:31:51 by goramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)
LIBS = -lreadline
LDFLAGS = -L$(LIBFT_DIR) -lft

GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

# Archivos fuente - Main
MAIN_SRCS = main.c \
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
UTILS_SRCS = env_utils.c \
			ft_freelist.c

# Construcción de rutas completas
SRCS = $(addprefix $(SRC_DIR)/, $(MAIN_SRCS)) \
		$(addprefix $(SRC_DIR)/parsing/, $(PARSING_SRCS)) \
		$(addprefix $(SRC_DIR)/builtins/, $(BUILTINS_SRCS)) \
		$(addprefix $(SRC_DIR)/utils/, $(UTILS_SRCS))

# Objetos
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regla principal
all: $(NAME)

# Compilar libft
$(LIBFT):
	@echo "$(YELLOW)📚 Compilando libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ Libft compilado$(NC)"

# Crear directorios de objetos y compilar
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔨 Compilando $<$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Linkear todo
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)🔗 Linkeando $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ MINISHELL COMPILADO!$(NC)"

# Limpiar objetos
clean:
	@echo "$(RED)🧹 Limpiando objetos...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR)

# Limpiar todo
fclean: clean
	@echo "$(RED)🗑️  Eliminando ejecutable...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)

# Recompilar todo
re: fclean all

# Norminette
norm:
	@echo "$(YELLOW)📏 Ejecutando norminette...$(NC)"
	@norminette $(SRC_DIR) $(INC_DIR) || true

.PHONY: all clean fclean re norm
