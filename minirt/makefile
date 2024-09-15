# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 18:54:01 by yeojukim          #+#    #+#              #
#    Updated: 2024/09/10 18:54:01 by yeojukim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

SRCS = \
	free1.c error.c get_next_line_utils.c get_next_line.c init.c libft_util1.c \
	libft_util2.c libft_util3.c libft_util4.c parse_util1.c parse_util2.c \
	parse.c set1.c set2.c control1.c vec_util1.c vec_util2.c\
	main.c

OBJS = $(SRCS:.c=.o)

AR = ar rcs
RM = rm -rf
CC = gcc
FW = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -lbsd

FLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux/

all : makelibs
	$(MAKE) $(NAME)

bonus : makelibs
	$(MAKE) $(NAME)

makelibs :
	$(MAKE) -C $(MLX_DIR)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ $(FW) -o $@

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean :
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(MLX_DIR)libmlx.a
	$(RM) $(MLX_DIR)libmlx_Linux.a

re : fclean all

.PHONY : all clean fclean re bonus
