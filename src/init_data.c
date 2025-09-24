/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:17:10 by jakand            #+#    #+#             */
/*   Updated: 2025/09/24 17:36:40 by jakand           ###   ########.fr       */
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

int	check_free_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	count_length(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc((count_length(s) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < count_length(s))
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i] = '\n';
	else
		line[i] = '\0';
	return (line);
}

int	init_game_map(char **cub_map, int start, t_game *game)
{
	int	end;
	int	len;
	int	i;

	end = start;
	while (cub_map[end])
	{
		if (check_free_line(cub_map[end]))
		{
			break ;
		}
		end++;
	}
	if (cub_map[end] && check_free_line(cub_map[end]))
	{
		i = end;
		while (cub_map[i])
		{
			if (check_free_line(cub_map[i]) == 0)
				return (printf("Chars under the map\n"), 1);
			i++;
		}
	}
	game->height = end - start;
	i = start;
	game->width = 0;
	while (i < end)
	{
		if (check_free_line(cub_map[i]))
		{
			break ;
		}
		len = count_length(cub_map[i]);
		if (len > game->width)
			game->width = len;
		i++;
	}
	game->map = malloc((game->height + 1) * sizeof(char *));
	if (!game->map)
		return (1);
	end = i;
	i = start;
	while (i < end)
	{
		game->map[i - start] = ft_strdup(cub_map[i]);
		if (!game->map[i - start])
		{
			while (i >= start)
			{
				free(game->map[i - start]);
				i--;
			}
			free(game->map);
			return (1);
		}
		i++;
	}
	game->map[game->height] = NULL;
	return (0);
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
		if (check_free_line(cub_file[y]))
		{
			y++;
			continue ;
		}
		if (cub_file[y] && game->color_c[0] >= 0 && game->color_f[0] >= 0)
		{
			if (init_game_map(cub_file, y, game))
				return (printf("Map init error\n"), free_cub(cub_file), free_texture(game), 1);
		}
		while (cub_file[y] && game->color_c[0] >= 0 && game->color_f[0] >= 0)
		{
			if (check_map_char(cub_file[y]))
				return (free_cub(cub_file), free_texture(game), free_map(game), 1);
			if (check_free_line(cub_file[y]))
			{
				y++;
				break ;
			}
			//printf("%s\n", cub_file[y]);
			y++;
		}
		//printf("%s\n", cub_file[y]);
		if (cub_file[y] && init_texture_color(cub_file[y], game))
			return (free_cub(cub_file), 1);
		if (cub_file[y])
			y++;
	}
	printf("NO texture = %s\nSO texture = %s\nWE texture = %s\nEA texture = %s\n", game->text_no, game->text_so, game->text_we, game->text_ea);
	printf("F color = %i,%i,%i\nC color = %i,%i,%i\n", game->color_f[0], game->color_f[1], game->color_f[2], game->color_c[0], game->color_c[1], game->color_c[2]);
	//printf(" game height = %i\n game width = %i\n", game->height, game->width);
	free_cub(cub_file);
	y = 0;
	while (game->map[y])
	{
		printf("%s\n", game->map[y]);
		y++;
	}
	return (0);
}
