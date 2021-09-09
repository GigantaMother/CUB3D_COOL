#include "../cub3d.h"

static int	check_ident_line_R_x(t_spec *spec, char *line, int *i);
static int	check_ident_line_R_y(t_spec *spec, char *line, int *i);
static int	check_ident_line_text_str(int *start, int *end, char *line);

// Проверка корректности разрешения
int	check_ident_line_R(t_spec *spec, char *line)
{
	int	i;

	i = 2;
	spec->flag_r++;
	while (line[i] == ' ')
		i++;
	if (check_ident_line_R_x(spec, line, &i) == 0)
		return (0);
	if (line[i] != ' ')
		return (error(8));
	i++;
	skip_symbols(line, &i, ' ');
	if (check_ident_line_R_y(spec, line, &i) == 0)
		return (0);
	if (spec->r.x < spec->r_min.x)
		return (error(13));
	if (spec->r.y < spec->r_min.y)
		return (error(14));
	while (line[i])
	{
		if (line[i] != ' ')
			return (error(32));
		i++;
	}
	return (1);
}

// Проверка корректности разрешения: ширина
// printf("Hello %d\n", spec->r.x);
static int	check_ident_line_R_x(t_spec *spec, char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			spec->r.x = spec->r.x * 10 + (line[*i] - 48);
			if (spec->r.x > spec->r_max.x)
				return (error(11));
		}
		else if (line[*i] == ' ')
			break ;
		else
			return (error(7));
		*i = *i + 1;
	}
	return (1);
}

// Проверка корректности разрешения: высота
static int	check_ident_line_R_y(t_spec *spec, char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			spec->r.y = spec->r.y * 10 + (line[*i] - 48);
			if (spec->r.y > spec->r_max.y)
				return (error(12));
		}
		else if (line[*i] == ' ')
			break ;
		else
			return (error(9));
		*i = *i + 1;
	}
	return (1);
}

// Определяет является ли спецификатор-текстура верным
int	check_id_line(int *flag, int *texture, char *line, char **way)
{
	int	l;
	int	start;
	int	end;
	int	len;

	*flag = *flag + 1;
	l = ft_strlen(line);
	start = 3;
	end = -1;
	if (check_ident_line_text_str(&start, &end, line) == 0)
		return (0);
	if (line[end - 3] != '.' || line[end - 2] != 'x' || \
		line[end - 1] != 'p' || line[end] != 'm')
		return (error(3));
	line = line + start;
	*texture = check_open_file(line);
	close (*texture);
	if (*texture == 0)
		return (0);
	len = ft_strlen(line);
	(*way) = malloc(sizeof(char) * (len + 1));
	ft_check_copy(line, way, len);
	return (1);
}

// Определяет часть строки, которая является путём для текстуры
static int	check_ident_line_text_str(int *start, int *end, char *line)
{
	int	i;

	while (line[*start] == ' ')
		*start = *start + 1;
	i = *start;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			*end = i - 1;
			while (line[i] == ' ')
				i++;
			if (line[i] && line[i] != ' ')
				return (error(35));
			line[*end + 1] = '\0';
			break ;
		}
		i++;
	}
	if (*end == -1)
		*end = i - 1;
	return (1);
}
