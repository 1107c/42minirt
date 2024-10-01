# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 11:30:30 by ksuh              #+#    #+#              #
#    Updated: 2024/09/16 06:37:12 by myeochoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS =-g -Wall -Wextra -Werror
MEN_DIR = ./srcs/
BONUS_DIR	=	./bonus/

PRE_MEN_C = 2d_array_utils.c bump.c cam_utils.c checker.c close.c cn_utils.c \
			cy_handler.c cy_utils.c draw_utils.c draw.c error.c get_ray_dist.c \
			get_uv.c init_utils.c init.c intersect_utils3.c intersection.c \
			key_handle_2.c key_handle.c light_and_shadow.c lst_utils.c \
			main.c matrix_utils.c mouse_handle.c parse_element.c parse_figure.c \
			parse_utils.c parse.c print_data.c threads.c vector_util.c \
			vector_util2.c xs.c xpm_util_1.c xpm_util_2.c light_and_shadow_utils.c \
			key_bump.c cy_handler2.c

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
