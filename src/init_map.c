/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:37:37 by jakand            #+#    #+#             */
/*   Updated: 2025/09/30 19:47:05 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_count_lines(char **cub_map, int *end, int *i)
{
	while (cub_map[*end])
	{
		if (check_free_line(cub_map[*end]))
		{
			break ;
		}
		(*end)++;
	}
	if (cub_map[*end] && check_free_line(cub_map[*end]))
	{
		(*i) = *end;
		while (cub_map[*i])
		{
			if (check_free_line(cub_map[*i]) == 0)
				return (printf("Chars under the map\n"), 1);
			(*i)++;
		}
	}
	return (0);
}

int	check_count_width(char **cub_map, int *len, t_game *game, int *i)
{
	int	end;

	end = *len;
	while (*i < end)
	{
		if (check_free_line(cub_map[*i]))
			break ;
		*len = count_length(cub_map[*i]);
		if (*len > game->width)
			game->width = *len;
		(*i)++;
	}
	return (0);
}

int	alloc_map(t_game *game, char **cub_map, int i, int start)
{
	int	end;

	game->map = malloc((game->height + 1) * sizeof(char *));
	if (!game->map)
		return (1);
	end = i;
	i = start;
	while (i < end)
	{
		game->map[i - start] = ft_strdup_with_spaces(cub_map[i], game);
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

int	init_game_map(char **cub_map, int start, t_game *game)
{
	int	end;
	int	len;
	int	i;

	end = start;
	if (check_count_lines(cub_map, &end, &i))
		return (1);
	game->height = end - start;
	i = start;
	game->width = 0;
	len = end;
	if (check_count_width(cub_map, &len, game, &i))
		return (1);
	if (alloc_map(game, cub_map, i, start))
		return (1);
	return (0);
}
