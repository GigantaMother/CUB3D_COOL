#include "../cub3d.h"

static void	print_field(t_map map);
static void	print_spec(t_spec spec);

// Функция печати исъодных данных
// id=1 - только карта
// id=2 - только спецификаторы
// id=3 - печатьв всего
void	print_mod(t_map map, int mod)
{
	if (mod == 1)
		print_field(map);
	else if (mod == 2)
		print_spec(map.spec);
	else if (mod == 3)
	{
		print_field(map);
		print_spec(map.spec);
	}
	else
		error (20);
}

// Печать карты и её основных характеристик
static void	print_field(t_map map)
{
	int	i;
	int	j;

	i = 0;
	printf("Строк карты: %d\n", map.line);
	printf("Столбцов карты: %d\n", map.column);
	printf("КАРТА\n");
	if (map.field == NULL)
		return ;
	while (i < map.line)
	{
		j = 0;
		while (j < map.column)
		{
			printf("%c", map.field[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// Печать спецификаторов
static void	print_spec(t_spec spec)
{
	printf("\n");
	printf("count_line:%d\n", spec.count_line);
	printf("r:%d(%d, %d)\n", spec.flag_r, spec.r.x, spec.r.y);
	printf("no:%d(%d)\n", spec.flag_no, spec.no);
	printf("so:%d(%d)\n", spec.flag_so, spec.so);
	printf("we:%d(%d)\n", spec.flag_we, spec.we);
	printf("ea:%d(%d)\n", spec.flag_ea, spec.ea);
	printf("f:%d(%d, %d, %d)\n", spec.flag_f, spec.f.r, spec.f.g, spec.f.b);
	printf("c:%d(%d, %d, %d)\n", spec.flag_c, spec.c.r, spec.c.g, spec.c.b);
}
