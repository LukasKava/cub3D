# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabbas <mabbas@students.42wolfsburg.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:35:38 by lkavalia          #+#    #+#              #
#    Updated: 2023/05/05 19:30:53 by mabbas           ###   ########.fr        #
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
		./SRC/drawing2d_map.c 			\
		./SRC/brezenham.c				\
		./SRC/raycasting.c				\
		./SRC/raycasting2.c				\
		./SRC/raycasting_utils.c        \
		./SRC/draw3d.c

OBJS = $(SRCS:.c=.o)


LIBFT = ./libs/libft/

SUBM_STATE := $(shell find libs/libft -type f)

all: $(SUBM_FLAG) libft $(NAME)

UNAME := $(shell uname)

ifeq ($(SUBM_STATE),)
SUBM_FLAG	= submodule
endif

%.o: %.c
	@echo "\033[0;35m.\033[0m\c"
	@$(CC) $(CFLAGS) -Imlx -I/opt/X11/include -c $< -o $@

minilibx-linux/libmlx.a:
	@make -C minilibx-linux
	@cp MLX/libmlx.a
	@echo "Making MLX..."

libft:
	@$(MAKE) -C $(LIBFT) 


ifeq ($(UNAME), Darwin)
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LIBFT)libft.a -lmlx -framework OpenGL -framework AppKit -o $(NAME)
endif

ifeq ($(UNAME), Linux)
$(NAME): minilibx-linux/libmlx.a $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LIBFT)libft.a minilibx-linux/libmlx.a -L/usr/include/X11/extensions -lX11 -lXext -lm -o $(NAME)
endif

submodule:
	@git submodule foreach git pull origin main
	@git submodule update --init
	

clean:
	@$(MAKE) -C $(LIBFT) clean
	@rm -f $(OBJS)
	@echo "\nUninstalling..."

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)
	@echo "\nUninstalled"

re: fclean all
	@echo "\nInstalling....."
	@echo "\nInstalled"

.PHONY: all clean fclean re libft submodule