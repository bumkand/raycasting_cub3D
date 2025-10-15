/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:46:57 by marcel            #+#    #+#             */
/*   Updated: 2025/10/15 19:54:22 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_vectors(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

void	handle_rotation(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_vectors(game, -ROTATION_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_vectors(game, ROTATION_SPEED);
}

void	apply_movement(t_game *game, double new_x, double new_y)
{
	double	radius;

	radius = (double)PLAYER_SIZE / (double)MINIMAP_TILE_SIZE / 2.0;
	if (!is_wall(game, new_x + radius, game->player.pos_y + radius)
		&& !is_wall(game, new_x + radius, game->player.pos_y - radius)
		&& !is_wall(game, new_x - radius, game->player.pos_y + radius)
		&& !is_wall(game, new_x - radius, game->player.pos_y - radius))
		game->player.pos_x = new_x;
	if (!is_wall(game, game->player.pos_x + radius, new_y + radius)
		&& !is_wall(game, game->player.pos_x + radius, new_y - radius)
		&& !is_wall(game, game->player.pos_x - radius, new_y + radius)
		&& !is_wall(game, game->player.pos_x - radius, new_y - radius))
		game->player.pos_y = new_y;
}
