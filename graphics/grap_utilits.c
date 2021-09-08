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

//write(2, "KEK\n", 4);
//my_mlx_pixel_put(&map->grap, x, i, color);
// void	verLine(t_map *map, int x, int drawStart, int drawEnd, int color)
// {
// 	int	i;

// 	i = 0;
// 	while (i < map->spec.r.y)
// 	{
// 		if (i >= drawStart && i <= drawEnd)
// 			my_mlx_pixel_put(&map->grap, x, i, color);
// 		else if (i < drawStart)
// 			my_mlx_pixel_put(&map->grap, x, i, Blue);
// 		i++;
// 	}
// }

// void	verLine_text(t_map *map, int x, int drawStart, int drawEnd)
// {
// 	int	w;

// 	w = 0;
// 	while (w < map->spec.r.y)
// 	{
// 		if (w >= drawStart && w <= drawEnd)
// 		{
// 			my_mlx_pixel_put(&map->grap, x, w, 
// 			map->text[0].data[(w % map->text[0].sprites_width) * 
// 			map->text[0].sprites_width + (x % map->text[0].sprites_height)]);
// 		}
// 		else if (w < drawStart)
// 			my_mlx_pixel_put(&map->grap, x, w, map->c);
// 		else if (w > drawEnd)
// 			my_mlx_pixel_put(&map->grap, x, w, map->f);
// 		w++;
// 	}
// }
