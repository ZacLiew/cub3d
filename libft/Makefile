# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 13:17:07 by leu-lee           #+#    #+#              #
#    Updated: 2022/03/21 17:41:39 by leu-lee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
						ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
						ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
						ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
						ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
						ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
						ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
						ft_strndup.c ft_strncpy.c

BONUS		=		ft_lstadd_front.c ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c \
						ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(BONUS:.c=.o)

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

NAME		= libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
		@ar rcs $(NAME) $(OBJS)
		@echo "$(GREEN)Compiled $@ successfully$(RESET)"

bonus:		$(OBJS) $(OBJS_BONUS)
		@ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

%.o: %.c
		@$(CC) $(CFLAGS) -c $<
clean:
		@$(RM) $(OBJS) $(OBJS_BONUS)
		@echo "$(RED)Removed $(NAME) .obj$(RESET)"


fclean:		clean
		@$(RM) $(NAME)
		@echo "$(RED)Removed $(NAME)$(RESET)"

re:			fclean all

.PHONY:		all bonus clean fclean re

# Colors are great!
# Formats are greater!
# https://misc.flogisoft.com/bash/tip_colors_and_formatting
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[033m
BLUE	= \033[034m
PINK	= \033[035m
TEAL	= \033[036m
WHITE	= \033[037m
RESET	= \033[0m # No Color
