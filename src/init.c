/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:44:19 by marcel            #+#    #+#             */
/*   Updated: 2025/09/18 21:51:21 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_game(t_game *game)
{
    if (!(game->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    return (EXIT_SUCCESS);
}

int     init_player(t_game *game)
{
    game->player_x = 100; // Initial X position
    game->player_y = 100; // Initial Y position
    game->player_img = mlx_new_image(game->mlx, 32, 32);
    if (!game->player_img)
        return (1);
    mlx_image_to_window(game->mlx, game->player_img, game->player_x, game->player_y);
    return (0);
}
