/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:00:17 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/02/13 13:19:33 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buffer[OPEN_MAX];

	content = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (!buffer[fd] || (buffer[fd] && !ft_strchr(buffer[fd], '\n')))
		buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	content = get_line(buffer[fd]);
	if (!content)
		return (ft_free(&buffer[fd]));
	buffer[fd] = clean_buf(buffer[fd]);
	return (content);
}
