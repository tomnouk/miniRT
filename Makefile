# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 12:33:09 by anomourn          #+#    #+#              #
#    Updated: 2024/10/24 13:00:18 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3

NAME = miniRT

NAME_BONUS = miniRT_bonus

SRCS =			./get_next_line/get_next_line.c \
				./get_next_line/get_next_line_utils.c \
				Mandatory/main.c \
				Mandatory/parsing/parsing.c \
				Mandatory/parsing/read_check_assign.c \
				Mandatory/parsing/get_number_of_elements.c \
				Mandatory/parsing/read_check_utils.c \
				Mandatory/parsing/utils_checks.c \
				Mandatory/parsing/ft_atof.c \
				Mandatory/parsing/Ambient.c \
				Mandatory/parsing/Camera.c \
				Mandatory/parsing/Light.c \
				Mandatory/parsing/Sphere.c \
				Mandatory/parsing/Plane.c \
				Mandatory/parsing/Cylinder.c \
				Mandatory/vectors/vect_operations.c \
				Mandatory/vectors/vect_properties.c \
				Mandatory/vectors/vect_creation.c \
				Mandatory/user_interface/change_properties.c \
				Mandatory/user_interface/display_properties.c \
				Mandatory/user_interface/handle_input.c \
				Mandatory/user_interface/mlx_hooks.c \
				Mandatory/raytracing/create_lighting.c \
				Mandatory/raytracing/obj_intersection.c \
				Mandatory/raytracing/obj_intersection_utils.c \
				Mandatory/raytracing/trace_rays.c \
				Mandatory/raytracing/color_operations.c \
				Mandatory/minirt_utils.c

SRCS_BONUS =	./get_next_line/get_next_line.c \
				./get_next_line/get_next_line_utils.c \
				Bonus/main_bonus.c \
				Bonus/parsing/parsing_bonus.c \
				Bonus/parsing/read_check_assign_bonus.c \
				Bonus/parsing/get_number_of_elements_bonus.c \
				Bonus/parsing/read_check_utils_bonus.c \
				Bonus/parsing/utils_checks_bonus.c \
				Bonus/parsing/ft_atof_bonus.c \
				Bonus/parsing/Ambient_bonus.c \
				Bonus/parsing/Camera_bonus.c \
				Bonus/parsing/Light_bonus.c \
				Bonus/parsing/Sphere_bonus.c \
				Bonus/parsing/Plane_bonus.c \
				Bonus/parsing/Cylinder_bonus.c \
				Bonus/parsing/extras_for_bonus.c \
				Bonus/parsing/paraboloid_bonus.c \
				Bonus/vectors/vect_operations_bonus.c \
				Bonus/vectors/vect_properties_bonus.c \
				Bonus/vectors/vect_creation_bonus.c \
				Bonus/user_interface/change_properties_bonus.c \
				Bonus/user_interface/display_properties_bonus.c \
				Bonus/user_interface/handle_input_bonus.c \
				Bonus/user_interface/mlx_hooks_bonus.c \
				Bonus/raytracing/create_lighting_bonus.c \
				Bonus/raytracing/obj_intersection_bonus.c \
				Bonus/raytracing/hyperbolic_paraboloid_intersection_bonus.c \
				Bonus/raytracing/h_p_intersection_utils_bonus.c \
				Bonus/raytracing/obj_intersection_utils_bonus.c \
				Bonus/raytracing/trace_rays_bonus.c \
				Bonus/raytracing/color_operations_bonus.c \
				Bonus/minirt_utils_bonus.c

MAKE_LIBFT = make -C libft

MAKE_MLX =  make -C minilibx-linux

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

RM = rm -f

.SILENT: $(OBJS) $(OBJS_BONUS)

all: $(NAME)

$(NAME): $(OBJS)
		@echo "\e[0;32mCompiling...\e[0;m"
		@$(MAKE_LIBFT) > /dev/null
		@$(MAKE_MLX) > /dev/null
		@$(CC) $(CC_FLAGS) $(OBJS) -Lmlx_linux ./libft/libft.a ./minilibx-linux/libmlx.a -lXext -lX11 -lm -lz -o $(NAME)
		@echo "\e[0;32mCompleted! 🤠\e[0;m"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
		@echo "\e[0;33mCompiling...\e[0;m"
		@$(MAKE_LIBFT) > /dev/null
		@$(MAKE_MLX) > /dev/null
		@$(CC) $(CC_FLAGS) $(OBJS_BONUS) -Lmlx_linux ./libft/libft.a ./minilibx-linux/libmlx.a -lXext -lX11 -lm -lz -o $(NAME_BONUS)
		@echo "\e[0;32mCompleted! 🤠\e[0;m"
		
clean:
		@echo "Cleaning up..."
		@$(MAKE) clean -C ./libft > /dev/null
		$(RM) $(OBJS_BONUS) $(OBJS)
		@echo "\e[0;31mCleaned! 🧹\e[0;m"

fclean:
		@echo "\e[0;32mWait ...\e[0;m"
		@$(MAKE) fclean -C ./libft > /dev/null
		$(RM) $(OBJS) $(OBJS_BONUS) $(NAME) $(NAME_BONUS)
		@$(MAKE) clean -C ./minilibx-linux > /dev/null
		@echo "\e[0;32mCleaned! 🧹\e[0;m"

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re