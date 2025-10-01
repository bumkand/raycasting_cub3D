/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:06:08 by jakand            #+#    #+#             */
/*   Updated: 2025/10/01 17:26:47 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_width(int fd)
{
	int		i;
	int		x;
	int		k;
	int		count;
	char	*line;

	i = 0;
	x = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		if (i > 7 && line)
		{
			k = 0;
			count = 0;
			while (line[k] && line[k] != '\n')
			{
				if (line[k] != ' ')
					count = k;
				k++;
			}
			if (count + 1 > x)
				x = count + 1;
		}
		free(line);
	}
	return (x);
}

int	get_height(int fd)
{
	int		i;
	int		y;
	int		k;
	char	*line;

	i = 0;
	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		if (i > 7)
		{
			k = 0;
			while (line[k] != '\n')
			{
				if (line[k] != ' ')
				{
					y++;
					break ;
				}
				k++;
			}
		}
		free(line);
	}
	return (y);
}

int	main(void)
{
	t_game	game;

	game.text_no = NULL;
	game.text_so = NULL;
	game.text_we = NULL;
	game.text_ea = NULL;
	game.color_f[0] = -1;
	game.color_c[0] = -1;
	game.map = NULL;
	if (init_data(&game))
	{
		free_texture(&game);
		return (1);
	}
	if (init_game(&game) || init_player(&game))
		return (1);
	game_loop(&game);
	free_texture(&game);
	free_map(&game);
	return (0);
}
