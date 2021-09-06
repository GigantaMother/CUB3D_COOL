#include "../cub3d.h"

// перевод цвета
int		rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// оптимизированный вывод
void	my_mlx_pixel_put(t_grap *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// отрисовка прямоугольника
void	square_print(t_map *map, t_coord start, t_coord size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size.x)
	{
		j = 0;
		while (j < size.y)
		{
			my_mlx_pixel_put(&map->grap, start.x + i, start.y + j, color);
			j++;
		}
		i++;
	}
}

void verLine(t_map *map, int x, int drawStart, int drawEnd, int color)
{
	int i;

	i = 0;
	while (i < map->spec.r.y)
	{
		if (i <= drawStart && i >= drawEnd)
		{
			//write(2, "KEK\n", 4);
			//my_mlx_pixel_put(&map->grap, x, i, color);
			my_mlx_pixel_put(&map->grap, 5, i, color);
		}
		//my_mlx_pixel_put(&map->grap, x, i, color);
		i++;
	}
}


int min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}
