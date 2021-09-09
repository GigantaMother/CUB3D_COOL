#include "../cub3d.h"

int	key_hook_repress(int keycode, t_map *map)
{
	if (keycode == Up && map->button.up == 1)
		map->button.up = 0;
	else if (keycode == Down && map->button.down == 1)
		map->button.down = 0;
	else if (keycode == Right && map->button.right == 1)
		map->button.right = 0;
	else if (keycode == Left && map->button.left == 1)
		map->button.left = 0;
	else if (keycode == Turn_right && map->button.turn_right == 1)
		map->button.turn_right = 0;
	else if (keycode == Turn_left && map->button.turn_left == 1)
		map->button.turn_left = 0;
	return (1);
}

int	key_hook_close(int keycode, t_map *map)
{
	printf("exit be ESC\n");
	exit (0);
}
