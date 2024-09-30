# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 20:45:10 by cmenke            #+#    #+#              #
#    Updated: 2023/10/14 19:26:45 by cmenke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

LIBFT_DIR = libft
LIBFT = libft.a

MLX_DIR = mlx
MLX = libmlx.a

SRC_DIR := sources

OBJ_DIR := objects

IMPORT_SCENE := $(addprefix import_scene/,\
							clear_import_data.c \
							convert_to_double_matrix.c \
							get_ambient_cam_light.c \
							get_atof.c \
							get_elemente_data.c \
							get_rgb_or_fov.c \
							get_xyz_vector_rgb.c \
							import_scene.c \
							is_rt_file.c \
							messages.c \
							print_functions.c \
							read_rt_file.c \
							tokenize_one_element.c)

SRCS := 	miniRT.c \
			vector_function.c \
			vector_functions_2.c \
			render_and_init_mlx.c \
			color_objects_intersecting.c \
			color_objects.c \
			sphere.c \
			plane.c \
			cylinder.c \
			cylinder_body_intersection.c \
			cylinder_cap_intersection.c \
			cylinder_cap_intersection2.c \
			compute_camera_ray.c \
			shadows.c \
			pixel_to_image.c \
			exit_functions.c \
			$(IMPORT_SCENE)


OBJS := $(patsubst %.c, ${OBJ_DIR}/%.o, ${SRCS})

HEADER := $(addprefix includes/,miniRT.h structs.h import_scene.h messages.h)

LDFLAGS := -L ${LIBFT_DIR} -lft -L ${MLX_DIR} -lmlx -lm -framework OpenGL -framework AppKit

#Production flags
CFLAGS := -Wall -Werror -Wextra -O3 -I includes
# CPPFLAGS := -DWIDTH=640 -DHEIGHT=480

#Development flags
# CFLAGS := -Wall -Wextra -I includes
# CFLAGS += Werror
#CFLAGS += -g -O0
# CFLAGS += -O3
# CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=undefined

CC := cc
export CC

RM := rm -f

all: library ${NAME}

library:
	make -C $(MLX_DIR)
	make -C ${LIBFT_DIR}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${CPPFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${HEADER} | ${OBJ_DIR}
	${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o $@

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}
	mkdir -p ${OBJ_DIR}/import_scene

clean:
	${RM} -r ${OBJ_DIR}
	make fclean -C ${LIBFT_DIR}
	make clean -C $(MLX_DIR)

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re library

.NOTPARALLEL:
