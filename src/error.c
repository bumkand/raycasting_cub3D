/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:12:53 by marcel            #+#    #+#             */
/*   Updated: 2025/10/02 21:13:16 by marcel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_error(const char *message)
{
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd((char *)message, 2);
    ft_putstr_fd("\n", 2);
    return (1);
}
