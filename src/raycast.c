/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 22:53:13 by marcel            #+#    #+#             */
/*   Updated: 2025/10/06 21:33:14 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_hit perform_dda(t_game *game, double ray_dir_x, double ray_dir_y)
{
    t_hit hit;
    int map_x;
    int map_y;
    double delta_dist_x;
    double delta_dist_y;
    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;
    int side;
    int hit_found;

    map_x = (int)game->player.pos_x;
    map_y = (int)game->player.pos_y;

    // Výpočet delta_dist_x a delta_dist_y bez ternárneho operátora
    if (ray_dir_x == 0)
        delta_dist_x = 1e30;
    else
        delta_dist_x = fabs(1 / ray_dir_x);

    if (ray_dir_y == 0)
        delta_dist_y = 1e30;
    else
        delta_dist_y = fabs(1 / ray_dir_y);

    // Určenie smeru kroku a počiatočnej vzdialenosti
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
    }

    // DDA algoritmus – krokovanie po mapových štvorcoch
    hit_found = 0;
    while (hit_found == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        if (game->map[map_y][map_x] == '1')
            hit_found = 1;
    }

    // Výpočet presnej vzdialenosti k stene
    hit.map_x = map_x;
    hit.map_y = map_y;
    hit.side = side;
    if (side == 0)
        hit.dist = side_dist_x - delta_dist_x;
    else
        hit.dist = side_dist_y - delta_dist_y;

    return (hit);
}
