#include "../cub3d.h"

// перевод цвета
int	rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// оптимизированный вывод
void	my_mlx_pixel_put(t_grap *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// отрисовка прямоугольника
void	square_print(t_map *map, t_coord start, t_coord size, int color)
{
	int	i;
	int	j;

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
