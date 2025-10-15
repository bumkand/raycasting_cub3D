/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:49:51 by marcel            #+#    #+#             */
/*   Updated: 2025/10/15 19:50:25 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    handle_mouse_rotation(t_game *game)
{
    int32_t mouse_x;
    int32_t mouse_y;
    int     delta_x;
    double  rotation_angle;

    mlx_get_mouse_pos(game->mlx, &mouse_x, &mouse_y);
    delta_x = mouse_x - game->player.last_mouse_x;
    game->player.last_mouse_x = mouse_x;
    
    if (delta_x == 0)
        return;
    
    rotation_angle = delta_x * 0.002;
    rotate_vectors(game, rotation_angle);
}
