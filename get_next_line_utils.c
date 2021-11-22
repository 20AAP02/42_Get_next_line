/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:50:28 by antonio           #+#    #+#             */
/*   Updated: 2021/11/22 11:32:33 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

void	get_line_block(char *backup, char *line, int *i)
{
	while (backup[*i])
	{
		if (backup[*i] == '\n')
		{
			line[*i] = '\n';
			*i += 1;
			break ;
		}
		line[*i] = backup[*i];
		*i += 1;
	}
}

char	*get_line(char *backup)
{
	char	*line;
	int		i;

	i = 0;
	while (backup[i])
	{
		if (backup[i++] == '\n')
			break ;
	}
	if (ft_strchr(backup, '\n') != NULL)
		i += 2;
	else
		i++;
	line = malloc(i + 1);
	i = 0;
	get_line_block(backup, line, &i);
	line[i] = '\0';
	return (line);
}
