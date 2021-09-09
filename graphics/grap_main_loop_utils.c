#include "../cub3d.h"

int	char_in_str(char cr, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == cr)
			return (1);
	}
	return (0);
}

int	numOfText(int side, int stepY, int stepX)
{
	if (side == 1)
	{
		if (stepY == -1)
			return (WE);
		else
			return (EA);
	}
	else
	{
		if (stepX == -1)
			return (NO);
		else
			return (SO);
	}
}

int	it_is_not_wall(t_map *map, double row, double col)
{
	if (map->field[(int)row][(int)col] != '0')
		return (0);
	else if (map->field[(int)(row + 0.11)][(int)(col + 0.11)] != '0')
		return (0);
	else if (map->field[(int)(row + 0.11)][(int)(col)] != 48)
		return (0);
	else if (map->field[(int)(row)][(int)(col + 0.11)] != 48)
		return (0);
	else if (map->field[(int)(row - 0.11)][(int)(col - 0.11)] != 48)
		return (0);
	else if (map->field[(int)(row - 0.11)][(int)(col)] != 48)
		return (0);
	else if (map->field[(int)(row)][(int)(col - 0.11)] != 48)
		return (0);
	return (1);
}
