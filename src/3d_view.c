/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:54:46 by jakand            #+#    #+#             */
/*   Updated: 2025/10/09 17:12:38 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rgb_to_trgb(int t, int r, int g, int b)
{
	return (((t & 0xFF) << 24) | ((r & 0xFF) << 16)
		| ((g & 0xFF) << 8) | (b & 0xFF));
}

void	draw_vertical_line(t_game *game, int x, double draw_start, double draw_end, int color)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < draw_start)
			mlx_put_pixel(game->game_img, x, y, rgb_to_trgb(255, game->color_f[0], game->color_f[1], game->color_f[2]));
		else if (y >= draw_start && y < draw_end)
			mlx_put_pixel(game->game_img, x, y, color);
		else
			mlx_put_pixel(game->game_img, x, y, rgb_to_trgb(255, game->color_c[0], game->color_c[1], game->color_c[2]));
		y++;
	}
}

void	draw_3d_view(t_game *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	t_hit	hit;
	int		color;
	double	line_height;
	double	draw_start;
	double	draw_end;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		hit = perform_dda(game, ray_dir_x, ray_dir_y);
		line_height = HEIGHT / hit.dist;
		draw_start = (HEIGHT / 2) - (line_height / 2);
		if (draw_start < 0)
			draw_start = 0;
		draw_end = (HEIGHT / 2) + (line_height / 2);
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		if (hit.side == 0)
			color = C_WHITE;
		else
			color = C_GREY;
		draw_vertical_line(game, x, draw_start, draw_end, color);
		x++;
	}
}
