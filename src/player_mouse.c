/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:49:51 by marcel            #+#    #+#             */
/*   Updated: 2025/10/16 10:57:07 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	delta_x;
	double	rotation;

	(void) ypos;
	game = (t_game *)param;
	delta_x = xpos - (WIDTH / 2);
	rotation = delta_x * MOUSE_SENSITIVITY;
	if (rotation != 0)
		rotate_vectors(game, rotation);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
}
