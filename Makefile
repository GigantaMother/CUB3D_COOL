CC = gcc

SRCS := error.c \
		cub3d.c \
		graphics/grap_init.c \
		graphics/grap_main.c \
		graphics/grap_my_test.c \
		graphics/grap_utilits.c \
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

NAME	=	so_long

FLAGS	= 					

OBJ		=	$(patsubst %.c, %.o, $(SRCS))

all		:	$(NAME)

$(NAME)	:	$(SRC)
	gcc $(CFLAGS)  -c $(SRCS)
	gcc $(FLAGS) $(SRCS) -o -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -lmx

clean	:
	rm -f $(OBJ)

fclean	:	clean
	rm -f $(NAME)

.PHONY	:	all clean fclean re