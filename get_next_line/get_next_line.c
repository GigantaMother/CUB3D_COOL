#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		*buffer;
	int			y;
	int			BUFFER_SIZE;

	BUFFER_SIZE = 10;
	y = 42;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	while (y)
	{
		if (get_check(str))
			break ;
		y = read(fd, buffer, BUFFER_SIZE);
		if (y == -1)
			return (get_end(buffer, y));
		buffer[y] = '\0';
		str = ft_strjoin(str, buffer);
	}
	*line = get_cut(str);
	str = get_tail(str);
	return (get_end(buffer, y));
}

char	*get_cut(char *str)
{
	char	*str_new;
	int		i;

	if (!str)
		return (NULL);
	str_new = malloc(sizeof(char) * (ft_strlen_c(str, '\n') + 1));
	if (!str_new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		str_new[i] = str[i];
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}

char	*get_tail(char *str)
{
	char	*str_new;
	int		size;
	int		i;

	if (!str)
		return (NULL);
	size = ft_strlen_c(str, '\n');
	if (str[size] == '\0')
	{
		free(str);
		return (NULL);
	}
	str_new = malloc(sizeof(char) * (ft_strlen_c(str, '\0') - size + 1));
	if (!str_new)
		return (NULL);
	size++;
	i = 0;
	while (str[size + i])
	{
		str_new[i] = str[size + i];
		i++;
	}
	str_new[i] = '\0';
	free(str);
	return (str_new);
}

int	get_check(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	get_end(char *buffer, int y)
{
	free(buffer);
	if (y == -1)
		return (y);
	else if (y == 0)
		return (y);
	else
		return (1);
}
