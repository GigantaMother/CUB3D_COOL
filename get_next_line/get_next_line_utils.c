#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (0);
	i = ft_strlen_c(s1, '\0');
	j = ft_strlen_c(s2, '\0');
	new_str = (char *)malloc(sizeof(char) * (i + j + 1));
	if (new_str == NULL)
		return (NULL);
	ft_memmove(new_str, s1, i);
	ft_memmove(new_str + i, s2, j);
	new_str[i + j] = '\0';
	free((char *)s1);
	return (new_str);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned char	*h;
	size_t			i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	p = (unsigned char *)dst;
	h = (unsigned char *)src;
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			*(p + len) = *(h + len);
		}
	}
	else
	{
		while (++i < len)
			*(p + i) = *(h + i);
	}
	return (dst);
}

size_t	ft_strlen_c(const char *s, char c)
{
	size_t	size;

	size = 0;
	if (s)
	{
		while (s[size])
		{
			if (s[size] == c)
				break ;
			size++;
		}
	}
	return (size);
}
