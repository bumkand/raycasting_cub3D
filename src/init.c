/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:44:19 by marcel            #+#    #+#             */
/*   Updated: 2025/10/09 21:55:27 by jakand           ###   ########.fr       */
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
	return (0);
}

int	get_image(t_game *game)
{
	game->img = ft_calloc(1, sizeof(t_image));
	if (!game->img)
		return (1);
	game->img->NO = mlx_texture_to_image(game->mlx, game->text->NO);
	game->img->SO = mlx_texture_to_image(game->mlx, game->text->SO);
	game->img->WE = mlx_texture_to_image(game->mlx, game->text->WE);
	game->img->EA = mlx_texture_to_image(game->mlx, game->text->EA);
	if (!game->img->NO || !game->img->SO
		|| !game->img->WE || !game->img->EA)
	{
		if (game->img->NO)
			mlx_delete_texture(game->text->NO);
		if (game->img->SO)
			mlx_delete_texture(game->text->SO);
		if (game->img->WE)
			mlx_delete_texture(game->text->WE);
		if (game->img->EA)
			mlx_delete_texture(game->text->EA);
		return (free(game->img), 1);
	}
	mlx_delete_texture(game->text->NO);
	mlx_delete_texture(game->text->SO);
	mlx_delete_texture(game->text->WE);
	mlx_delete_texture(game->text->EA);
	return (0);
}

void	free_visual(t_game *game)
{
	if (game->img != NULL)
		free(game->img);
	if (game->text != NULL)
		free(game->text);
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

	if (get_textures(game) || get_image(game))
	{
		free_visual(game);
		return (ft_error("Failed to create wall images"));
	}
    return (EXIT_SUCCESS);
}
