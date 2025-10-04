/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:56:08 by marcel            #+#    #+#             */
/*   Updated: 2025/10/04 09:48:06 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Vrací 1, pokud je na souřadnicích zeď, jinak 0
int is_wall(t_game *game, double x, double y)
{
    int map_x;
    int map_y;

    // Převedeme double souřadnice na indexy v poli
    map_x = (int)x;
    map_y = (int)y;

    // Bezpečnostní kontrola, abychom se nepodívali mimo mapu
    if (map_x < 0 || map_x >= game->width || map_y < 0 || map_y >= game->height)
        return (1); // Chovej se k prostoru mimo mapu jako ke zdi

    // Kontrola samotného znaku v mapě
    if (game->map[map_y][map_x] == '1')
        return (1);
        
    return (0);
}

void handle_player_input(t_game *game)
{
    double	old_dir_x;
    double	old_plane_x;
        
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);

    double new_x = game->player.pos_x;
    double new_y = game->player.pos_y;

    // Calculate new position based on key presses
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        new_x += game->player.dir_x * PLAYER_SPEED;
        new_y += game->player.dir_y * PLAYER_SPEED;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        new_x -= game->player.dir_x * PLAYER_SPEED;
        new_y -= game->player.dir_y * PLAYER_SPEED;
    }

    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        new_x -= game->player.plane_x * PLAYER_SPEED;
        new_y -= game->player.plane_y * PLAYER_SPEED;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        new_x += game->player.plane_x * PLAYER_SPEED;
        new_y += game->player.plane_y * PLAYER_SPEED;
    }

    // --- ROTACE ---
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)) {
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROTATION_SPEED) - game->player.dir_y * sin(-ROTATION_SPEED);
        game->player.dir_y = old_dir_x * sin(-ROTATION_SPEED) + game->player.dir_y * cos(-ROTATION_SPEED);
        old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROTATION_SPEED) - game->player.plane_y * sin(-ROTATION_SPEED);
        game->player.plane_y = old_plane_x * sin(-ROTATION_SPEED) + game->player.plane_y * cos(-ROTATION_SPEED);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)) {
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED) - game->player.dir_y * sin(ROTATION_SPEED);
        game->player.dir_y = old_dir_x * sin(ROTATION_SPEED) + game->player.dir_y * cos(ROTATION_SPEED);
        old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED) - game->player.plane_y * sin(ROTATION_SPEED);
        game->player.plane_y = old_plane_x * sin(ROTATION_SPEED) + game->player.plane_y * cos(ROTATION_SPEED);
    }
        
    // Zkontroluj kolizi pro osu X
    if (!is_wall(game, new_x + COLLISION_RADIUS, game->player.pos_y + COLLISION_RADIUS) && \
        !is_wall(game, new_x + COLLISION_RADIUS, game->player.pos_y - COLLISION_RADIUS) && \
        !is_wall(game, new_x - COLLISION_RADIUS, game->player.pos_y + COLLISION_RADIUS) && \
        !is_wall(game, new_x - COLLISION_RADIUS, game->player.pos_y - COLLISION_RADIUS))
    {
        game->player.pos_x = new_x;
    }

    // Zkontroluj kolizi pro osu Y
    if (!is_wall(game, game->player.pos_x + COLLISION_RADIUS, new_y + COLLISION_RADIUS) && \
        !is_wall(game, game->player.pos_x + COLLISION_RADIUS, new_y - COLLISION_RADIUS) && \
        !is_wall(game, game->player.pos_x - COLLISION_RADIUS, new_y + COLLISION_RADIUS) && \
        !is_wall(game, game->player.pos_x - COLLISION_RADIUS, new_y - COLLISION_RADIUS))
    {
        game->player.pos_y = new_y;
    }
}

int check_collision(t_game *game, double new_x, double new_y)
{
    (void)  game;
    // Basic boundary checking (window bounds for now)
    if (new_x < 0 || new_x > (WIDTH - 32))
        return (0);
    if (new_y < 0 || new_y > (HEIGHT - 32))
        return (0);
    if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
        return (0);
    if (game->map[(int)new_y][(int)new_x] == '1' || game->map[(int)new_y][(int)new_x] == ' ')
        return (0);
    // TODO: Add map collision when map is ready
    // For now, just check window boundaries
    return (1); // Movement is valid
}
