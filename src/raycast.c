/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 22:53:13 by marcel            #+#    #+#             */
/*   Updated: 2025/10/15 19:08:10 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_delta_dist(t_hit *hit, double ray_dir_x, double ray_dir_y)
{
	if (ray_dir_x == 0)
		hit->delta_dist_x = 1e30;
	else
		hit->delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_y == 0)
		hit->delta_dist_y = 1e30;
	else
		hit->delta_dist_y = fabs(1 / ray_dir_y);
}

void	init_side_dist(t_game *game, t_hit *hit,
		double ray_dir_x, double ray_dir_y)
{
	if (ray_dir_x < 0)
	{
		hit->step_x = -1;
		hit->side_dist_x = (game->player.pos_x - hit->map_x)
			* hit->delta_dist_x;
	}
	else
	{
		hit->step_x = 1;
		hit->side_dist_x = (hit->map_x + 1.0 - game->player.pos_x)
			* hit->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		hit->step_y = -1;
		hit->side_dist_y = (game->player.pos_y - hit->map_y)
			* hit->delta_dist_y;
	}
	else
	{
		hit->step_y = 1;
		hit->side_dist_y = (hit->map_y + 1.0 - game->player.pos_y)
			* hit->delta_dist_y;
	}
}

void	find_hit(t_hit *hit, t_game *game, double ray_dir_x, double ray_dir_y)
{
	hit->found = 0;
	while (hit->found == 0)
	{
		if (hit->side_dist_x < hit->side_dist_y)
		{
			hit->side_dist_x += hit->delta_dist_x;
			hit->map_x += hit->step_x;
			hit->side = 0;
		}
		else
		{
			hit->side_dist_y += hit->delta_dist_y;
			hit->map_y += hit->step_y;
			hit->side = 1;
		}
		if (game->map[hit->map_y][hit->map_x] == '1')
			hit->found = 1;
	}
	if (hit->side == 0)
		hit->dist = (hit->map_x - game->player.pos_x
				+ (1 - hit->step_x) / 2) / ray_dir_x;
	else
		hit->dist = (hit->map_y - game->player.pos_y
				+ (1 - hit->step_y) / 2) / ray_dir_y;
}

t_hit	perform_dda(t_game *game, double ray_dir_x, double ray_dir_y)
{
	t_hit	hit;

	hit.map_x = (int)game->player.pos_x;
	hit.map_y = (int)game->player.pos_y;
	init_delta_dist(&hit, ray_dir_x, ray_dir_y);
	init_side_dist(game, &hit, ray_dir_x, ray_dir_y);
	find_hit(&hit, game, ray_dir_x, ray_dir_y);
	return (hit);
}
