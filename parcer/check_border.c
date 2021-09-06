#include "../cub3d.h"

static int	check_border_cell(t_map map, int i, int j);

// Проверяет корректность карты
int	check_border(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.line)
	{
		j = 0;
		while (j < map.column)
		{
			if (check_map_symbol(map.field[i][j]) >= 2)
			{
				if (check_border_cell(map, i, j) == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// Проверяет корректность для каждой ячейки
static int	check_border_cell(t_map map, int i, int j)
{
	if (map.field[i + 1][j] == ' '
	|| map.field[i - 1][j] == ' '
	|| map.field[i][j + 1] == ' '
	|| map.field[i][j - 1] == ' ' )
		return (error(30));
	if (map.field[i + 1][j] == '!'
	|| map.field[i - 1][j] == '!'
	|| map.field[i][j + 1] == '!'
	|| map.field[i][j - 1] == '!' )
		return (error(30));
	if (map.field[i + 1][j + 1] == ' '
	|| map.field[i - 1][j + 1] == ' '
	|| map.field[i - 1][j - 1] == ' '
	|| map.field[i + 1][j - 1] == ' ' )
		return (error(30));
	if (map.field[i + 1][j + 1] == '!'
	|| map.field[i - 1][j + 1] == '!'
	|| map.field[i - 1][j - 1] == '!'
	|| map.field[i + 1][j - 1] == '!' )
		return (error(30));
	return (1);
}
