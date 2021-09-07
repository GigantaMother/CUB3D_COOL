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
			if (map->field[i][j] == 'E' || map->field[i][j] == 'N' || map->field[i][j] == 'W' || map->field[i][j] == 'S')
			{
				map->lodev.posX = i + 0.5;
				map->lodev.posY = j + 0.5;

				map->lodev.dirX = -1.0;
				map->lodev.dirY = 0;

				map->lodev.planeX = 0;
				map->lodev.planeY = 0.66;
			}
			j++;
		}
		i++;
	}
	//-------
	map->lodev.w = map->spec.r.x;
	map->lodev.h = map->spec.r.y;
	
	map->lodev.moveSpeed = 0.1;
	map->lodev.rotSpeed = 0.1;
	//--------
}

void init_text(t_map *map)
{
	map->field[(int)map->lodev.posX][(int)map->lodev.posY] = '0';

	map->lodev.wall_no = mlx_xpm_file_to_image(map->grap.mlx, "textures/brick1.xpm", &map->lodev.sprites_width, &map->lodev.sprites_height);
	printf("map->lodev.sprites_width= %d\n", map->lodev.sprites_width);
	printf("map->lodev.sprites_height= %d\n", map->lodev.sprites_height);
	// map->lodev.wall_so = mlx_xpm_file_to_image(map->grap.mlx, "textures/brick2.xpm", &map->lodev.sprites_width, &map->lodev.sprites_height);
	// map->lodev.wall_we = mlx_xpm_file_to_image(map->grap.mlx, "textures/brick3.xpm", &map->lodev.sprites_width, &map->lodev.sprites_height);
	// map->lodev.wall_ea = mlx_xpm_file_to_image(map->grap.mlx, "textures/brick4.xpm", &map->lodev.sprites_width, &map->lodev.sprites_height);

	map->lodev.size_line = 0;
	map->lodev.endlan = 0;
	map->lodev.bpp = 32;
	map->lodev.data_no = (int *)mlx_get_data_addr(map->lodev.wall_no, &map->lodev.bpp, &map->lodev.size_line, &map->lodev.endlan);
	printf("map->lodev.bpp= %d\n", map->lodev.bpp);
	printf("map->lodev.size_line= %d\n", map->lodev.size_line);
	printf("map->lodev.endlan= %d\n",map->lodev.endlan);
}
