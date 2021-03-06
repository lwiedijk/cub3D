# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwiedijk <lwiedijk@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/14 15:20:32 by lwiedijk      #+#    #+#                  #
#    Updated: 2021/08/25 11:41:55 by lwiedijk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC_FILES = main.c
HEADER_FILES = cub3d.h mlx/mlx.h

INIT_SRC_FILES = initiate.c read_textures.c \
ft_error.c ft_read.c free.c \

PARSE_DIR = parser/
PARSE_SRC_FILES = parse.c \
parse_screenres.c parse_textures.c \
parse_color.c parse_map.c \
check_screenres.c check_map.c \
check_argument.c parser_utils.c

FRAME_BUILD_DIR = frame_build/
FRAME_BUILD_SRC_FILES = key_button_hook.c \
render_frame.c player_movement.c \
ray_casting.c minimap.c \
dda.c draw_walls.c ray_casting_utils.c


LIBFT_DIR = libft/
LIBFT =	libft.a

MLX_DIR		=	mlx/
MLX			=	libmlx.dylib

CFLAGS = -Wall -Wextra -Werror -g

OBJS_DIR = objs/
_OBJ_FILES = $(SRC_FILES:.c=.o) \
$(INIT_SRC_FILES:.c=.o) \
$(addprefix $(PARSE_DIR), $(PARSE_SRC_FILES:.c=.o)) \
$(addprefix $(FRAME_BUILD_DIR), $(FRAME_BUILD_SRC_FILES:.c=.o)) \

OBJ_FILES = $(addprefix $(OBJS_DIR), $(_OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT) ./
	make -C $(MLX_DIR)
	cp $(MLX_DIR)$(MLX) ./
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)

clean:
	rm -f $(LIBFT) $(MLX) $(_OBJ_FILES) $(OBJ_FILES)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
