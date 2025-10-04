/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:51:57 by marcel            #+#    #+#             */
/*   Updated: 2025/10/04 22:52:51 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// V souboru render.c

void draw_floor_and_ceiling(t_game *game)
{
    int x, y;
    int ceiling_color;
    int floor_color;

    // Připravíme si barvy jen jednou před cykly
    ceiling_color = get_rgba(game->color_c[0], game->color_c[1], game->color_c[2], 255);
    floor_color = get_rgba(game->color_f[0], game->color_f[1], game->color_f[2], 255);

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            if (y < HEIGHT / 2)
                mlx_put_pixel(game->game_img, x, y, ceiling_color);
            else
                mlx_put_pixel(game->game_img, x, y, floor_color);
        }
    }
}