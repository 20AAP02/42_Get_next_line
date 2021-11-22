/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio <antonio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:50:28 by antonio           #+#    #+#             */
/*   Updated: 2021/11/22 10:23:08 by antonio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
