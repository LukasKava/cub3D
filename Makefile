# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:35:38 by lkavalia          #+#    #+#              #
#    Updated: 2023/05/06 21:23:23 by lkavalia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

SRCS =	./SRC/main.c 					\
		./SRC/parsing/map.c				\
		./SRC/parsing/errors.c 			\
		./SRC/parsing/parsing.c			\
		./SRC/parsing/checking_map.c 	\
		./SRC/parsing/errors_utils.c	\
		./SRC/parsing/texure_handling.c \
		./SRC/parsing/utils.c			\
		./SRC/init.c					\
		./SRC/free.c					\
		./SRC/colors.c					\
		./SRC/player.c 					\
		./SRC/brezenham.c				\
		./SRC/raycasting.c				\
		./SRC/raycasting2.c				\
		./SRC/raycasting_utils.c        \
		./SRC/utils.c 					\
		./SRC/draw3d.c

OBJS = $(SRCS:.c=.o)


LIBFT = ./libs/libft/

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	MLX = ./minilibx-mac
else
	MLX = ./minilibx-linux
endif

ifeq ($(UNAME), Darwin)
	LFLAGS = -L$(MLX) -lmlx -framework OpenGL -framework AppKit 
else
	LFLAGS = -L$(MLX) -lmlx -L/usr/include/X11/extensions -lX11 -lXext -lm
endif

all: libft $(NAME)

%.o: %.c
	@echo "\033[0;35m.\033[0m\c"
	@$(CC) $(CFLAGS) -Imlx -I/opt/X11/include -c $< -o $@

minilibx-linux/libmlx.a:
	@make -C minilibx-linux
	@echo "Making MLX..."

minilibx-mac/libmlx.a:
	@make -C minilibx-mac
	@echo "Making MLX..."


libft:
	@$(MAKE) -C $(LIBFT) 


$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LIBFT)libft.a $(LFLAGS) -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C  $(MLX) clean
	@rm -f $(OBJS)
	@echo "\nUninstalling..."

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)
	@echo "\nUninstalled"

re: fclean all
	@echo "\nInstalling....."
	@echo "\nInstalled"

.PHONY: all clean fclean re libft