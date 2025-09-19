/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:19:03 by jakand            #+#    #+#             */
/*   Updated: 2025/09/18 22:29:41 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	count_lines(int height, char *line, int fd)
{
	height = 0;
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	lines_length(char ****cub_file, char *line, int height)
{
	int	lenght;
	int	j;

	lenght = 0;
	while (line[lenght] != '\n' && line[lenght])
		lenght++;
	(**cub_file)[height] = malloc((lenght + 1) * sizeof(char));
	if (!(**cub_file)[height])
		return (free(line), 1);
	j = 0;
	while (j < lenght)
	{
		(**cub_file)[height][j] = line[j];
		j++;
	}
	(**cub_file)[height][j] = '\0';
	free(line);
	return (0);
}

int	get_cub_file(char ***cub_file, int fd, char *line)
{
	int	height;

	height = count_lines(0, line, fd);
	*cub_file = malloc((height + 1) * sizeof(char *));
	if (!*cub_file)
		return (1);
	fd = open("maps/valid_map_1.cub", O_RDONLY);
	line = get_next_line(fd);
	height = 0;
	while (line)
	{
		if (lines_length(&cub_file, line, height))
			return (close(fd), 1);
		line = get_next_line(fd);
		height++;
	}
	(*cub_file)[height] = NULL;
	close(fd);
	return (0);
}
