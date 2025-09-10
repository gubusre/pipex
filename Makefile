# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubusque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/10 14:01:23 by gubusque          #+#    #+#              #
#    Updated: 2025/09/10 14:19:46 by gubusque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME = pipex

# Compilador y banderas
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

# Directorios
SRC_DIR = src
LIBFT_DIR = libft
OBJ_DIR = obj
INCLUDE_DIR = include

# Archivos fuente
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c
LIBFT_SRCS = $(LIBFT_DIR)/ft_bzero.c \
             $(LIBFT_DIR)/ft_calloc.c \
             $(LIBFT_DIR)/ft_memcpy.c \
             $(LIBFT_DIR)/ft_split.c \
             $(LIBFT_DIR)/ft_strjoin.c \
             $(LIBFT_DIR)/ft_strdup.c \
             $(LIBFT_DIR)/ft_strlen.c \
             $(LIBFT_DIR)/ft_substr.c \
	    	 $(LIBFT_DIR)/ft_strncmp.c

# Archivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT_OBJS = $(LIBFT_SRCS:$(LIBFT_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regla principal
all: $(NAME)

# Compilar el ejecutable
$(NAME): $(OBJS) $(LIBFT_OBJS)
	$(CC) $(OBJS) $(LIBFT_OBJS) -o $(NAME)

# Compilar archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos objeto
clean:
	rm -rf $(OBJ_DIR)

# Limpiar todo (incluido el ejecutable)
fclean: clean
	rm -f $(NAME)

# Recompilar desde cero
re: fclean all

.PHONY: all clean fclean re
