CC = gcc

SRCS := error.c \
		cub3d.c \
		graphics/grap_init_player.c \
		graphics/grap_init.c \
		graphics/grap_key_help.c \
		graphics/grap_key.c \
		graphics/grap_main.c \
		graphics/grap_minimap.c \
		graphics/grap_utilits.c \
		graphics/grap_main_loop_utils.c \
		graphics/grap_move.c \
		graphics/grap_calculate_img.c \
		parcer/check_border.c \
		parcer/check_file.c \
		parcer/check_map.c \
		parcer/check_spec_color.c \
		parcer/check_spec_line.c \
		parcer/check_spec.c \
		parcer/init_map.c \
		parcer/init.c \
		parcer/print.c \
		parcer/utilits.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

NAME	=	CUB3D

INCLUDE = -I./ -I./get_next_line

FRAEMWORKS= -framework OpenGL -framework AppKit

HEADER = cub3d.h

LIBS = libft.a libmlx.a

CFLAGS	= -Wall -Wextra -Werror					

OBJ		=	$(patsubst %.c, %.o,$(SRCS))

%.o:%.c $(HEADER)
			$(CC) $(CFLAGS) $(INCLUDE) -c -g $< -o $@
all		:	$(NAME)

$(NAME)	: $(OBJ)
	$(MAKE) -C ./libft
	cp libft/libft.a .
	$(MAKE) -C minilibx_macos/ all
	cp minilibx_macos/libmlx.a .
	$(CC) $(CFLAGS) -g -o $(NAME) $(FLAG) $(OBJ) $(FRAEMWORKS) $(LIBS)

clean:
	rm -rf $(OBJ) $(LIBS)
	$(MAKE) -C ./minilibx_macos/ clean
	$(MAKE) -C ./libft clean

fclean: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re:		fclean all

$(NAME)	:	$(OBJ)

