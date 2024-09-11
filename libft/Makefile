# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 17:10:52 by myeochoi          #+#    #+#              #
#    Updated: 2024/09/04 17:34:32 by ksuh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	=	cc
# CFALG	=	-Wall -Wextra -Werror
NAME	=	libft.a
SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c\
ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c\
ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c\
ft_toupper.c get_next_line.c ft_isspace.c ft_strcmp.c ft_atod.c ft_iscomma.c

BONUS_S	=	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c\
ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c\
ft_lstnew_bonus.c ft_lstsize_bonus.c get_next_line.c ft_isspace.c ft_strcmp.c ft_atod.c \
ft_iscomma.c

OBJS	=	$(SRCS:.c=.o)
BONUS_O	=	$(BONUS_S:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS)	:	$(SRCS)
	$(CC) $(CFALG) -c $(SRCS) 

bonus	:	$(BONUS_S)
	$(CC) $(CFALG) -c $(BONUS_S)
	ar rcs $(NAME) $(BONUS_O)

clean	:
	rm -rf $(OBJS) $(BONUS_O)

fclean	:	clean
	rm -rf $(NAME)

re	:	fclean all

.PHONY	:	re clean fclean all bonus
