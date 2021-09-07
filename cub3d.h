#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "get_next_line/get_next_line.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

// перечисление для цветов
enum e_color {
	White = 16777215,
	Black = 0,
	Gray = 8421504,
	Red = 16711680,
	Lime = 65280,
	Blue = 255,
	Yellow = 16776960,
	Fuchsia = 16711935,
	Aqua = 65535
};

enum e_button {
	Esc = 53,
	Up = 13,
	Down = 1,
	Right = 2,
	Left = 0,
	Turn_right = 124,
	Turn_left = 123,
	M = 46
};
// структура для координат чего либо(целые числа)
typedef struct s_coord
{
	int	x;
	int	y;
}t_coord;

// структура для координат чего либо(float числа)
typedef struct s_coord_f
{
	float	x;
	float	y;
}t_coord_f;

// структура для цвета
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}t_color;

// структура для спецификаторов
typedef struct s_spec
{
	int		count_line;
	int		flag_r;
	t_coord	r;
	t_coord	r_min;
	t_coord	r_max;
	int		flag_no;
	int		no;
	int		flag_so;
	int		so;
	int		flag_we;
	int		we;
	int		flag_ea;
	int		ea;
	int		flag_s;
	int		s;
	int		flag_f;
	t_color	f;
	int		flag_c;
	t_color	c;
}t_spec;

typedef struct s_lodev
{
	double posX;
	double posY;

	double dirX;
	double dirY;

	double planeX;
	double planeY;

	double moveSpeed;
	double rotSpeed;

	int		sprites_width;
	int 	sprites_height;

	int		size_line;
	int		endlan;
	int		bpp;

	void	*wall_no;
	// void	*wall_so;
	// void	*wall_we;
	// void	*wall_ea;

	int		*data_no;
	// int		*data_so;
	// int		*data_we;
	// int		*data_ea;


	int		w;
	int		h;

} t_lodev;

// структура для графики
typedef struct s_grap
{
	void	*mlx;
	void	*win;
	void	*img;
	int		img_width;
	int		img_height;
	
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_grap;

// структура для кнопок
// 0 отжата 1 нажата
typedef struct s_button
{
	int	up;
	int	down;
	int	right;
	int	left;
	int	turn_right;
	int	turn_left;
}t_button;

//структура для игрока
typedef struct s_player
{
	t_coord_f	coord; // координата персонажа
	float		angle;  // куда смотрит персонаж
	float		speed_moving; // скорость движения
	float		speed_turn; // скорость поворота
	float		angle_view; // угол обзора
	int			ray_count; // кол-во лучей
	int			cell_size; // размер 1 ячейки мини карты
	int			cell_zoom; // часть экрана, которую может занимать миникарта
	int			cell_ray;  // во сколько раз лучей на мини карте будет меньше, чем в 3д
}t_player;

// структура для карты
typedef struct s_map
{
	int			fd;
	char		**field;
	int			line;
	int			line_max;
	int			column;
	int			column_max;
	t_spec		spec;
	t_grap		grap;
	t_button	button;
	t_player	player;

	t_lodev 	lodev;
}t_map;

//  функции из файла grap_main.c
int		main_graphics(t_map *map);
void verLine_text(t_map *map, int x, int drawStart, int drawEnd, int color);

//  функции из файла grap_utilits.c
int		rgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_grap *map, int x, int y, int color);
void	square_print(t_map *map, t_coord start, t_coord size, int color);
int		min(int x, int y);

//  функции из файла grap_init.c
int		init_grap(t_map *map);
void	init_buttom(t_button *button);

//  функции из файла grap_my_test.c
void print_help(t_map *map);
int map_print(t_map *map);


//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------

// функции из файла init.c (4)
void	init_t_map(t_map *map);
void	init_t_coord(t_coord *coord);
void	init_t_color(t_color *color);

// функции из файла init_map.c (5)
int		init_map(t_map *map, char *name);

// функции из файла check_file.c (3)
int		main_parser(int argc, char **argv, t_map *map);
int		check_open_file(char *name);

// функции из файла check_spec.c (4)
int		check_ident(t_spec *spec, int fd);

// функции из файла check_spec_line.c (5)
int		check_ident_line_R(t_spec *spec, char *line);
int		check_ident_line_text(int *flag, int *texture, char *line);

// функции из файла check_spec_color.c (3)
int		check_ident_line_color(int *flag, t_color *color, char *line);

// функции из файла utilits.c (4)
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, int start, size_t n);
void	skip_symbols(char *str, int *i, char symbol);
//char	**ft_free(char **tab, size_t i);

// функции из файла check_map.c (4)
int		check_map(t_map *map);
int		check_map_symbol(char c);

// функции из файла check_border.c (2)
int		check_border(t_map map);

//  функции из файла error.c (5)
int		error(int e);

//  функции из файла print.c (3)
void	print_mod(t_map map, int mod);

void verLine(t_map *map, int x, int drawStart, int drawEnd, int color);

#endif