#include "../cub3d.h"

//static void	init_buttom(t_button *button);
static void	init_player(t_map *map);

// иницилизация начальных параметров для работы с графикой
int	init_grap(t_map *map)
{
	map->grap.mlx = mlx_init();
	if (map->grap.mlx == NULL)
		return (error(31));
	map->grap.win = mlx_new_window(map->grap.mlx, map->spec.r.x, map->spec.r.y, "cub3D");
	map->grap.img = mlx_new_image(map->grap.mlx, map->spec.r.x, map->spec.r.y);
	map->grap.addr = mlx_get_data_addr(map->grap.img, &map->grap.bits_per_pixel, &map->grap.line_length,
								&map->grap.endian);
	init_buttom(&map->button);
	init_player(map);
	return (1);
}

// установка статуса кнопок
 void	init_buttom(t_button *button)
{
	button->up = 0;
	button->down = 0;
	button->right = 0;
	button->left = 0;
	button->turn_right = 0;
	button->turn_left = 0;
}

// начальные данные игрока
static void	init_player(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (i < map->line)
	{
		j = 0;
		while (j < map->column)
		{
			if (map->field[i][j] == 'E' || map->field[i][j] == 'N' ||
				map->field[i][j] == 'W' || map->field[i][j] == 'S')
			{
				map->player.coord.x = j + 0.5;
				map->player.coord.y = i + 0.5;
				if (map->field[i][j] == 'E')
					map->player.angle = 0;
				else if (map->field[i][j] == 'N')
					map->player.angle = 3 * M_PI / 2;
				else if (map->field[i][j] == 'W')
					map->player.angle = M_PI;
				else if (map->field[i][j] == 'S')
					map->player.angle = M_PI / 2;
			}
			j++;
		}
		i++;
	}
	//-------
	map->player.speed_moving = 0.101;
	map->player.speed_turn = M_PI / 60;
	map->player.angle_view = M_PI / 3;
	map->player.ray_count = map->spec.r.x;
	map->player.cell_zoom = 3;
	map->player.cell_size = min(map->spec.r.x / map->player.cell_zoom / map->line,
								map->spec.r.y / map->player.cell_zoom / map->column);
	map->player.cell_ray = map->player.ray_count / map->player.cell_zoom / 5;
	//printf("\nx_cell=%d, y_cell= %d\n", x_cell, y_cell);
}