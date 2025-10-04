/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 21:39:34 by marcel            #+#    #+#             */
/*   Updated: 2025/10/04 22:57:24 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void setup_hooks(t_game *game)
{ 
    mlx_loop_hook(game->mlx, game_tick, game);
    
}

void game_loop(t_game *game)
{
    setup_hooks(game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);  // Cleanup when loop ends
}


void game_tick(void *param)
{
    t_game *game = (t_game *)param;

    // 1. KROK: AKTUALIZACE LOGIKY
    handle_player_input(game);

    // 2. KROK: VYKRESLENÍ VŠEHO
    clear_framebuffer(game);
    draw_floor_and_ceiling(game); // Krok 1
    cast_rays(game);              // Krok 2
    draw_minimap(game);           // Krok 3
}