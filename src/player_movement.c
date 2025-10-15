/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:46:57 by marcel            #+#    #+#             */
/*   Updated: 2025/10/15 19:07:20 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_vectors(t_game *game, double angle)
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
	if (!is_wall(game, new_x + COLLISION_RADIUS,
			game->player.pos_y + COLLISION_RADIUS)
		&& !is_wall(game, new_x + COLLISION_RADIUS,
			game->player.pos_y - COLLISION_RADIUS)
		&& !is_wall(game, new_x - COLLISION_RADIUS,
			game->player.pos_y + COLLISION_RADIUS)
		&& !is_wall(game, new_x - COLLISION_RADIUS,
			game->player.pos_y - COLLISION_RADIUS))
		game->player.pos_x = new_x;
	if (!is_wall(game, game->player.pos_x + COLLISION_RADIUS,
			new_y + COLLISION_RADIUS)
		&& !is_wall(game, game->player.pos_x + COLLISION_RADIUS,
			new_y - COLLISION_RADIUS)
		&& !is_wall(game, game->player.pos_x - COLLISION_RADIUS,
			new_y + COLLISION_RADIUS)
		&& !is_wall(game, game->player.pos_x - COLLISION_RADIUS,
			new_y - COLLISION_RADIUS))
		game->player.pos_y = new_y;
}
