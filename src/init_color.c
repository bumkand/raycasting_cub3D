/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:38:22 by jakand            #+#    #+#             */
/*   Updated: 2025/09/24 17:47:43 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	color_c_f(char *line, int *x, t_game *game)
{
	if (line[*x] == 'F')
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
	return (0);
}
