/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_text_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 21:17:53 by jakand            #+#    #+#             */
/*   Updated: 2025/09/22 21:20:54 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_texture(char *line, int i, char **texture)
{
	int	y;
	int	j;

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
	if (!(*texture))
		return (printf("Texture with no path\n"), 1);
	while (line[y] == ' ')
		y++;
	if (line[y] != '\n' && line[y] != '\0')
		return (1);
	return (0);
}

long	ft_atoi(const char *nptr, int *i)
{
	static int	j;
	long		store;

	store = 0;
	j++;
	if (!(nptr[*i] >= '0' && nptr[*i] <= '9'))
		return (-1);
	while ((unsigned char)nptr[*i] >= '0' && (unsigned char)nptr[*i] <= '9')
	{
		store = store * 10 + ((unsigned char)nptr[*i] - 48);
		(*i)++;
	}
	if (nptr[*i] == ',' && j < 3)
		(*i)++;
	while (j == 3 && nptr[*i] != '\n' && nptr[*i] != '\0')
	{
		if (nptr[*i] != ' ')
			return (-1);
		(*i)++;
	}
	if (j == 3)
		j = 0;
	return (store);
}

int	fill_color(char *line, int i, int color[])
{
	int	j;

	while (line[i] == ' ')
		i++;
	if (line[i] >= 9 && line[i] <= 13)
		return (printf("Whitespace if file .cub\n"), 1);
	j = 0;
	while (line[i] && j < 3)
	{
		color[j] = ft_atoi(line, &i);
		if (color[j] < 0 || color[j] > 255)
			return (1);
		j++;
	}
	return (0);
}

int	check_order_texture(char *text_1, char *text_2)
{
	if (text_1 && text_2)
		return (1);
	return (0);
}

int	check_order_color(t_game *game, int i)
{
	if (i == 1 && game->color_f[0] >= 0 && game->color_c[0] >= 0)
		return (1);
	if (i == 2 && game->color_c[0] >= 0 && game->color_f[0] < 0)
		return (1);
	if (i == 3 && game->text_ea && game->color_f[0] >= 0)
		return (1);
	return (0);
}

int	choose_texture_color(char *line, int *x, t_game *game)
{
	int	i;

	i = *x;
	if (line[*x] == 'N' && line[*x + 1] && line[*x + 1] == 'O')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_no) || check_order_texture(game->text_no, game->text_so))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'S' && line[*x + 1] && line[*x + 1] == 'O')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_so) || check_order_texture(game->text_so, game->text_we))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'W' && line[*x + 1] && line[*x + 1] == 'E')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_we) || check_order_texture(game->text_we, game->text_ea))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'E' && line[*x + 1] && line[*x + 1] == 'A')
	{
		(*x) += 2;
		if (fill_texture(line, *x, &game->text_ea) || check_order_color(game, 3))
			return (printf("Fill texture error\n"), 1);
	}
	else if (line[*x] == 'F')
	{
		(*x) += 1;
		if (fill_color(line, *x, game->color_f) || check_order_color(game, 1))
			return (printf("Fill color error\n"), 1);
	}
	else if (line[*x] == 'C')
	{
		(*x) += 1;
		if (fill_color(line, *x, game->color_c) || check_order_color(game, 2))
			return (printf("Fill color error\n"), 1);
	}
	else if (i == *x)
	{
		while (line[*x] != '\n' && line[*x] != '\0')
		{
			if (line[*x] != ' ')
				return (printf("Forbidden characters in .cub\n"), 1);
		}
	}
	return (0);
}
