/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:17:10 by jakand            #+#    #+#             */
/*   Updated: 2025/09/22 22:49:04 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_char(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != ' ' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W' && *line != '\n')
			return (printf("Wrong char in the map\n"), 1);
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			count++;
		if (count > 1)
			return (printf("More than 1 starting position\n"), 1);
		line++;
	}
	return (0);
}

int	init_texture_color_map(char *line, t_game *game)
{
	int	x;

	x = 0;
	while (line[x] != '\n' && line[x] != '\0')
	{
		while (line[x] == ' ')
			x++;
		if (line[x] >= 9 && line[x] <= 13)
		{
			free_texture(game);
			return (printf("Whitespace in file\n"), 1);
		}
		if (choose_texture_color(line, &x, game))
			return (free_texture(game), 1);
		while (line[x] != '\0' && line[x] != '\n')
			x++;
	}
	return (0);
}

int	check_line(char *line, int *y)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	(*y)++;
	return (1);
}

int	init_data(t_game *game)
{
	int		fd;
	int		y;
	char	*line;
	char	**cub_file;

	fd = open("maps/valid_map_1.cub", O_RDONLY);
	line = get_next_line(fd);
	if (get_cub_file(&cub_file, fd, line))
		return (printf(".cub File Array Error\n"), 1);
	y = 0;
	while (cub_file[y])
	{
		if (check_line(cub_file[y], &y))
			continue ;
		while (cub_file[y] && game->color_c[0] >= 0 && game->color_f[0] >= 0)
		{
			if (check_map_char(cub_file[y]))
				return (free_cub(cub_file), free_texture(game), 1);
			if (check_line(cub_file[y], &y))
				break ;
			printf("%s\n", cub_file[y]);
			y++;
		}
		printf("%s\n", cub_file[y]);
		if (cub_file[y] && init_texture_color_map(cub_file[y], game))
			return (free_cub(cub_file), 1);
		if (cub_file[y])
			y++;
	}
	printf("NO texture = %s\nSO texture = %s\nWE texture = %s\nEA texture = %s\n", game->text_no, game->text_so, game->text_we, game->text_ea);
	printf("F color = %i,%i,%i\nC color = %i,%i,%i\n", game->color_f[0], game->color_f[1], game->color_f[2], game->color_c[0], game->color_c[1], game->color_c[2]);
	fd = open("maps/valid_map_1.cub", O_RDONLY);
	game->height = get_height(fd);
	close(fd);
	fd = open("maps/valid_map_1.cub", O_RDONLY);
	game->width = get_width(fd);
	close(fd);
	printf(" game height = %i\n game width = %i\n", game->height, game->width);
	free_cub(cub_file);
	return (0);
}
