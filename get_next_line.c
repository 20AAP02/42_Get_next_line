/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:50:38 by antonio           #+#    #+#             */
/*   Updated: 2021/11/22 11:32:46 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*backup;
	unsigned long	bytes_read;
	char			*line;

	if ((read(fd, 0, 0) == -1) || fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (buf[bytes_read] != '\0')
		buf[bytes_read] = '\0';
	if (bytes_read == 0 && *backup == '\0')
		return (NULL);
	if (bytes_read != 0)
	{
		backup = ft_strjoin(backup, buf);
	}
	while (ft_strchr(backup, '\n') == NULL && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (buf[bytes_read] != '\0')
			buf[bytes_read] = '\0';
		backup = ft_strjoin(backup, buf);
	}
	line = get_line(backup);
	if (ft_strchr(backup, '\n') == NULL)
	{
		while (*backup)
			backup++;
	}
	else
		backup = ft_strchr(backup, '\n') + 1;
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
	printf("\n");
	free(a[0]);
	free(a[1]);
	free(a[2]);
	free(a[3]);
	free(a);
}