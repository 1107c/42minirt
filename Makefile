# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 11:30:30 by ksuh              #+#    #+#              #
#    Updated: 2024/07/04 13:22:23 by ksuh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = close.c error.c init.c main.c

OBJS= $(SRCS:.c=.o)

INCS = -Lminilibx-linux -Iminilibx-linux -lmlx -lXext -lX11 -lm

MLX = libmlx_Linux.a
MLX_PATH = ./minilibx-linux

LIB_DIR = ./libft
LIB = libft.a

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
	cp $(LIB_DIR)/$(LIB) $(LIB)

clean :	
	make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean : 
	make fclean -C $(LIB_DIR)
	make clean -C $(MLX_PATH)
	rm -rf $(OBJS)
	rm -rf $(NAME)
	rm -rf $(LIB)

re : fclean all

bonus : all

.PHONY : all clean fclean re bonus

