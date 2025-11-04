/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:40:06 by jaandras          #+#    #+#             */
/*   Updated: 2025/10/16 11:28:35 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	line = ft_calloc((ft_strlen(buffer) - i), sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*ft_save_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_line(int fd, char *buffer)
{
	char	*line;
	int		read_char;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	line = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	read_char = 1;
	while (read_char > 0)
	{
		read_char = read(fd, line, BUFFER_SIZE);
		if (read_char == -1)
			return (free(buffer), free(line), NULL);
		line[read_char] = '\0';
		buffer = ft_free_join(buffer, line);
		if (!buffer)
			return (free(line), NULL);
		if (ft_strchr(line, '\n'))
			break ;
	}
	free(line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*read_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_get_line(fd, buffer);
	if (!buffer)
		return (NULL);
	read_line = ft_save_line(buffer);
	buffer = ft_next_line(buffer);
	return (read_line);
}
