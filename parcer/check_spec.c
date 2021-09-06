#include "../cub3d.h"

static int	check_ident_line(t_spec *spec, char *line);
static int	check_ident_all(t_spec spec);
static int	check_ident_double(t_spec spec);

// Основаная функция проверки спецификаторов
int	check_ident(t_spec *spec, int fd)
{
	char	*line;
	int		ret;

	ret = 42;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		spec->count_line++;
		if (check_ident_line(spec, line) == 0)
			return (0);
		if (check_ident_all(*spec) == 1)
			return (1);
		if (check_ident_double(*spec) == 0)
			return (0);
		free(line);
	}
	if (check_ident_all(*spec) == 0)
		return (error(6));
	return (1);
}

// Проверяет отдельную строку, специфиатор это или нет
static int	check_ident_line(t_spec *spec, char *line)
{
	if (ft_strlen(line) < 7 && ft_strlen(line) != 0)
		return (error(5));
	else if (ft_strlen(line) == 0)
		return (1);
	else if (ft_strncmp(line, "R ", 2) == 0)
		return (check_ident_line_R(spec, line));
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (check_ident_line_text(&spec->flag_no, &spec->no, line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (check_ident_line_text(&spec->flag_so, &spec->so, line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (check_ident_line_text(&spec->flag_we, &spec->we, line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (check_ident_line_text(&spec->flag_ea, &spec->ea, line));
	else if (ft_strncmp(line, "F  ", 2) == 0)
		return (check_ident_line_color(&spec->flag_f, &spec->f, line));
	else if (ft_strncmp(line, "C  ", 2) == 0)
		return (check_ident_line_color(&spec->flag_c, &spec->c, line));
	else
		return (error(15));
	return (1);
}

// Определяет все ли спецификаторы найдены
static int	check_ident_all(t_spec spec)
{
	if (spec.flag_r == 1
		&& spec.flag_no == 1
		&& spec.flag_so == 1
		&& spec.flag_we == 1
		&& spec.flag_ea == 1
		&& spec.flag_f == 1
		&& spec.flag_c == 1)
		return (1);
	return (0);
}

// Определяет нет ли дублирующихся спецификаторов
static int	check_ident_double(t_spec spec)
{
	if (spec.flag_r > 1
		|| spec.flag_no > 1
		|| spec.flag_so > 1
		|| spec.flag_we > 1
		|| spec.flag_ea > 1
		|| spec.flag_f > 1
		|| spec.flag_c > 1)
		return (error(10));
	return (1);
}
