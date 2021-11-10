#include "get_next_line.h"

#define BUFFER_SIZE 40

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	else
	{
		i = ft_strlen(dst);
		j = 0;
		while (src[j] != '\0' && i + 1 < size)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}

char	*ft_strchr(const char *s, int c)
{
	int	index;

	index = 0;
	if (s[index] == (char)c)
		return ((char *)s);
	while (s[index++] != '\0')
		if (s[index] == (char)c)
			return ((char *)s + index);
	return (NULL);
}

char *get_next_line(int fd)
{
	char buf[BUFFER_SIZE];
	static char *backup;

	if (fd < 0 || fd >= RLIMIT_NOFILE || BUFFER_SIZE < 1)
		return (NULL);
	if (backup != NULL && ft_strchr(backup, '\n') == NULL)
		backup = NULL;
	while (ft_strchr(backup, '\n') == NULL)
	{
		read(fd, buf, BUFFER_SIZE);
		strlcat(backup, buf, BUFFER_SIZE);
	}
	if (ft_strchr(backup, '\n') == )
	return (NULL);
}

int main()
{
	int fd;
	char **a;

	a = malloc(300);
	fd = open("a.txt", O_RDONLY);
	int i = 0;
	while (1)
	{
		a[i] = get_next_line(fd);
		if (a[i] == NULL)
			break;
		i++;
	}
	int j = 0;
	while (j < i)
		printf("%s", a[j++]);
}