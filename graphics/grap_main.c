#include "../cub3d.h"

void	display_game(t_print_data *vel, t_map *map, int x)
{
	int	w;
	int	texY;

	w = 0;
	while (w < map->spec.r.y)
	{
		if (w >= vel->drawStart && w <= vel->drawEnd)
		{
			texY = (int)vel->texPos & (map->text[vel->numText].sprites_height
					- 1);
			vel->texPos += vel->step;
			my_mlx_pixel_put(&map->grap, x, w, map->text[vel->numText].data[texY
				* map->text[vel->numText].sprites_height + vel->texX]);
		}
		else if (w < vel->drawStart)
			my_mlx_pixel_put(&map->grap, x, w, map->c);
		else if (w > vel->drawEnd)
			my_mlx_pixel_put(&map->grap, x, w, map->f);
		w++;
	}
}

int	ft_map_print(t_map *map)
{
	t_print_data	vel;
	int				x;

	x = 0;
	while (x < map->lodev.w)
	{
		calculate_img1(&vel, map, x);
		calculate_img2(&vel, map);
		calculate_img3(&vel, map);
		calculate_img4(&vel, map);
		calculate_img5(&vel, map);
		display_game(&vel, map, x);
		x++;
	}
	ft_mini_map(map);
	mlx_put_image_to_window(map->grap.mlx, map->grap.win, map->grap.img, 0, 0);
	return (0);
}

int	main_graphics(t_map *map)
{
	if (init_grap(map) == 0)
		return (0);
	init_text(map);
	init_mini_map(map);
	ft_map_print(map);
	mlx_hook(map->grap.win, 2, 1L << 2, key_hook_press, map);
	mlx_hook(map->grap.win, 3, 1L << 3, key_hook_repress, map);
	mlx_hook(map->grap.win, 17, 1L << 2, key_hook_close, map);
	mlx_loop(map->grap.mlx);
	return (1);
}
