/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 21:17:53 by jakand            #+#    #+#             */
/*   Updated: 2025/09/24 17:49:09 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	choose_texture_color(char *line, int *x, t_game *game)
{
	int	i;

	i = *x;
	if (texture_no_so(line, x, game))
		return (1);
	if (texture_we_ea(line, x, game))
		return (1);
	if (color_c_f(line, x, game))
		return (1);
	if (i == *x)
	{
		while (line[*x] != '\n' && line[*x] != '\0')
		{
			if (line[*x] != ' ')
				return (printf("Forbidden characters in .cub\n"), 1);
		}
	}
	return (0);
}

int	init_texture_color(char *line, t_game *game)
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
