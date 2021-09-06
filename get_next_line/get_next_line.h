#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
char	*get_cut(char *str);
char	*get_tail(char *str);
int		get_check(char *str);
int		get_end(char *buffer, int y);

char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen_c(const char *s, char c);

#endif