/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:24:25 by jakand            #+#    #+#             */
/*   Updated: 2025/09/23 17:25:57 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_game *game)
{
	if (game->text_no)
		free(game->text_no);
	if (game->text_so)
		free(game->text_so);
	if (game->text_we)
		free(game->text_we);
	if (game->text_ea)
		free(game->text_ea);
	game->text_no = NULL;
	game->text_so = NULL;
	game->text_we = NULL;
	game->text_ea = NULL;
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map && game->map[i])
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		if (game->map)
			free(game->map);
	}
}

void	free_cub(char **cub_file)
{
	int	y;

	y = 0;
	while (cub_file[y])
	{
		free(cub_file[y]);
		y++;
	}
	if (cub_file)
		free(cub_file);
}
