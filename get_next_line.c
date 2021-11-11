#include "get_next_line.h"

#define BUFFER_SIZE 40

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

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

char	*ft_strdup(const char *s1)
{
	int		s1_lenght;
	char	*str;
	int		i;

	s1_lenght = 0;
	while (s1[s1_lenght])
		s1_lenght++;
	str = malloc(s1_lenght + 1);
	if (!str)
		return (str);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	new_str = malloc(i + j + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	new_str[i] = 0;
	return (new_str);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	index;

	if (!s)
		return (NULL);
	if (!len || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start > len)
		ptr = (char *)malloc((len + 1) * sizeof(char));
	else
		ptr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	index = 0;
	while (index < len && s[start + index])
	{
		ptr[index] = s[start + index];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

char *get_line(char *line, char *backup)
{
	int i;
	char *ptr_free;
	if (ft_strchr(backup, '\n') != NULL)
		line = malloc((ft_strchr(backup, '\n') - backup) + 2);
	else
		line = malloc((ft_strchr(backup, '\0') - backup) + 1);
	i = 0;
	while(backup[i])
	{
		if (backup[i] == '\n')
		{
			line[i] = '\n';
			line[i + 1] = 0;
			break;
		}
		else if (backup[i] == '\0')
		{
			line[i] = '\0';
			free(backup);
			backup = NULL;
			break;
		}
		else
		{
			line[i] = backup[i];
			i++;
		}
	}
	return (line);
}

void delete_line_from_backup(char *backup, char *line)
{
	if (ft_strchr(backup, '\n') != NULL)
		backup = ft_strchr(backup, '\n') + 1;
	else
	{
		free(backup);
		backup = NULL;
	}	
}

char *get_next_line(int fd)
{
	char buf[BUFFER_SIZE + 1];
	static char *backup;
	unsigned long bytes_read;
	char *line;

	if (fd < 0 || fd >= RLIMIT_NOFILE || BUFFER_SIZE < 1)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	if (backup == NULL)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
			return (NULL);
		backup = malloc(1);
		*backup = 0;
		backup = ft_strjoin(backup, buf);
	}
	while (ft_strchr(backup, '\n') == NULL && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = 0;
		backup = ft_strjoin(backup, buf);
	}
	line = get_line(line, backup);
	delete_line_from_backup(backup, line);
	return (line);
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