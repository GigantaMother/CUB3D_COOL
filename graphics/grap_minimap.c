#include "../cub3d.h"

static void	ft_mini_map_block(t_map *map, t_coord coord_player, \
								t_coord start, t_coord size);
static void	ft_mini_map_player(t_map *map, int cell);
static void	ft_coord(t_coord *a, int a_x, int a_y);

void	ft_mini_map(t_map *map)
{
	t_coord	start;
	t_coord	size;
	t_coord	coord_player;
	int		i;
	int		j;

	i = 0;
	if (map->mini_map.size == 0)
		return ;
	map->mini_map.cell = min(map->spec.r.x / map->column / map->mini_map.size,
			map->spec.r.y / map->line / map->mini_map.size);
	ft_coord(&size, map->mini_map.cell, map->mini_map.cell);
	while (i < map->line)
	{
		j = 0;
		while (j < map->column)
		{
			ft_coord(&start, j * map->mini_map.cell, i * map->mini_map.cell);
			ft_coord(&coord_player, i, j);
			ft_mini_map_block(map, coord_player, start, size);
			j++;
		}
		i++;
	}
	ft_mini_map_player(map, map->mini_map.cell);
}

static void	ft_mini_map_block(	t_map *map, t_coord coord_player, \
								t_coord start, t_coord size)
{
	if (map->mini_map.mode == 0)
	{
		if (map->field[coord_player.x][coord_player.y] == '1')
			square_print(map, start, size, map->mini_map.color_wall);
		else if (map->field[coord_player.x][coord_player.y] == '0')
			square_print(map, start, size, map->mini_map.color_empty);
	}
	else if (map->mini_map.mode == 1)
	{
		if (map->field[coord_player.x][coord_player.y] == '1')
			square_print(map, start, size, map->mini_map.color_wall);
	}
	else if (map->mini_map.mode == 2)
	{
		if (map->field[coord_player.x][coord_player.y] == '0')
			square_print(map, start, size, map->mini_map.color_empty);
	}
}

static void	ft_mini_map_player(t_map *map, int cell)
{
	t_coord	start;
	t_coord	size;

	start.x = (map->lodev.posY - 0.5) * cell + cell / 4;
	start.y = (map->lodev.posX - 0.5) * cell + cell / 4;
	size.x = cell / 2;
	size.y = cell / 2;
	square_print(map, start, size, map->mini_map.color_player);
}

static void	ft_coord(t_coord *a, int a_x, int a_y)
{
	a->x = a_x;
	a->y = a_y;
}
