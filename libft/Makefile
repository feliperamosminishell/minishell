# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/29 17:12:20 by juan-her          #+#    #+#              #
#    Updated: 2026/02/04 01:32:18 by goramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
NAME = libft.a
SOURCE = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_strlen.c \
			ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
			ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c \
			ft_strnstr.c ft_strrchr.c ft_toupper.c ft_tolower.c ft_substr.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_isspace.c
SOURCEBONUS = ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
				ft_lstadd_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
				ft_multifree.c 
OBJ = $(SOURCE:.c=.o)
OBJBONUS = $(SOURCEBONUS:.c=.o)
INCLUDE = libft.h
RM = rm -f

all: $(NAME)

clean:
	@$(RM) $(OBJ) $(OBJBONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(OBJBONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJBONUS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

.DEFAULT_GOAL= all
