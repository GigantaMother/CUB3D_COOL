#include "../cub3d.h"

static int	check_ident_line_col_rgb(int *log, int *color, char *line, int *i);
static int	check_ident_line_color_log(char *line, int i, t_color log_rgb);

// Проверка корректности цвета
int	check_ident_line_color(int *flag, t_color *color, char *line)
{
	int		i;
	t_color	log_rgb;

	init_t_color(&log_rgb);
	*flag = *flag + 1;
	if (ft_strlen(line) < 7)
		return (error(5));
	i = 2;
	while (line[i] == ' ')
		i++;
	if (check_ident_line_col_rgb(&log_rgb.r, &color->r, line, &i) == 0)
		return (0);
	if (line[i - 1] == ' ')
		return (error(33));
	if (check_ident_line_col_rgb(&log_rgb.g, &color->g, line, &i) == 0)
		return (0);
	if (line[i - 1] == ' ')
		return (error(33));
	if (check_ident_line_col_rgb(&log_rgb.b, &color->b, line, &i) == 0)
		return (0);
	if (line[i - 1] == ',')
		return (error(19));
	if (check_ident_line_color_log(line, i, log_rgb) == 0)
		return (0);
	return (1);
}

// Проверка является ли каждый параметр числом
static int	check_ident_line_col_rgb(int *log, int *color, char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			*log = 1;
			*color = *color * 10 + (line[*i] - 48);
			if (*color > 255)
				return (error(17));
		}
		else if (line[*i] == ',')
			break ;
		else if (line[*i] == ' ')
			break ;
		else
			return (error(16));
		*i = *i + 1;
	}
	*i = *i + 1;
	return (1);
}

// Проверка полностью ли написан цвет
static int	check_ident_line_color_log(char *line, int i, t_color log_rgb)
{
	while (line[i])
	{
		if (line[i] != ' ')
			return (error(34));
		i++;
	}
	if (log_rgb.r == 0 || log_rgb.g == 0 || log_rgb.b == 0)
		return (error(18));
	return (1);
}
