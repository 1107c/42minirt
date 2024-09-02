# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 11:30:30 by ksuh              #+#    #+#              #
#    Updated: 2024/09/01 14:34:29 by ksuh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = close.c error.c init.c key_handle.c main.c draw.c

OBJS= $(SRCS:.c=.o)

INCS = -Lminilibx-linux -Iminilibx-linux -lmlx -lXext -lX11 -lm

MLX = libmlx_Linux.a
MLX_PATH = ./minilibx-linux

LIB_DIR = ./libft
LIB = ${LIB_DIR}/libft.a

NAME = miniRT

all : $(NAME) 

$(NAME) : $(OBJS) $(LIB) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(INCS) -o $(NAME)

%.o : %.c 
	$(CC) $(CFLAGS) -c $^

$(MLX) :
	make -C $(MLX_PATH)

$(LIB) :
	make -C $(LIB_DIR)

clean :	
	make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean : 
	make fclean -C $(LIB_DIR)
	make clean -C $(MLX_PATH)
	rm -rf $(OBJS)
	rm -rf $(NAME)

re : fclean all

bonus : all

.PHONY : all clean fclean re bonus

