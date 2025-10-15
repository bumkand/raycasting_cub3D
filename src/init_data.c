/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:17:10 by jakand            #+#    #+#             */
/*   Updated: 2025/10/15 18:30:16 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_char(char *line, t_game *game, int y)
{
	static int	count;

	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != ' ' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W' && *line != '\n')
			return (printf("Wrong char in the map\n"), 1);
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			count++;
		line++;
	}
	if (game->height - 1 == y && (count > 1 || count == 0))
		return (printf("Wrong amount starting position\n"), 1);
	return (0);
}

int	map_text_color(char **cub_file, int *y, t_game *game)
{
	if (check_free_line(cub_file[*y]))
		return ((*y)++, 0);
	if (cub_file[*y] && game->color_c[0] >= 0 && game->color_f[0] >= 0)
	{
		if (init_game_map(cub_file, *y, game))
			return (printf("Map init error\n"),
				free_cub(cub_file), free_texture(game), 1);
	}
	while (cub_file[*y] && game->color_c[0] >= 0 && game->color_f[0] >= 0)
	{
		if (check_free_line(cub_file[*y]))
		{
			(*y)++;
			break ;
		}
		(*y)++;
	}
	if (cub_file[*y] && init_texture_color(cub_file[*y], game))
		return (free_cub(cub_file), 1);
	if (cub_file[*y])
		(*y)++;
	return (0);
}

int	map_gamebility(t_game *game)
{
	char	**map_copy;
	int		y;

	y = 0;
	while (game->map[y])
	{
		if (check_map_char(game->map[y], game, y))
			return (1);
		y++;
	}
	map_copy = copy_of_map(game);
	if (map_copy == NULL)
		return (1);
	find_start_position(game);
	if (check_map_walls(map_copy, game))
		return (free_cub(map_copy), 1);
	free_cub(map_copy);
	return (0);
}

int	check_struct(t_game *game)
{
	if (!game->text_no
		|| !game->text_so
		|| !game->text_we
		|| !game->text_ea
		|| game->color_c[0] == -1
		|| game->color_c[1] == -1
		|| game->color_c[2] == -1
		|| game->color_f[0] == -1
		|| game->color_f[1] == -1
		|| game->color_f[2] == -1
		|| !game->map)
		return (1);
	return (0);
}

int	init_data(t_game *game, char *map_path)
{
	int		fd;
	int		y;
	char	*line;
	char	**cub_file;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_error("Could not open map file"));
	line = get_next_line(fd);
	if (get_cub_file(&cub_file, fd, line, map_path))
		return (ft_error(".cub File Array Error"));
	y = 0;
	while (cub_file[y])
	{
		if (map_text_color(cub_file, &y, game))
			return (1);
	}
	free_cub(cub_file);
	if (game->map && map_gamebility(game))
		return (1);
	if (check_struct(game))
		return (printf("Problem with .cub file\n"), 1);
	return (0);
}
