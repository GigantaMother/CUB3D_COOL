#include "../cub3d.h"

// подсчёт длины классчический 
int	ft_strlen(const char *s)
{
	size_t	size;

	if (!s)
		return (0);
	size = 0;
	while (*s)
	{
		size++;
		s++;
	}
	return (size);
}

// сравнивает n символов
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
		i++;
	}
	if (i == n)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// копирует n символов начиная со start
void	*ft_memcpy(void *dst, const void *src, int start, size_t n)
{
	unsigned char	*p;
	unsigned char	*t;
	size_t			i;

	i = 0;
	p = (unsigned char *)dst;
	t = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		p[i + start] = t[i];
		i++;
	}
	return (dst);
}

// двигает индекс в место, где заканчиваются пробелы
void	skip_symbols(char *str, int *i, char symbol)
{
	while (str[*i] == symbol)
		*i = *i + 1;
}

// char	**ft_free(char **tab, size_t i)
// {
// 	while (i--)
// 	{
// 		if (!tab[i] || !*tab[i])
// 			break ;
// 		free(tab[i]);
// 		tab[i] = NULL;
// 	}
// 	free(*tab);
// 	return (NULL);
// }
