/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:06:08 by jakand            #+#    #+#             */
/*   Updated: 2025/09/20 21:59:11 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_char(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != ' ' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W' && *line != '\n')
			return (printf("Wrong char in the map\n"), 1);
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			count++;
		if (count > 1)
			return (printf("More than 1 starting position\n"), 1);
		line++;
	}
	return (0);
}

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
	char	*line;
	int		fd;
	int		i;
	t_game	game;

	fd = open("maps/valid_map_1.cub", O_RDONLY);
	if (fd < 0)
		return (printf("fd error\n"), 1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (i > 7 && line && check_map_char(line))
		{
			free(line);
			line = NULL;
			break ;
		}
		if (!line)
			break ;
		printf("%s", line);
		free(line);
		line = NULL;
		i++;
	}
	close(fd);
	game.text_no = NULL;
	game.text_so = NULL;
	game.text_we = NULL;
	game.text_ea = NULL;
	game.color_f[0] = -1;
	game.color_c[0] = -1;
	if (init_data(&game, fd))
	{
		free_texture(&game);
		return (1);
	}
	//if (init_game(&game) || init_player(&game))
    //	return (1);
	//game_loop(&game);
	free_texture(&game);
	return (0);
}
