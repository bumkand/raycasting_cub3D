/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:24:40 by marcel            #+#    #+#             */
/*   Updated: 2025/10/04 22:26:40 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void clear_framebuffer(t_game *game)
{
    ft_memset(game->game_img->pixels, 0,
        game->game_img->width * game->game_img->height * sizeof(int32_t));
}

void draw_square(t_game *game, int start_x, int start_y, int size, int color)
{
    int x, y;

    x = -1;
    y = -1;
    while (++y < size)
    {
        x = -1;
        while (++x < size)
        {
            mlx_put_pixel(game->game_img, start_x + x, start_y + y, color);
        }
    }
}
void draw_player(t_game *game)
{
    int i;
    int player_screen_x = game->player.pos_x * MINIMAP_TILE_SIZE;
    int player_screen_y = game->player.pos_y * MINIMAP_TILE_SIZE;
    int ray_x;
    int ray_y;
    // Kreslíme čtverec tak, aby jeho střed byl na pozici hráče
    draw_square(game, player_screen_x - (PLAYER_SIZE / 2), 
                      player_screen_y - (PLAYER_SIZE / 2), 
                      PLAYER_SIZE, C_RED);

    // Paprsek směru teď bude také vycházet ze středu
    i = -1;
    while (++i < 25) {
        ray_x = player_screen_x + game->player.dir_x * i;
        ray_y = player_screen_y + game->player.dir_y * i;
        if (ray_x < 0 || ray_x >= WIDTH || ray_y < 0 || ray_y >= HEIGHT)
            break; // Pokud paprsek vyjde mimo obrazovku, přerušíme smyčku
        mlx_put_pixel(game->game_img, ray_x, ray_y, C_GREEN);
    }
}

void draw_minimap(t_game *game)
{
    int     x;
    int     y;

    x = -1;
    y = -1;
    while (++y < game->height) {
        x = -1;
        while (++x < game->width)
        {
            if (game->map[y] && x < (int)ft_strlen(game->map[y]))
            {
                if (game->map[y][x] == '1' || game->map[y][x] == ' ')
                    draw_square(game, x * MINIMAP_TILE_SIZE, y * MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE,
                        C_WHITE);
                else if (game->map[y][x] == '0' || game->map[y][x] == 'N' ||
                         game->map[y][x] == 'S' || game->map[y][x] == 'W' ||
                         game->map[y][x] == 'E')
                {
                    draw_square(game, x * MINIMAP_TILE_SIZE, y * MINIMAP_TILE_SIZE,
                        MINIMAP_TILE_SIZE, C_GREY);
                }
            }
        }
    }
    draw_player(game);
}