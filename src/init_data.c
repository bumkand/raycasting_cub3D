/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:17:10 by jakand            #+#    #+#             */
/*   Updated: 2025/09/19 17:48:25 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_texture(char *line, int i, char **texture)
{
	int	y;
	int	j;

	while (line[i] == ' ')
		i++;
	if (line[i] >= 9 && line[i] <= 13)
		return (printf("Whitespace if file .cub\n"), 1);
	if (line[i] != '\n' && line[i] != '\0')
	{
		y = i;
		while (line[i] != '\n' && line[i] != '\0' && line[i] != ' ')
			i++;
		j = i - y;
		*texture = malloc((j + 1) * sizeof(char));
		if (!texture)
			return (printf("Texture allocation error\n"), 1);
		i = 0;
		while (i < j)
			(*texture)[i++] = line[y++];
		(*texture)[i] = '\0';
	}
	while (line[y] == ' ')
		y++;
	if (line[y] != '\n' && line[y] != '\0')
		return (1);
	return (0);
}

int	check_order(char *text_1, char *text_2)
{
	if (text_1 && text_2)
		return (1);
	return (0);
}

int	choose_texture(char *line, int *x, t_game *game)
{
	if (line[*x] == 'N' && line[*x + 1] && line[*x + 1] == 'O')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_no) || check_order(game->text_no, game->text_so))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'S' && line[*x + 1] && line[*x + 1] == 'O')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_so) || check_order(game->text_so, game->text_we))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'W' && line[*x + 1] && line[*x + 1] == 'E')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_we) || check_order(game->text_we, game->text_ea))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'E' && line[*x + 1] && line[*x + 1] == 'A')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_ea))
			return (printf("Fill texture error\n"), 1);
	}
	//else if (line[*x] == 'F' || check_order(game->text_ea, game->color_f[0]))
	return (0);
}

int	init_texture_color_map(char *line, t_game *game)
{
	int	x;

	x = 0;
	while (line[x] != '\n' && line[x] != '\0')
	{
		while (line[x] == ' ')
			x++;
		if (line[x] >= 9 && line[x] <= 13)
		{
			free_texture(game);
			return (printf("Whitespace in file\n"), 1);
		}
		if (choose_texture(line, &x, game))
			return (free_texture(game), 1);
		if (line[x] != '\0' && line[x] != '\n')
			x++;
	}
	return (0);
}

int	init_data(t_game *game, int fd)
{
	int		y;
	char	*line;
	char	**cub_file;

	fd = open("maps/valid_map_1.cub", O_RDONLY);
	line = get_next_line(fd);
	if (get_cub_file(&cub_file, fd, line))
		return (printf(".cub File Array Error\n"), 1);
	//y = 0;
	//while (cub_file[y])
	//{
	//	printf("%s\n", cub_file[y]);
	//	y++;
	//}
	y = 0;
	while (cub_file[y])
	{
		if (init_texture_color_map(cub_file[y], game))
			return (free_cub(cub_file), 1);
		y++;
	}
	printf("NO texture = %s\nSO texture = %s\nWE texture = %s\nEA texture = %s\n", game->text_no, game->text_so, game->text_we, game->text_ea);
	fd = open("maps/valid_map_1.cub", O_RDONLY);
	game->height = get_height(fd);
	close(fd);
	fd = open("maps/valid_map_1.cub", O_RDONLY);
	game->width = get_width(fd);
	close(fd);
	printf(" game height = %i\n game width = %i\n", game->height, game->width);
	free_cub(cub_file);
	return (0);
}
