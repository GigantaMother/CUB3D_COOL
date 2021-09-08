#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "get_next_line/get_next_line.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

#define WE 2
#define SO 1
#define NO 0
#define EA 3
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
	M = 46,
	F = 3
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
	char 	*no_way;

	int		flag_so;
	int		so;
	char 	*so_way;

	int		flag_we;
	int		we;
	char 	*we_way;

	int		flag_ea;
	int		ea;
	char 	*ea_way;

	int		flag_s;
	int		s;
	int		flag_f;
	t_color	f;
	int		flag_c;
	t_color	c;
}t_spec;

typedef struct s_lodev
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
	int		w;
	int		h;

}	t_lodev;

typedef struct s_text
{
	int		sprites_width;
	int		sprites_height;
	int		size_line;
	int		endlan;
	int		bpp;
	void	*wall;
	int		*data;
}	t_text;

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

typedef struct s_mini_map
{
	int	color_wall;
	int	color_empty;
	int	color_player;
	int	size;
	int	mode;
	int cell;

}t_mini_map;

// структура для карты
typedef struct s_map
{
	int			fd;
	char		**field;
	int			line;
	int			line_max;
	int			column;
	int			column_max;
	int			f;
	int			c;
	t_spec		spec;
	t_grap		grap;
	t_button	button;
	t_text		*text;
	t_mini_map	mini_map;
	t_lodev		lodev;
}t_map;

void	ft_check_copy(char *line, char **way, int len);
int		key_hook_close(int keycode, t_map *map);
int		ft_map_print(t_map *map);
void	move_forward(t_map *map, int flag, double *x, double *y);
void	move_side(t_map *map, int flag, double *x, double *y);
void	change_player_position(t_map *map, double row, double col);
int		key_hook_press(int keycode, t_map *map);
int		key_hook_repress(int keycode, t_map *map);
//  функции из файла grap_main.c
void	ft_mini_map(t_map *map);
void	init_text(t_map *map);
int		main_graphics(t_map *map);
//void	verLine_text(t_map *map, int x, int drawStart, int drawEnd);
void	init_mini_map(t_map *map);
void	init_player(t_map *map);

//  функции из файла grap_utilits.c
int		rgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_grap *map, int x, int y, int color);
void	square_print(t_map *map, t_coord start, t_coord size, int color);
int		min(int x, int y);

//  функции из файла grap_init.c
int		init_grap(t_map *map);
void	init_buttom(t_button *button);

//  функции из файла grap_my_test.c
void	print_help(t_map *map);
int		map_print(t_map *map);

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
//-------------------------------------------------------------------------
int		check_id_line(int *flag, int *texture, char *line, char **way);
//-------------------------------------------------------------------------
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
//void	verLine(t_map *map, int x, int drawStart, int drawEnd, int color);

#endif
