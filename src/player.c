/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:56:08 by marcel            #+#    #+#             */
/*   Updated: 2025/10/01 20:51:20 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void update_player_position(void *param)
// {
//     t_game *game = (t_game *)param;

//     if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
//         mlx_close_window(game->mlx);

//     int new_x = game->player_x;
//     int new_y = game->player_y;

//     // Calculate new position based on key presses
//     if (mlx_is_key_down(game->mlx, MLX_KEY_W))
//     {
//         new_x += cos(game->player_angle) * MOVE_SPEED;
//         new_y += sin(game->player_angle) * MOVE_SPEED;
//     }
//     if (mlx_is_key_down(game->mlx, MLX_KEY_S))
//     {
//         new_x -= cos(game->player_angle) * MOVE_SPEED;
//         new_y -= sin(game->player_angle) * MOVE_SPEED;
//     }

//     if (mlx_is_key_down(game->mlx, MLX_KEY_A))
//     {
//         new_x += cos(game->player_angle - M_PI/2) * MOVE_SPEED;
//         new_y += sin(game->player_angle - M_PI/2) * MOVE_SPEED;
//     }
//     if (mlx_is_key_down(game->mlx, MLX_KEY_D))
//     {
//         new_x += cos(game->player_angle + M_PI/2) * MOVE_SPEED;
//         new_y += sin(game->player_angle + M_PI/2) * MOVE_SPEED;
//     }

//     if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
//         game->player_angle -= 0.05;  // Rotace vlevo
//     if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
//         game->player_angle += 0.05;  // Rotace vpravo

//     // Check if movement is valid before applying
//     if (check_collision(game, new_x, new_y))
//     {
//         game->player_x = new_x;
//         game->player_y = new_y;
//         game->player_img->instances[0].x = game->player_x;
//         game->player_img->instances[0].y = game->player_y;
//     }
// }

// int check_collision(t_game *game, int new_x, int new_y)
// {
//     (void)  game;
//     // Basic boundary checking (window bounds for now)
//     if (new_x < 0 || new_x > (WIDTH - 32))
//         return (0);
//     if (new_y < 0 || new_y > (HEIGHT - 32))
//         return (0);

//     // TODO: Add map collision when map is ready
//     // For now, just check window boundaries
//     return (1); // Movement is valid
// }
