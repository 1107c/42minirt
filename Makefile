# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 11:30:30 by ksuh              #+#    #+#              #
#    Updated: 2024/09/08 12:52:14 by myeochoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# CFLAGS = -g -Wall -Wextra -Werror

MEN_DIR = ./srcs/
BONUS_DIR	=	./bonus/

PRE_MEN_C = 2d_array_utils.c close.c error.c init.c key_handle.c main.c parse.c \
			parse_element.c parse_figure.c parse_utils.c init_utils.c rt_utils.c \
			draw.c ray.c vector_util.c vector_util2.c intersection.c
PRE_MEN_O = $(PRE_MEN_C:%.c=%.o)

MEN_C	=	$(addprefix $(MEN_DIR),$(PRE_MEN_C))
MEN_O	=	$(addprefix $(MEN_DIR),$(PRE_MEN_O))

PRE_BONUS_C =
PRE_BONUS_O = $(PRE_BONUS_C:%.c=%.o)

BONUS_C	=	$(addprefix $(BONUS_DIR),$(PRE_BONUS_C))
BONUS_O	=	$(addprefix $(BONUS_DIR),$(PRE_BONUS_O))

ifdef WITH_BONUS
	OBJS = $(BONUS_O)
	SRCS = $(BONUS_C)
else
	OBJS = $(MEN_O)
	SRCS = $(MEN_C)
endif

MLX_DIR = ./minilibx-linux/
MLX = libmlx_Linux.a

LIB_DIR = ./libft/
LIB = libft.a

HEADER_DIR	=	./includes/
INCS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm

NAME = miniRT

all : $(NAME)


$(NAME): $(OBJS) $(LIB) $(MLX_DIR)$(MLX)
	cp $(LIB_DIR)/$(LIB) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(INCS) -o $@

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS) -I$(MLX_DIR) -I$(HEADER_DIR)
ifdef WITH_BONUS
	mv $(PRE_BONUS_O) $(BONUS_DIR)
else
	mv $(PRE_MEN_O) $(MEN_DIR)
endif


$(LIB) : $(LIB_DIR)
	make -C $(LIB_DIR)

$(MLX_DIR)$(MLX):
	make -C $(MLX_DIR)

clean :	
	make clean -C $(LIB_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(MEN_O) $(BONUS_O) $(LIB)

fclean :
	make fclean -C $(LIB_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(NAME) $(MEN_O) $(BONUS_O) $(LIB)

re : fclean all

bonus : all

.PHONY : all clean fclean re bonus

