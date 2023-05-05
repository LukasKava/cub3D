# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:35:38 by lkavalia          #+#    #+#              #
#    Updated: 2023/05/05 15:46:01 by lkavalia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d 

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

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

UNAME := $(shell uname)
%.o: %.c
	$(CC) $(CFLAGS) -Imlx -I/opt/X11/include -c $< -o $@
minilibx-linux/libmlx.a:
	make -C minilibx-linux
	cp MLX/libmlx.a
	@echo "Making MLX..."

ifeq ($(UNAME), Darwin)
$(NAME): libftprintf/libftprintf.a $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit ./libftprintf/libftprintf.a -o $(NAME)
endif

ifeq ($(UNAME), Linux)
$(NAME): /libftprintf/libftprintf.a minilibx-linux/libmlx.a $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) minilibx-linux/libmlx.a -L/usr/include/X11/extensions -lX11 -lXext -lm -o $(NAME)
endif

libftprintf/libftprintf.a:
	@make -C libftprintf
#mv libftprintf/libftprintf.a .
	@echo "Making libftprintf..."

clean:
	@make -C libftprintf clean
#rm libftprintf.a
	@rm -f $(OBJS)
	@echo "cleaning..."

fclean: clean
	@make -C libftprintf fclean
	@rm -f $(NAME)
	@echo "fully cleaning..."

re: fclean all
	@echo "remaking files..."

.PHONY: all clean fclean re