/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:39:59 by jaandras          #+#    #+#             */
/*   Updated: 2025/10/02 21:23:55 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_join(char *buffer, char *line)
{
	char	*str;

	str = ft_strjoin(buffer, line);
	if (!str)
		return (free(buffer), NULL);
	free(buffer);
	return (str);
}
