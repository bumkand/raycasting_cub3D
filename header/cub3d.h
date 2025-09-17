/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 13:27:05 by jakand            #+#    #+#             */
/*   Updated: 2025/09/17 17:46:52 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1

# define WIDTH 850
# define HEIGHT 550

# include "MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_game
{
	char	**map;
	int		width;
	int		height;
	char	*text_no;			// Texture North
	char	*text_so;			// Texture South
	char	*text_we;			// Texture West
	char	*text_ea;			// Texture East
	char	color_f[3];			// RGB Floor
	char	color_c[3];			// RGB Ceiling
}	t_game;


// Get Next Line Functions
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_free_join(char *buffer, char *line);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);

#endif