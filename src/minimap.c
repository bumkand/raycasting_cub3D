/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:24:40 by marcel            #+#    #+#             */
/*   Updated: 2025/10/15 17:59:30 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_framebuffer(t_game *game)
{
	ft_memset(game->game_img->pixels, 0,
		game->game_img->width * game->game_img->height * sizeof(int32_t));
}

void	draw_square(t_game *game, t_square sq)
{
	int	x;
	int	y;

	y = -1;
	while (++y < sq.size)
	{
		x = -1;
		while (++x < sq.size)
			mlx_put_pixel(game->game_img, sq.x + x, sq.y + y, sq.color);
	}
}

void	draw_player(t_game *game)
{
	int			player_screen_x;
	int			player_screen_y;
	t_square	sq;
	t_render	render;

	player_screen_x = game->player.pos_x * MINIMAP_TILE_SIZE;
	player_screen_y = game->player.pos_y * MINIMAP_TILE_SIZE;
	sq.x = player_screen_x - (PLAYER_SIZE / 2);
	sq.y = player_screen_y - (PLAYER_SIZE / 2);
	sq.size = PLAYER_SIZE;
	sq.color = C_RED;
	draw_square(game, sq);
	render.camera_x = 0;
	draw_single_ray(game, &render, player_screen_x, player_screen_y);
}

void	draw_minimap(t_game *game)
{
	draw_minimap_tiles(game);
	draw_player(game);
}
