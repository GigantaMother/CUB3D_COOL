#include "../cub3d.h"

static void	key_hook_press_take(int keycode, t_map *map);
static void	key_hook_press_take_minimap(int keycode, t_map *map);

int	key_hook_press(int keycode, t_map *map)
{
	double	testPosX;
	double	testPosY;

	mlx_destroy_image(map->grap.mlx, map->grap.img);
	map->grap.img = mlx_new_image(map->grap.mlx, map->spec.r.x, map->spec.r.y);
	if (map->grap.img == NULL)
		error(38);
	map->grap.addr = mlx_get_data_addr(map->grap.img, \
	&map->grap.bits_per_pixel, &map->grap.line_length, &map->grap.endian);
	testPosX = map->lodev.posX;
	testPosY = map->lodev.posY;
	key_hook_press_take(keycode, map);
	if (map->button.up == 1 && map->button.down == 0)
		move_forward(map, 1, &testPosX, &testPosY);
	else if (map->button.down == 1 && map->button.up == 0)
		move_forward(map, -1, &testPosX, &testPosY);
	if (map->button.right == 1 && map->button.left == 0)
		move_side(map, 1, &testPosX, &testPosY);
	else if (map->button.left == 1 && map->button.right == 0)
		move_side(map, -1, &testPosX, &testPosY);
	key_hook_press_turn_r(map);
	key_hook_press_turn_l(map);
	change_player_position(map, testPosX, testPosY);
	ft_map_print(map);
	return (1);
}

static void	key_hook_press_take(int keycode, t_map *map)
{
	if (keycode == Esc)
	{
		printf("Выход через esc\n");
		mlx_destroy_window(map->grap.mlx, map->grap.win);
		exit (0);
	}
	else if (keycode == Up && map->button.up == 0)
		map->button.up = 1;
	else if (keycode == Down && map->button.down == 0)
		map->button.down = 1;
	else if (keycode == Right && map->button.right == 0)
		map->button.right = 1;
	else if (keycode == Left && map->button.left == 0)
		map->button.left = 1;
	else if (keycode == Turn_right && map->button.turn_right == 0)
		map->button.turn_right = 1;
	else if (keycode == Turn_left && map->button.turn_left == 0)
		map->button.turn_left = 1;
	else
		key_hook_press_take_minimap(keycode, map);
}

static void	key_hook_press_take_minimap(int keycode, t_map *map)
{
	if (keycode == M)
	{
		if (map->mini_map.size == 4)
			map->mini_map.size = 0;
		else
			map->mini_map.size++;
	}
	else if (keycode == F)
	{
		if (map->mini_map.mode == 2)
			map->mini_map.mode = 0;
		else
			map->mini_map.mode++;
	}
}

void	key_hook_press_turn_r(t_map *map)
{
	double	oldDirX;
	double	oldPlaneX;

	if (map->button.turn_right == 1 && map->button.turn_left == 0)
	{
		oldDirX = map->lodev.dirX;
		map->lodev.dirX = map->lodev.dirX * cos(-map->lodev.rotSpeed) - \
		map->lodev.dirY * sin(-map->lodev.rotSpeed);
		map->lodev.dirY = oldDirX * sin(-map->lodev.rotSpeed) + \
		map->lodev.dirY * cos(-map->lodev.rotSpeed);
		oldPlaneX = map->lodev.planeX;
		map->lodev.planeX = map->lodev.planeX * cos(-map->lodev.rotSpeed) - \
		map->lodev.planeY * sin(-map->lodev.rotSpeed);
		map->lodev.planeY = oldPlaneX * sin(-map->lodev.rotSpeed) + \
		map->lodev.planeY * cos(-map->lodev.rotSpeed);
	}
}

void	key_hook_press_turn_l(t_map *map)
{
	double	oldDirX;
	double	oldPlaneX;

	if (map->button.turn_left == 1 && map->button.turn_right == 0)
	{
		oldDirX = map->lodev.dirX;
		map->lodev.dirX = map->lodev.dirX * cos(map->lodev.rotSpeed) - \
		map->lodev.dirY * sin(map->lodev.rotSpeed);
		map->lodev.dirY = oldDirX * sin(map->lodev.rotSpeed) + \
		map->lodev.dirY * cos(map->lodev.rotSpeed);
		oldPlaneX = map->lodev.planeX;
		map->lodev.planeX = map->lodev.planeX * cos(map->lodev.rotSpeed) - \
		map->lodev.planeY * sin(map->lodev.rotSpeed);
		map->lodev.planeY = oldPlaneX * sin(map->lodev.rotSpeed) + \
		map->lodev.planeY * cos(map->lodev.rotSpeed);
	}
}
