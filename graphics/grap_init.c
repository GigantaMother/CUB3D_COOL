#include "../cub3d.h"

// иницилизация начальных параметров для работы с графикой
int	init_grap(t_map *map)
{
	map->grap.mlx = mlx_init();
	if (map->grap.mlx == NULL)
		return (error(31));
	map->grap.win = mlx_new_window(map->grap.mlx, map->spec.r.x, map->spec.r.y, \
					 "cub3D");
	map->grap.img = mlx_new_image(map->grap.mlx, map->spec.r.x, map->spec.r.y);
	map->grap.addr = mlx_get_data_addr(map->grap.img, \
									&map->grap.bits_per_pixel, \
									&map->grap.line_length, &map->grap.endian);
	init_buttom(&map->button);
	init_player(map);
	map->f = rgb(1, map->spec.f.r, map->spec.f.g, map->spec.f.b);
	map->c = rgb(1, map->spec.c.r, map->spec.c.g, map->spec.c.b);
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

void	init_mini_map(t_map *map)
{
	map->mini_map.color_wall = Gray;
	map->mini_map.color_empty = White;
	map->mini_map.color_player = Lime;
	map->mini_map.size = 2;
	map->mini_map.mode = 0;
}

/*
	printf("%s\n", map->spec.no_way);
	printf("%s\n", map->spec.so_way);
	printf("%s\n", map->spec.we_way);
	printf("%s\n", map->spec.ea_way);
*/
void	init_text(t_map *map)
{
	map->field[(int)map->lodev.posX][(int)map->lodev.posY] = '0';
	map->text = malloc(sizeof(t_text) * 4);
	if (map->text == NULL)
		error(36);
	map->text[0].wall = mlx_xpm_file_to_image(map->grap.mlx, \
		map->spec.no_way, &map->text[0].sprites_width, \
		&map->text[0].sprites_height);
	map->text[0].data = (int *)mlx_get_data_addr(map->text[0].wall, \
		&map->text[0].bpp, &map->text[0].size_line, &map->text[0].endlan);
	map->text[1].wall = mlx_xpm_file_to_image(map->grap.mlx, \
		 map->spec.so_way, &map->text[1].sprites_width, \
		&map->text[1].sprites_height);
	map->text[1].data = (int *)mlx_get_data_addr(map->text[1].wall, \
		&map->text[1].bpp, &map->text[1].size_line, &map->text[1].endlan);
	map->text[2].wall = mlx_xpm_file_to_image(map->grap.mlx, \
		map->spec.we_way, &map->text[2].sprites_width, \
		&map->text[2].sprites_height);
	map->text[2].data = (int *)mlx_get_data_addr(map->text[2].wall, \
		&map->text[2].bpp, &map->text[2].size_line, &map->text[2].endlan);
	map->text[3].wall = mlx_xpm_file_to_image(map->grap.mlx, \
		map->spec.ea_way, &map->text[3].sprites_width, \
		&map->text[3].sprites_height);
	map->text[3].data = (int *)mlx_get_data_addr(map->text[3].wall, \
		&map->text[3].bpp, &map->text[3].size_line, &map->text[3].endlan);
}
