# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 12:33:09 by anomourn          #+#    #+#              #
#    Updated: 2024/09/10 16:48:48 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -g

CFLAGS = -Wall -Wextra -Werror

NAME = minirt

NAME_BONUS = minirt_bonus

SRCS =	./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c \
		main.c \
		./parsing/parsing.c \
		./parsing/read_check_assign.c \
		./parsing/get_number_of_elements.c \
		./parsing/read_check_utils.c \
		./parsing/utils_checks.c \
		./parsing/ft_atof.c \
		./parsing/Ambient.c \
		./parsing/Camera.c \
		./vectors/operations.c

SRCS_BONUS =

MAKE_LIBFT = make -C libft

MAKE_MLX =  make -C minilibx-linux

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

RM = rm -f

.SILENT: $(OBJS) $(OBJS_BONUS)

all: $(NAME)

$(NAME): $(OBJS)
		@echo "\e[0;35m$< ----> $@\e[0;m"
		@$(MAKE_LIBFT)
		@$(MAKE_MLX)
		@$(CC) $(CC_FLAGS) $(OBJS) -Lmlx_linux ./libft/libft.a ./minilibx-linux/libmlx.a -lXext -lX11 -lm -lz -o $(NAME)
		@echo "\e[0;32mCompleted! 🤠\e[0;m"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
		@echo "\e[0;35m$< ----> $@\e[0;m"
		@$(MAKE_LIBFT) 
		@$(MAKE_MLX)
		@$(CC) $(CC_FLAGS) $(OBJS_BONUS) -Lmlx_linux ./libft/libft.a ./minilibx-linux/libmlx.a -lXext -lX11 -lm -lz -o $(NAME_BONUS)
		@echo "\e[0;32mCompleted! 🤠\e[0;m"
		
clean:
		@echo "Cleaning up..."
		@$(MAKE) clean -C ./libft
		$(RM) $(OBJS_BONUS) $(OBJS)
		@echo "\e[0;31mCleaned! 🧹\e[0;m"

fclean:
		@echo "\e[0;32mWait ...\e[0;m"
		@$(MAKE) fclean -C ./libft
		$(RM) $(OBJS) $(OBJS_BONUS) $(NAME) $(NAME_BONUS)
		@$(MAKE) clean -C ./minilibx-linux
		@echo "\e[0;32mCleaned! 🧹\e[0;m"

re: fclean all

.PHONY: all bonus clean fclean re