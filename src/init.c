/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:44:19 by marcel            #+#    #+#             */
/*   Updated: 2025/10/12 18:17:54 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_textures(t_game *game)
{
	game->text = ft_calloc(1, sizeof(t_texture));
	if (!game->text)
		return (1);
	game->text->NO = mlx_load_png(game->text_no);
	game->text->SO = mlx_load_png(game->text_so);
	game->text->WE = mlx_load_png(game->text_we);
	game->text->EA = mlx_load_png(game->text_ea);
	if (!game->text->NO || !game->text->SO
		|| !game->text->WE || !game->text->EA)
	{
		if (game->text->NO)
			mlx_delete_texture(game->text->NO);
		if (game->text->SO)
			mlx_delete_texture(game->text->SO);
		if (game->text->WE)
			mlx_delete_texture(game->text->WE);
		if (game->text->EA)
			mlx_delete_texture(game->text->EA);
		return (free(game->text), 1);
	}
	return (0);
}

int init_game(t_game *game)
{
    // 1. Inicializace MLX (toto už máte)
    game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
    if (!game->mlx)
    {
        // Zde by mělo být volání vaší chybové funkce
        return (ft_error("MLX initialization failed"));
    }

    // 2. Vytvoření obrázku (framebufferu) - TOTO CHYBÍ
    game->game_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->game_img)
    {
        mlx_terminate(game->mlx); // Uklidíme po mlx_init
        return (ft_error("Failed to create MLX image"));
    }

    // 3. Zobrazení obrázku v okně - TOTO CHYBÍ
    if (mlx_image_to_window(game->mlx, game->game_img, 0, 0) == -1)
    {
        mlx_terminate(game->mlx); // Uklidíme
        return (ft_error("Failed to display image in window"));
    }

	if (get_textures(game))
	{
		mlx_terminate(game->mlx); // Uklidíme
		return (ft_error("Failed to save wall textures"));
	}
    return (EXIT_SUCCESS);
}
