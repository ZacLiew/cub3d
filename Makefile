# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 13:17:07 by leu-lee           #+#    #+#              #
#    Updated: 2022/09/06 15:16:48 by zhliew           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC			= gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1
CCD			= gcc -Wall -Wextra -Werror -fsanitize=address -g3
MACMLX 		= -framework OpenGl -framework Appkit -lm

RM			= rm -rf

SRCS_DIR	= ./src
OBJS_DIR	= ./obj
GNL_DIR		= ./get_next_line

SRCS		= color.c image_utils.c floor_ceiling.c game_loop.c \
				get_wall.c key_event.c minimap.c mouse_event.c raycasting.c \
				read_file.c check_map_valid.c get_textures.c parsing_utils.c \
				player_direction.c \
				

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

SRCS_GNL	= get_next_line.c get_next_line_utils.c
OBJS_GNL	= $(SRCS_GNL:%.c=$(OBJS_DIR)/%.o)

LIB			= -lmlx -Lmlx -Llibft -lft
INCLUDES	= -Imlx -Iincludes -Ilibft -Iget_next_line

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_GNL) main.c libft/libft.a
		@$(CC) main.c $(OBJS) $(OBJS_GNL) $(INCLUDES) $(LIB) $(MACMLX) -o $@
		@echo "$(GREEN)Compiled $@ successfully $(RESET)"
	
libft/libft.a:
		@make bonus -C libft

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(INCLUDES) -c $< -o $@

test:
		make && "./cub3d ./maps/map2.cub"

clean:
	@$(RM) $(OBJS_DIR) $(NAME)
	@echo "$(RED)Removed $(NAME) .obj$(RESET)"

fclean: clean
	@$(RM) $(OBJS_DIR)
	@make fclean -C libft
	@echo "$(RED)Removed $(NAME)$(RESET)"

re: fclean all

.PHONY: all run clean fclean

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
