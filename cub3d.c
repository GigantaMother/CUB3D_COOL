#include "./cub3d.h"

// компиляция
// gcc libmlx.dylib -framework OpenGL -framework Appkit
// get_next_line/*.c parcer/*.c graphics/*.c *.c && ./a.out map1.cub
// Основная функция, запускает основные этапы обработки
int	main(int argc, char **argv)
{
	t_map	map;

	if (main_parser(argc, argv, &map) == 0)
		exit (0);
	printf("C парсером всё хорошо\n");
	print_mod(map, 3);
	if (main_graphics(&map) == 0)
		exit (0);
	exit (0);
}
