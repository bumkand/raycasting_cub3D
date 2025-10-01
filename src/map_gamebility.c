/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gamebility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:43:04 by jakand            #+#    #+#             */
/*   Updated: 2025/09/30 19:43:15 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_of_map(t_game *game)
{
	int		y;
	char	**map_copy;

	map_copy = malloc((game->height + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	y = 0;
	while (game->map[y])
	{
		map_copy[y] = ft_strdup(game->map[y]);
		if (!map_copy[y])
		{
			while (y >= 0)
			{
				free(map_copy[y]);
				y--;
			}
			free(map_copy);
			return (NULL);
		}
		y++;
	}
	map_copy[y] = NULL;
	return (map_copy);
}

void	find_start_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'W' || game->map[y][x] == 'E')
			{
				game->start_x = x;
				game->start_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	check_first_last_line(char **map_copy, int x, int *y, t_game *game)
{
	while (map_copy[*y][x])
	{
		if (map_copy[*y][x] != '1' && map_copy[*y][x] != ' ')
			return (1);
		x++;
	}
	x = 0;
	while (map_copy[game->height - 1][x])
	{
		if (map_copy[game->height - 1][x] != '1'
			&& map_copy[game->height - 1][x] != ' ')
			return (1);
		x++;
	}
	(*y)++;
	return (0);
}

int	check_other_lines(char **map_copy, int *x, int y)
{
	if (*x == 0 && map_copy[y][*x] == '0')
		return (1);
	if (map_copy[y][*x] == '0')
	{
		if ((map_copy[y + 1][*x] != '0' && map_copy[y + 1][*x] != '1')
		|| (map_copy[y - 1][*x] != '0' && map_copy[y - 1][*x] != '1')
		|| (map_copy[y][*x + 1] != '0' && map_copy[y][*x + 1] != '1')
		|| (map_copy[y][*x - 1] != '0' && map_copy[y][*x - 1] != '1'))
			return (1);
	}
	(*x)++;
	return (0);
}


int	check_gamebility(char **map_copy, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map_copy[y])
	{
		x = 0;
		if (y == 0)
		{
			if (check_first_last_line(map_copy, x, &y, game))
				return (printf("Walls or spaces problem in the map\n"), 1);
			continue ;
		}
		while (map_copy[y][x])
		{
			if (check_other_lines(map_copy, &x, y))
				return (printf("Walls or spaces problem in the map\n"), 1);
		}
		y++;
	}
	return (0);
}
