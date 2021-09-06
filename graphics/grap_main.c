#include "../cub3d.h"

//123 left 124 right 
//126 вверх 125 вниз 
int	key_hook_press(int keycode, t_map *map)
{
	mlx_destroy_image(map->grap.mlx, map->grap.img);
	map->grap.img = mlx_new_image(map->grap.mlx, map->spec.r.x, map->spec.r.y);
	map->grap.addr = mlx_get_data_addr(map->grap.img, &map->grap.bits_per_pixel, &map->grap.line_length,
								&map->grap.endian); 

	float x_step = cos(map->player.angle) * map->player.speed_moving;
	float y_step = sin(map->player.angle) * map->player.speed_moving;

	if (keycode == Esc )
	{
		printf("Выход через esc\n");
		mlx_destroy_window(map->grap.mlx, map->grap.win);
		exit (0);
	}
	else if (keycode == Up && map->button.up == 0)
	{
		map->button.up = 1;
		//printf("Вверх нажато\n");
	}
	else if (keycode == Down && map->button.down == 0)
	{
		map->button.down = 1;
		//printf("Вниз нажато\n");
	}
	else if (keycode == Right && map->button.right == 0)
	{
		map->button.right = 1;
		//printf("Вправо нажато\n");
	}
	else if (keycode == Left && map->button.left == 0)
	{
		map->button.left = 1;
		//printf("Влево нажато\n");
	}
	else if (keycode == Turn_right && map->button.turn_right == 0)
	{
		map->button.turn_right = 1;
		//printf("Поворот вправо нажато\n");
	}
	else if (keycode == Turn_left && map->button.turn_left == 0)
	{
		map->button.turn_left = 1;
		//printf("Поворот влево нажато\n");
	}
	else if (keycode == M)
	{
		if (map->player.cell_zoom < 4)
			map->player.cell_zoom++;
		else
			map->player.cell_zoom = 0;
		//printf("Режим миникарты\n");
	}
	else
		printf("Неизвестная клавиша %d\n", keycode);

	// движение вперёд/назад
	if (map->button.up == 1 && map->button.down == 0)
	{
		// printf("--------------------\n");
		// printf("x(до)=%f y(до)=%f\n", map->player.coord.x, map->player.coord.y);
		// printf("элемент до(%c)\n", map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x)]);

		if (map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x + x_step)] != '1')
			map->player.coord.x += x_step;
		if (map->field[(int)(map->player.coord.y + y_step)][(int)(map->player.coord.x)] != '1')
			map->player.coord.y += y_step;

		// printf("x(после)=%f y(после)=%f\n", map->player.coord.x, map->player.coord.y);
		// printf("элемент после(%c)\n", map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x)]);
	}
	else if (map->button.down == 1 && map->button.up == 0)
	{
		// printf("--------------------\n");
		// printf("x(до)=%f y(до)=%f\n", map->player.coord.x, map->player.coord.y);
		// printf("элемент до(%c)\n", map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x)]);

		if (map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x - x_step)] != '1')
			map->player.coord.x -= x_step;
		if (map->field[(int)(map->player.coord.y - y_step)][(int)(map->player.coord.x)] != '1')
			map->player.coord.y -= y_step;

		// printf("x(после)=%f y(после)=%f\n", map->player.coord.x, map->player.coord.y);
		// printf("элемент после(%c)\n", map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x)]);
	}
	// движение вправо/влево
	if (map->button.right == 1 && map->button.left == 0)
	{
		if (map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x - y_step)] != '1')
			map->player.coord.x -= y_step;
		if (map->field[(int)(map->player.coord.y + x_step)][(int)(map->player.coord.x)] != '1')
			map->player.coord.y += x_step;
	}
	else if (map->button.left == 1 && map->button.right == 0)
	{
		if (map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x + y_step)] != '1')
			map->player.coord.x += y_step;
		if (map->field[(int)(map->player.coord.y - x_step)][(int)(map->player.coord.x)] != '1')
			map->player.coord.y -= x_step;
	}
	// поворот вправо/влево
	if (map->button.turn_right == 1 && map->button.turn_left == 0)
	{
		map->player.angle += map->player.speed_turn;
	}
	else if (map->button.turn_left == 1 && map->button.turn_right == 0)
	{
		map->player.angle -= map->player.speed_turn;
	}

	printf("(%f,%f)\n", map->player.coord.x, map->player.coord.y);
	//-Менять-----------
	map_print(map);
	//------------------
	return (1);
}

int	key_hook_repress(int keycode, t_map *map)
{
	if (keycode == Up && map->button.up == 1)
	{
		map->button.up = 0;
		//printf("Вверх отжато\n");
	}
	else if (keycode == Down && map->button.down == 1)
	{
		map->button.down = 0;
		//printf("Вниз отжато\n");
	}
	else if (keycode == Right && map->button.right == 1)
	{
		map->button.right = 0;
		//printf("Вправо отжато\n");
	}
	else if (keycode == Left && map->button.left == 1)
	{
		map->button.left = 0;
		//printf("Влево отжато\n");
	}
	else if (keycode == Turn_right && map->button.turn_right == 1)
	{
		map->button.turn_right = 0;
		//printf("Поворот вправо отжато\n");
	}
	else if (keycode == Turn_left && map->button.turn_left == 1)
	{
		map->button.turn_left = 0;
		//printf("Поворот влево отжато\n");
	}

	return (1);
}

int key_hook_close(int keycode, t_map *map)
{
	printf("Выход через крестик\n");
	//mlx_destroy_window(map->grap.mlx, map->grap.win);
	exit (0);
}

int		main_graphics(t_map *map)
{
	if (init_grap(map) == 0)
		return (0);

	//-Менять-----------
	map_print(map);
	//------------------

	mlx_hook(map->grap.win, 2, 1L << 2, key_hook_press, map);
	mlx_hook(map->grap.win, 3, 1L << 3, key_hook_repress, map); 
	mlx_hook(map->grap.win, 17, 1L << 2, key_hook_close, map);

	mlx_loop(map->grap.mlx);
	return (1);
}
