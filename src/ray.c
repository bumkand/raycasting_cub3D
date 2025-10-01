/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 22:53:13 by marcel            #+#    #+#             */
/*   Updated: 2025/09/20 23:07:43 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_ray(void *param)
{
    t_game *game = (t_game *)param;
    
    // Vymaž předchozí ray
    uint32_t y = 0;
    while (y < game->ray_img->height)
    {
        uint32_t x = 0;
        while (x < game->ray_img->width)
        {
            mlx_put_pixel(game->ray_img, x, y, 0x00000000);
            x++;
        }
        y++;
    }
    
    // Nakresli nový ray
    int ray_length = 100;
    // Odstraň end_x a end_y - nepoužívají se
    
    // Jednoduchá čára
    int i = 0;
    while (i <= ray_length)
    {
        int x = game->player_x + 16 + (int)(cos(game->player_angle) * i);
        int y = game->player_y + 16 + (int)(sin(game->player_angle) * i);
        
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            mlx_put_pixel(game->ray_img, x, y, 0x00FF00FF);
        i++;
    }
}