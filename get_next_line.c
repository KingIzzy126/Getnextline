/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:55:25 by ialashqa          #+#    #+#             */
/*   Updated: 2024/01/07 16:51:11 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_end(char *str, size_t i)
{
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*trim_buffer(char *s1)
{
	size_t	start;
	char	*trimmed_str;

	if (s1 == NULL || *s1 == '\0')
	{
		free(s1);
		return (NULL);
	}
	start = line_end(s1, 0);
	trimmed_str = ft_substr(s1, start, ft_strlen(s1) - start);
	free(s1);
	return (trimmed_str);
}

char	*get_first_line(char *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (NULL);
	i = line_end(str, i);
	line = (char *)malloc(sizeof(char) * i + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*freebuff(char *buffer1, char *buffer2)
{
	free(buffer1);
	free(buffer2);
	buffer2 = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*content;
	int			bytes;

	bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	content = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (content == NULL)
		return (NULL);
	while (!(ft_strchr(buffer, '\n')) && bytes > 0)
	{
		bytes = read(fd, content, BUFFER_SIZE);
		if (bytes == -1)
		{
			buffer = freebuff(content, buffer);
			return (NULL);
		}
		content[bytes] = '\0';
		buffer = ft_strjoin(buffer, content);
	}
	free(content);
	content = get_first_line(buffer);
	buffer = trim_buffer(buffer);
	return (content);
}
