/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:56:08 by marcel            #+#    #+#             */
/*   Updated: 2025/10/15 19:51:03 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_movement(t_game *game, double *new_x, double *new_y)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		*new_x += game->player.dir_x * PLAYER_SPEED;
		*new_y += game->player.dir_y * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		*new_x -= game->player.dir_x * PLAYER_SPEED;
		*new_y -= game->player.dir_y * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		*new_x -= game->player.plane_x * PLAYER_SPEED;
		*new_y -= game->player.plane_y * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		*new_x += game->player.plane_x * PLAYER_SPEED;
		*new_y += game->player.plane_y * PLAYER_SPEED;
	}
}

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->width
		|| map_y < 0 || map_y >= game->height)
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	handle_player_input(t_game *game)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	new_x = game->player.pos_x;
	new_y = game->player.pos_y;
	handle_movement(game, &new_x, &new_y);
	handle_rotation(game);
    handle_mouse_rotation(game);
	apply_movement(game, new_x, new_y);
}
