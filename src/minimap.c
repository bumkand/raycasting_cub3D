/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:24:40 by marcel            #+#    #+#             */
/*   Updated: 2025/10/05 16:53:59 by jakand           ###   ########.fr       */
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

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / MINIMAP_SCALE;
	y = py / MINIMAP_SCALE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void draw_player(t_game *game)
{
    int i;
	int	r;
    int player_screen_x;
    int player_screen_y;
    int ray_x;
    int ray_y;

	player_screen_x = game->player.pos_x * MINIMAP_SCALE;
    player_screen_y = game->player.pos_y * MINIMAP_SCALE;
    // Kreslíme čtverec tak, aby jeho střed byl na pozici hráče
    draw_square(game, player_screen_x - (PLAYER_SIZE / 2), 
                      player_screen_y - (PLAYER_SIZE / 2), 
                      PLAYER_SIZE, C_RED);

    // Paprsek
	r = 0;
	int	num_rays = WIDTH / 4;
	while (r < num_rays)
	{
		double camera_x = 2 * r / (double)num_rays - 1;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		i = 0;
    	while (1) 
		{
    	    ray_x = player_screen_x + ray_dir_x * i;
    	    ray_y = player_screen_y + ray_dir_y * i;
			if (touch(ray_x, ray_y, game))
				break ;
    	    if (ray_x < 0 || ray_x >= WIDTH || ray_y < 0 || ray_y >= HEIGHT)
    	        break; // Pokud paprsek vyjde mimo obrazovku, přerušíme smyčku
    	    mlx_put_pixel(game->game_img, ray_x, ray_y, C_GREEN);
			i++;
    	}
		r++;
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
                    draw_square(game, x * MINIMAP_SCALE, y * MINIMAP_SCALE, MINIMAP_SCALE,
                        C_WHITE);
                else if (game->map[y][x] == '0' || game->map[y][x] == 'N' ||
                         game->map[y][x] == 'S' || game->map[y][x] == 'W' ||
                         game->map[y][x] == 'E')
                {
                    draw_square(game, x * MINIMAP_SCALE, y * MINIMAP_SCALE,
                        MINIMAP_SCALE, C_GREY);
                }
            }
        }
    }
    draw_player(game);
}
