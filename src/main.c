/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:06:08 by jakand            #+#    #+#             */
/*   Updated: 2025/10/05 16:10:45 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_game *game)
{
	game->text_no = NULL;
	game->text_so = NULL;
	game->text_we = NULL;
	game->text_ea = NULL;
	game->color_f[0] = -1;
	game->color_f[1] = -1;
	game->color_f[2] = -1;
	game->color_c[0] = -1;
	game->color_c[1] = -1;
	game->color_c[2] = -1;
	game->map = NULL;
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
        return (ft_error("Usage: ./cub3D maps/map_file.cub"));
	
	init_struct(&game);
	if (init_data(&game, argv[1]))
	{
		free_texture(&game);
		free_map(&game);
		return (1);
	}
	if (init_game(&game) || load_textures(&game))
		return (1);
	game_loop(&game);
	free_texture(&game);
	free_map(&game);
	return (0);
}
