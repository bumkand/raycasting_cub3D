/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:39:59 by jaandras          #+#    #+#             */
/*   Updated: 2025/09/16 15:24:01 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (NULL);
	if ((nmemb * size) < nmemb || (nmemb * size) < size)
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char	*ft_free_join(char *buffer, char *line)
{
	char	*str;

	str = ft_strjoin(buffer, line);
	if (!str)
		return (free(buffer), NULL);
	free(buffer);
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		total;
	int		i;
	int		j;
	char	*string;

	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2);
	string = ft_calloc((total + 1), sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		string[i++] = s2[j++];
	string[i] = '\0';
	return (string);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0' && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}
