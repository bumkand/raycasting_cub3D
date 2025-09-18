/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
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
	mlx_t			*mlx;
    mlx_image_t		*player_img;
	
	// Player position (in pixel coordinates for now)
    int             player_x;
    int             player_y;
	
	// Map data
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

int		init_game(t_game *game);

int     init_player(t_game *game);
void    update_player_position(t_game *game);
void    render_player(t_game *game);
int     check_collision(t_game *game, int new_x, int new_y);

// game.c
void 	game_loop(t_game *game);


#endif