/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:41:37 by jakand            #+#    #+#             */
/*   Updated: 2025/09/30 18:08:01 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_free_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	count_length(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc((count_length(s) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < count_length(s))
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
			line[i] = '0';
		else
			line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i] = '\n';
	else
		line[i] = '\0';
	return (line);
}

char	*ft_strdup_with_spaces(const char *s, t_game *game)
{
	int		i;
	char	*line;
	int		len;

	len = count_length(s);
	i = 0;
	line = malloc((game->width + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = s[i];
		i++;
	}
	while (i < game->width)
	{
		line[i] = ' ';
		i++;
	}
	line[i] = '\0';
	return (line);
}
