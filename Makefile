# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/09 14:43:43 by zhliew            #+#    #+#              #
#    Updated: 2022/08/11 16:13:06 by zhliew           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS =	main.c color.c image_utils.c

INCLUDES = cub3d.h

INC=/usr/include

INCLIB=$(INC)/usr/lib

LFLAGS =  -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

all: $(SRCS) $(INCLUDES) 
	@make -C mlx
	@gcc -Wall -Wextra -Werror -o $(NAME) $(SRCS) $(LFLAGS) mlx/libmlx.a

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@make -C mlx/ clean
	@/bin/rm -f $(NAME)

re: fclean all

PHONY: all clean fclean re