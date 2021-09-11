#include "./cub3d.h"

// Основная функция, запускает основные этапы обработки
// print_mod(map, 3);
int	main(int argc, char **argv)
{
	t_map	map;

	if (main_parser(argc, argv, &map) == 0)
		exit (0);
	if (main_graphics(&map) == 0)
		exit (0);
	exit (0);
}
