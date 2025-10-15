/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:46:09 by marcel            #+#    #+#             */
/*   Updated: 2025/10/15 17:59:02 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tile(t_game *game, int x, int y)
{
	t_square	sq;

	sq.x = x * MINIMAP_TILE_SIZE;
	sq.y = y * MINIMAP_TILE_SIZE;
	sq.size = MINIMAP_TILE_SIZE;
	if (game->map[y][x] == '1' || game->map[y][x] == ' ')
		sq.color = C_WHITE;
	else
		sq.color = C_GREY;
	draw_square(game, sq);
}

void	draw_minimap_tiles(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->map[y] && x < (int)ft_strlen(game->map[y]))
			{
				if (game->map[y][x] == '1' || game->map[y][x] == ' '
					|| game->map[y][x] == '0' || game->map[y][x] == 'N'
					|| game->map[y][x] == 'S' || game->map[y][x] == 'W'
					|| game->map[y][x] == 'E')
					draw_tile(game, x, y);
			}
		}
	}
}

void	draw_single_ray(t_game *game, t_render *render, int px, int py)
{
	t_hit	hit;
	int		i;
	int		ray_x;
	int		ray_y;

	render->ray_dir_x = game->player.dir_x
		+ game->player.plane_x * render->camera_x;
	render->ray_dir_y = game->player.dir_y
		+ game->player.plane_y * render->camera_x;
	hit = perform_dda(game, render->ray_dir_x, render->ray_dir_y);
	i = 0;
	while (i < hit.dist * MINIMAP_TILE_SIZE)
	{
		ray_x = px + render->ray_dir_x * i;
		ray_y = py + render->ray_dir_y * i;
		mlx_put_pixel(game->game_img, ray_x, ray_y, C_GREEN);
		i++;
	}
}
