# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubusque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/10 14:01:23 by gubusque          #+#    #+#              #
#    Updated: 2025/09/18 19:41:37 by gubusque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC_DIR = src
LIBFT_DIR = libft
OBJ_DIR = obj
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/childs.c
LIBFT_SRCS = $(LIBFT_DIR)/ft_bzero.c \
             $(LIBFT_DIR)/ft_calloc.c \
             $(LIBFT_DIR)/ft_memcpy.c \
             $(LIBFT_DIR)/ft_split.c \
             $(LIBFT_DIR)/ft_strjoin.c \
             $(LIBFT_DIR)/ft_strdup.c \
             $(LIBFT_DIR)/ft_strlen.c \
             $(LIBFT_DIR)/ft_substr.c \
	    	 $(LIBFT_DIR)/ft_strncmp.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/src_%.o)
LIBFT_OBJS = $(LIBFT_SRCS:$(LIBFT_DIR)/%.c=$(OBJ_DIR)/libft_%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	$(CC) $(OBJS) $(LIBFT_OBJS) -o $(NAME)

$(OBJ_DIR)/src_%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/libft_%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
