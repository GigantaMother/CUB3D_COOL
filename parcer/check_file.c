#include "../cub3d.h"

static int	check_arguments(int argc, char **argv);

// Основная функция парсера, заускает основные этапы
int	main_parser(int argc, char **argv, t_map *map)
{
	init_t_map(map);
	if (check_arguments(argc, argv) == 0)
		return (0);
	map->fd = check_open_file(argv[1]);
	if (map->fd == 0)
		return (0);
	if (check_ident(&map->spec, map->fd) == 0)
		return (0);
	if (check_map(map) == 0)
		return (0);
	close(map->fd);
	if (init_map(map, argv[1]) == 0)
		return (0);
	if (check_border(*map) == 0)
		return (0);
	return (1);
}

// Функция провряет кол-во аргументов передаваемых в программу
// и их корректность
static int	check_arguments(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		return (error(1));
	len = ft_strlen(argv[1]);
	if (len < 4)
		return (error(2));
	else
	{
		if (argv[1][len - 4] != '.' ||
			argv[1][len - 3] != 'c' ||
			argv[1][len - 2] != 'u' ||
			argv[1][len - 1] != 'b')
			return (error(3));
	}
	return (1);
}

// Функция проверяет удалось ли открыть нужный файл
int	check_open_file(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (error(4));
	return (fd);
}
