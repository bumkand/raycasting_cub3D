/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:24:25 by jakand            #+#    #+#             */
/*   Updated: 2025/10/16 11:17:12 by mmravec          ###   ########.fr       */
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

void	free_loaded_textures(t_game *game)
{
	if (game->text && game->text->north)
		mlx_delete_texture(game->text->north);
	if (game->text && game->text->south)
		mlx_delete_texture(game->text->south);
	if (game->text && game->text->west)
		mlx_delete_texture(game->text->west);
	if (game->text && game->text->east)
		mlx_delete_texture(game->text->east);
	if (game->text)
		free(game->text);
}
