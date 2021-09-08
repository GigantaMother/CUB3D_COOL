#include "../cub3d.h"

static void	init_player_E_W(t_map *map, int i, int j);
static void	init_player_N_S(t_map *map, int i, int j);

// начальные данные игрока
// N - север S - юг E - восток  W - запад 
void	init_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->line)
	{
		j = 0;
		while (j < map->column)
		{
			if (map->field[i][j] == 'E' || map->field[i][j] == 'N' || \
				map->field[i][j] == 'W' || map->field[i][j] == 'S')
			{
				map->lodev.posX = i + 0.5;
				map->lodev.posY = j + 0.5;
				init_player_N_S(map, i, j);
			}
			j++;
		}
		i++;
	}
	map->lodev.w = map->spec.r.x;
	map->lodev.h = map->spec.r.y;
	map->lodev.moveSpeed = 0.1;
	map->lodev.rotSpeed = 0.1;
}

static void	init_player_N_S(t_map *map, int i, int j)
{
	if (map->field[i][j] == 'N')
	{
		map->lodev.dirX = -1.0;
		map->lodev.dirY = 0;
		map->lodev.planeX = 0;
		map->lodev.planeY = 0.66;
	}
	else if (map->field[i][j] == 'S')
	{
		map->lodev.dirX = 1.0;
		map->lodev.dirY = 0;
		map->lodev.planeX = 0;
		map->lodev.planeY = -0.66;
	}
	else
		init_player_E_W(map, i, j);
}

static void	init_player_E_W(t_map *map, int i, int j)
{
	if (map->field[i][j] == 'E')
	{
		map->lodev.dirX = 0;
		map->lodev.dirY = 1;
		map->lodev.planeX = 0.66;
		map->lodev.planeY = 0;
	}
	else if (map->field[i][j] == 'W')
	{
		map->lodev.dirX = 0;
		map->lodev.dirY = -1.0;
		map->lodev.planeX = -0.66;
		map->lodev.planeY = 0;
	}
}

int	min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

int	max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}
