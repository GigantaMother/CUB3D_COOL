#include "../cub3d.h"

void print_help(t_map *map)
{
	t_coord square;
	t_coord square_size;
	//---------------------------Отрисовка пола и потолка----
	init_t_coord (&square);
	square_size.x = map->spec.r.x;
	square_size.y = map->spec.r.y / 2;
	square_print(map, square, square_size,\
	rgb(1, map->spec.c.r, map->spec.c.g, map->spec.c.b));
	square.y = map->spec.r.y / 2;
	square_print(map, square, square_size,\
	rgb(1, map->spec.f.r, map->spec.f.g, map->spec.f.b));
	//---------------------------Отрисовка мини карты----
	if (map->player.cell_zoom > 0)
	{
		map->player.cell_size = min(map->spec.r.x / map->player.cell_zoom / map->line,
								map->spec.r.y / map->player.cell_zoom / map->column);
		map->player.cell_ray = map->player.ray_count / map->player.cell_zoom / 5;
		int	i;
		int	j;

		square_size.x = map->player.cell_size;
		square_size.y = map->player.cell_size;
		i = 0;
		while (i < map->column)
		{
			j = 0;
			while (j < map->line)
			{
				square.x = i * map->player.cell_size;
				square.y = j * map->player.cell_size;
				if (map->field[j][i] == '!')
					square_print(map, square, square_size, Black);
				else if (map->field[j][i] == '1')
					square_print(map, square, square_size, Red);
				else if (check_map_symbol(map->field[j][i]) >= 2)
					square_print(map, square, square_size, White);
				j++;
			}
			i++;
		}
	}
	//---------------------------Отрисовка персонажа----
	if (map->player.cell_zoom > 0)
	{
		square.x = map->player.coord.x * map->player.cell_size;
		square.y = map->player.coord.y * map->player.cell_size;
		square_size.x = 1;
		square_size.y = 1;
		square_print(map, square, square_size, Blue);
	}
}

int map_print(t_map *map)
{
	t_coord square;
	t_coord square_size;
	print_help(map);
	if (map->player.cell_zoom > 0)
	{
		//---------------------------Отрисовка лучей----
		float start = map->player.angle - map->player.angle_view / 2;
		float	end = map->player.angle + map->player.angle_view / 2;
		float step = (end - start) / map->player.ray_count;
		float x = map->player.coord.x * map->player.cell_size;
		float y = map->player.coord.y * map->player.cell_size;
		int ray = map->player.ray_count; // кол-во лучей на мини карте
		//---
		//printf("x=%f y=%f\n", x, y);
		int lych = 0; // проверка сколько лучей было кинуто
		//int ray_length = 0; // длина каждого луча

		//printf("start= %f\n", start);
		//printf("end= %f\n", end);

		float lenght = 0; // длина луча

		while (ray > 0)
		{
			x = map->player.coord.x * map->player.cell_size;
			y = map->player.coord.y * map->player.cell_size;
			//ray_length = 0;
			while (42)
			{
				x = x + cos(start) / 10;
				y = y + sin(start) / 10;
				//ray_length++;
				if (map->field[(int)(y/map->player.cell_size)][(int)x/map->player.cell_size] == '1')
					break;
				my_mlx_pixel_put(&map->grap, x, y, Blue);
			}
			lenght = sqrt((x / map->player.cell_size - map->player.coord.x) * (x / map->player.cell_size - map->player.coord.x) +
						  (y / map->player.cell_size - map->player.coord.y) * (y / map->player.cell_size - map->player.coord.y));

			lenght = lenght * cos(start - map->player.angle);

			if (lenght > 20)
				lenght = 0;
			else
				lenght = 20 - lenght;
		
			lenght = lenght * map->spec.r.y / 20;
			if (lenght >= map->spec.r.y)
				lenght = map->spec.r.y;

			//printf("%d)lenght= %f x=%f map->x= %f y= %f map->y= %f\n", lych, lenght, x, map->player.coord.x, y, map->player.coord.y);
			
			square.x = lych;
			square.y = map->spec.r.y / 2 - lenght / 2;
			square_size.x = 1;
			square_size.y = lenght;
			square_print(map, square, square_size, Lime); // Lime = 65280

			start += step;
			ray--;
			lych++;
		}
		printf("лучей: %d\n", lych);
	}
	//-------------------------------------------
	mlx_put_image_to_window(map->grap.mlx, map->grap.win, map->grap.img, 0, 0);

	return (1);
}
