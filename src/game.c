/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 21:39:34 by marcel            #+#    #+#             */
/*   Updated: 2025/10/16 10:43:05 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, game_tick, game);
	mlx_cursor_hook(game->mlx, &mouse_hook, game);
}

void	game_loop(t_game *game)
{
	setup_hooks(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

void	game_tick(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_player_input(game);
	clear_framebuffer(game);
	draw_3d_view(game);
	draw_minimap(game);
}
