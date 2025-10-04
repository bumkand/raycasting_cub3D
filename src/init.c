/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:44:19 by marcel            #+#    #+#             */
/*   Updated: 2025/10/02 23:20:49 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
    
    return (EXIT_SUCCESS);
}
