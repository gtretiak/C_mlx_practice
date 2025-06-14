# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/26 12:13:42 by gtretiak          #+#    #+#              #
#    Updated: 2025/06/14 19:23:53 by gtretiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = demo
HEADER = mlx_graphics_demo.h
MLX_DIR = minilibx-linux/
MLX = libmlx_Linux.a
SRCS_DIR = ./
SRCS = mlx_graphics_demo.c
OBJS = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))
CFLAGS = -Wall -Wextra -Werror
MLX_FEATURES = -lX11 -lXext -lXrender -lXrandr -lm -lpthread

all: $(MLX) $(NAME)

$(MLX):
	@make -C $(MLX_DIR)

%.o: %.c $(HEADER) $(MLX_DIR)$(MLX)
	cc $(CFLAGS) -I. -I$(MLX_DIR) -c $< -o $@ 
	
$(NAME): $(MLX) $(OBJS)
	@if [ ! -f $(NAME) ]; then \
		cc $(OBJS) $(MLX_DIR)$(MLX) $(MLX_FEATURES) -o $(NAME); fi

.PHONY: clean fclean re

clean:
	rm -f $(OBJS)
	@make clean -C $(MLX_DIR) || true

fclean: clean
	rm -f $(NAME)

re: fclean all
