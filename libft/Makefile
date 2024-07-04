# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 17:37:11 by ksuh              #+#    #+#              #
#    Updated: 2024/03/02 17:11:45 by ksuh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_BASIC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS_BASIC = $(SRCS_BASIC:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = libft.a

ifndef BONUS
	OBJS = $(OBJS_BASIC)
else
	OBJS = $(OBJS_BONUS)
endif

all : $(NAME) 

$(NAME) : $(OBJS)
	ar rcs $@ $^

%.o : %.c 
	$(CC) $(CFLAGS) -c $^ -o $@

clean :	
	rm -rf $(OBJS_BASIC) 
	rm -rf $(OBJS_BONUS)	

fclean : clean
	rm -rf $(NAME)

re : fclean all

bonus :
	make BONUS=1 all

.PHONY : all clean fclean re bonus
