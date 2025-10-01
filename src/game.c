/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 21:39:34 by marcel            #+#    #+#             */
/*   Updated: 2025/10/01 20:54:26 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void setup_hooks(t_game *game)
{
    (void) game;
    // mlx_loop_hook(game->mlx, update_player_position, game);
    // mlx_loop_hook(game->mlx, draw_ray, game);
}

void game_loop(t_game *game)
{
    setup_hooks(game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);  // Cleanup when loop ends
}
