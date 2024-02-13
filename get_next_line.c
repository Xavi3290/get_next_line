/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:45:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/02/13 13:19:19 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buf)
{
	char	*line;
	int		read_bytes;

	read_bytes = 1;
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (ft_free(&buf));
	while (read_bytes > 0 && !ft_strchr(buf, '\n'))
	{
		read_bytes = read(fd, line, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(line), ft_free(&buf));
		if ((read_bytes == 0 && !buf))
			return (free(line), NULL);
		line[read_bytes] = '\0';
		buf = ft_strjoin(buf, line);
		if (!buf)
			return (free(line), NULL);
	}
	free(line);
	return (buf);
}

static char	*get_line(char *buf)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buf || buf[i] == '\0')
		return (NULL);
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*clean_buf(char *buf)
{
	char	*subs;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	if (!buf[i])
		return (ft_free(&buf));
	subs = malloc(sizeof(char) * ((ft_strlen(buf) - i) + 1));
	if (!subs)
		return (ft_free(&buf));
	while (buf[i] != '\0')
	{
		subs[j] = buf[i];
		j++;
		i++;
	}
	subs[j] = '\0';
	ft_free(&buf);
	return (subs);
}

char	*get_next_line(int fd)
{
	char		*content;
	static char	*buffer;

	content = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!buffer || (buffer && !ft_strchr(buffer, '\n')))
		buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	content = get_line(buffer);
	if (!content)
		return (ft_free(&buffer));
	buffer = clean_buf(buffer);
	return (content);
}
