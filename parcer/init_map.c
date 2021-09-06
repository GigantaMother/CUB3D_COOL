#include "../cub3d.h"

static int	memory_field(t_map *map);
static void	init_map_border(t_map *map);
static void	init_map_transfer(t_map *map, char *name);
static void	replacement(t_map *map);

// Иницилизирует данные карты (все клетки = ?)
int	init_map(t_map *map, char *name)
{
	int	i;
	int	j;

	map->line = map->line + 2;
	map->column = map->column + 2;
	if (memory_field(map) == 0)
		return (0);
	i = 0;
	while (i < map->line)
	{
		j = 0;
		while (j < map->column)
		{
			map->field[i][j] = '?';
			j++;
		}
		i++;
	}
	init_map_border(map);
	init_map_transfer(map, name);
	replacement(map);
	return (1);
}

// Выделяет нужное кол-во памяти для карты 
static int	memory_field(t_map *map)
{
	int	i;

	i = 0;
	map->field = malloc(sizeof(char *) * map->line);
	if (map->field == NULL)
		return (error(27));
	while (i < map->line)
	{
		map->field[i] = malloc(map->column);
		if (map->field[i] == NULL)
			return (error(28));
		i++;
	}
	return (1);
}

// Иницилизирует стену вокруг карты (все боковые клекти  = !)
static void	init_map_border(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->line)
	{
		map->field[i][0] = '!';
		map->field[i][map->column - 1] = '!';
		i++;
	}
	while (j < map->column)
	{
		map->field[0][j] = '!';
		map->field[map->line - 1][j] = '!';
		j++;
	}
}

// Переносит карту из файла в массив 
static void	init_map_transfer(t_map *map, char *name)
{
	char	*line;
	int		i;
	int		r;
	int		count;

	count = 0;
	i = 1;
	r = 42;
	map->fd = open(name, O_RDONLY);
	while (count < map->spec.count_line)
	{
		count++;
		get_next_line(map->fd, &line);
	}
	while (r)
	{
		r = get_next_line(map->fd, &line);
		ft_memcpy(map->field[i], line, 1, ft_strlen(line));
		i++;
		free(line);
	}
	close(map->fd);
}

// Заменяет оставшиеся ? на пробел
static void	replacement(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->line)
	{
		j = 0;
		while (j < map->column)
		{
			if (map->field[i][j] == '?')
				map->field[i][j] = ' ';
			j++;
		}
		i++;
	}
}
