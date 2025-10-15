/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:44:19 by marcel            #+#    #+#             */
/*   Updated: 2025/10/15 19:38:54 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_textures(t_game *game)
{
	game->text = ft_calloc(1, sizeof(t_texture));
	if (!game->text)
		return (1);
	game->text->north = mlx_load_png(game->text_no);
	game->text->south = mlx_load_png(game->text_so);
	game->text->west = mlx_load_png(game->text_we);
	game->text->east = mlx_load_png(game->text_ea);
	if (!game->text->north || !game->text->south
		|| !game->text->west || !game->text->east)
	{
		if (game->text->north)
			mlx_delete_texture(game->text->north);
		if (game->text->south)
			mlx_delete_texture(game->text->south);
		if (game->text->west)
			mlx_delete_texture(game->text->west);
		if (game->text->east)
			mlx_delete_texture(game->text->east);
		return (free(game->text), 1);
	}
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
	{
		return (ft_error("MLX initialization failed"));
	}
	game->game_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->game_img)
	{
		mlx_terminate(game->mlx);
		return (ft_error("Failed to create MLX image"));
	}
	if (mlx_image_to_window(game->mlx, game->game_img, 0, 0) == -1)
	{
		mlx_terminate(game->mlx);
		return (ft_error("Failed to display image in window"));
	}
	if (get_textures(game))
	{
		mlx_terminate(game->mlx);
		return (ft_error("Failed to save wall textures"));
	}
	return (EXIT_SUCCESS);
}
