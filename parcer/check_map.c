#include "../cub3d.h"

static int	check_map_help(t_map *map, int *player, char *line, int ret);
static int	check_map_line(t_map *map, char *line, int *player);

// Проверяет корректность карты
int	check_map(t_map *map)
{
	char	*line;
	int		ret;
	int		player;

	ret = 42;
	player = 0;
	while (ret)
	{
		ret = get_next_line(map->fd, &line);
		if (ft_strlen(line) != 0)
			break ;
		free(line);
		map->spec.count_line++;
	}
	if (check_map_help(map, &player, line, ret) == 0)
		return (0);
	free(line);
	if (player == 0)
		return (error(25));
	if (map->line < 3 || map->column < 3)
		return (error(29));
	return (1);
}

// Помогает проверять корректность карты =)
static int	check_map_help(t_map *map, int *player, char *line, int ret)
{
	while (ret)
	{
		if (ft_strlen(line) == 0)
			break ;
		if (check_map_line(map, line, player) == 0)
			return (0);
		if (*player > 1)
			return (error(21));
		ret = get_next_line(map->fd, &line);
		free(line);
	}
	if (ft_strlen(line) != 0)
	{
		if (check_map_line(map, line, player) == 0)
			return (0);
	}
	while (ret)
	{
		ret = get_next_line(map->fd, &line);
		if (ft_strlen(line) != 0)
			return (error(26));
		free(line);
	}
	return (1);
}

// Проверяет карту построчно
static int	check_map_line(t_map *map, char *line, int *player)
{
	int	i;

	i = 0;
	map->line++;
	if (map->line > map->line_max)
		return (error(23));
	if (ft_strlen(line) > map->column)
	{
		map->column = ft_strlen(line);
		if (map->column > map->column_max)
			return (error(24));
	}
	while (line[i])
	{
		if (check_map_symbol(line[i]) == 3)
			*player = *player + 1;
		if (check_map_symbol(line[i]) == 0)
			return (error(22));
		i++;
	}
	return (1);
}

// Проверяет корректность символа
// 3 - игрок, 2 - пол в лабиринте, 1 - стена или пробел 0 - ошибка
int	check_map_symbol(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (3);
	else if (c == '0')
		return (2);
	else if (c == '1' || c == ' ' || c == '\n')
		return (1);
	else
		return (0);
}
