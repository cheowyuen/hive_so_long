# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 07:57:47 by cwong             #+#    #+#              #
#    Updated: 2025/06/17 11:35:17 by cwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc

CFLAGS	:= -Wall -Wextra -Werror

NAME	:= so_long

SRCS	:= so_long.c handle_file_open.c process_buffer.c fill_and_validate_map.c \
		   process_map_lines.c init_and_run_game.c render_game.c my_keyhook.c \
		   set_null.c

OBJS	:= $(SRCS:.c=.o)

HEADER  := so_long.h

LIBFT_PATH	:= ./libft
LIBFT		:= $(LIBFT_PATH)/libft.a

MLX42_PATH	:= ./MLX42
MLX42		:= $(MLX42_PATH)/build/libmlx42.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX42) -ldl -lglfw -lm

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX42):
	cmake -S $(MLX42_PATH) -B $(MLX42_PATH)/build
	cmake --build $(MLX42_PATH)/build

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -f $(OBJS)
	rm -rf $(MLX42_PATH)/build

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
