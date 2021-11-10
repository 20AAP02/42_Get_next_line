#include "get_next_line.h"

#define BUFFER_SIZE 40

char *get_next_line(int fd)
{
	char *str;

	str = malloc(BUFFER_SIZE + 1);

	read(fd, str, BUFFER_SIZE);
	return (str);
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