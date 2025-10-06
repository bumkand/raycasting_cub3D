/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 22:53:13 by marcel            #+#    #+#             */
/*   Updated: 2025/10/06 21:32:28 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cast_rays(t_game *game)
{
    int		col;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int     side; // 0 pro X-stranu, 1 pro Y-stranu
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	
	mlx_texture_t *texture;
	double	texture_x;
	
	col = -1;
	while (++col < WIDTH)
	{
		camera_x = 2 * col / (double)WIDTH - 1; // Vypočítat souřadnice x kamery
		ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		map_x = (int)game->player.pos_x;
		map_y = (int)game->player.pos_y;
		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1 / ray_dir_y);
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
		// DDA algoritmus
		while (1)
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
				break ;
		}

		if (side == 0)
			perp_wall_dist = (map_x - game->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->player.pos_y + (1 - step_y) / 2) / ray_dir_y;

		line_height = (int)(HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		// Výběr textury na základě směru
		if (side == 0)	// Svislá stěna
		{
			if (ray_dir_x > 0)
				texture = game->textures.west; 
			else
				texture = game->textures.east; 
		}
		else // Vodorovná stěna
		{
			if (ray_dir_y > 0)
				texture = game->textures.north; 
			else
				texture = game->textures.south; 
		}
		// Výpočet přesné pozice zdi
		if (side == 0) // Svislá stěna
			wall_x = game->player.pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = game->player.pos_x + perp_wall_dist * ray_dir_x;
		wall_x = wall_x - (int)(wall_x);
		texture_x = (int)(wall_x * (double)(texture->width));
		
		double step = 1.0 * texture->height / line_height;
        double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
        int y = draw_start -1;
        
        while (++y <= draw_end)
        {
            int tex_y = (int)tex_pos & (texture->height - 1);
            tex_pos += step;
            
            // Získání barvy z textury
            uint8_t *pixel = &texture->pixels[(tex_y * texture->width + (int)texture_x) * 4];
            int color = get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]);
            
            // Nakreslení pixelu
            mlx_put_pixel(game->game_img, col, y, color);
        }
	}
	
}