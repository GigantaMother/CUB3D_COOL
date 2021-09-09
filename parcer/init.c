#include "../cub3d.h"

static void	init_t_spec(t_spec *spec);

// максимальный размер карты 50 x 50
void	init_t_map(t_map *map)
{
	map->fd = -1;
	map->line = 0;
	map->line_max = 50;
	map->column = 0;
	map->column_max = 50;
	init_t_spec(&map->spec);
}

// минимальное разрешение экрана 300 x 300
// максимальное разрешение экрана 1500 x 1500
static void	init_t_spec(t_spec *spec)
{
	spec->count_line = 0;
	spec->flag_r = 0;
	init_t_coord(&spec->r);
	spec->r_min.x = 300;
	spec->r_min.y = 300;
	spec->r_max.x = 1500;
	spec->r_max.y = 1500;
	spec->flag_no = 0;
	spec->no = -1;
	spec->flag_so = 0;
	spec->so = -1;
	spec->flag_we = 0;
	spec->we = -1;
	spec->flag_ea = 0;
	spec->ea = -1;
	spec->flag_f = 0;
	init_t_color(&spec->f);
	spec->flag_c = 0;
	init_t_color(&spec->c);
}

void	init_t_coord(t_coord *coord)
{
	coord->x = 0;
	coord->y = 0;
}

void	init_t_color(t_color *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}
