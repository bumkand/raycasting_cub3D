/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:37:40 by jakand            #+#    #+#             */
/*   Updated: 2025/09/24 17:46:23 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_texture(int *y, int i, char *line, char **texture)
{
	int	j;

	while (line[i] != '\n' && line[i] != '\0' && line[i] != ' ')
		i++;
	j = i - *y;
	*texture = malloc((j + 1) * sizeof(char));
	if (!*texture)
		return (printf("Texture allocation error\n"), 1);
	i = 0;
	while (i < j)
		(*texture)[i++] = line[(*y)++];
	(*texture)[i] = '\0';
	return (0);
}

int	fill_texture(char *line, int i, char **texture)
{
	int	y;

	y = 0;
	if (*texture)
		return (printf("Same texture allocation error\n"), 1);
	while (line[i] == ' ')
		i++;
	if (line[i] >= 9 && line[i] <= 13)
		return (printf("Whitespace if file .cub\n"), 1);
	if (line[i] != '\n' && line[i] != '\0')
	{
		y = i;
		if (allocate_texture(&y, i, line, texture))
			return (1);
	}
	if (!(*texture))
		return (printf("Texture with no path\n"), 1);
	while (line[y] == ' ')
		y++;
	if (line[y] != '\n' && line[y] != '\0')
		return (1);
	return (0);
}

int	check_order_texture(char *text_1, char *text_2)
{
	if (text_1 && text_2)
		return (1);
	return (0);
}

int	texture_we_ea(char *line, int *x, t_game *game)
{
	if (line[*x] == 'W' && line[*x + 1] && line[*x + 1] == 'E')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_we)
			|| check_order_texture(game->text_we, game->text_ea))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'E' && line[*x + 1] && line[*x + 1] == 'A')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_ea)
			|| check_order_color(game, 3))
			return (printf("Fill texture error\n"), 1);
	}
	return (0);
}

int	texture_no_so(char *line, int *x, t_game *game)
{
	if (line[*x] == 'N' && line[*x + 1] && line[*x + 1] == 'O')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_no)
			|| check_order_texture(game->text_no, game->text_so))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'S' && line[*x + 1] && line[*x + 1] == 'O')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_so)
			|| check_order_texture(game->text_so, game->text_we))
			return (printf("Fill texture error\n"), 1);
	}
	return (0);
}
