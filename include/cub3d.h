/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 13:27:05 by jakand            #+#    #+#             */
/*   Updated: 2025/10/14 20:59:04 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include "MLX42/MLX42.h"
# include "libft.h" 
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 1024          // Šířka okna
# define HEIGHT 768           // Výška okna
# define TILE_SIZE 32 // Velikost jednoho čtverečku mapy v pixelech
# define MINIMAP_SCALE 8 // Zmenšovací faktor pro minimapu
# define PLAYER_SPEED 0.1
# define PLAYER_SIZE 8
# define COLLISION_RADIUS ( (double)PLAYER_SIZE / (double)TILE_SIZE / 2.0 )
# define ROTATION_SPEED 0.05

# define C_BLACK   0x000000FF  // Černá
# define C_WHITE   0xFFFFFFFF  // Bílá
# define C_RED     0xFF0000FF  // Červená (pro hráče)
# define C_GREY    0x808080FF  // Šedá (pro podlahu minimapy)
# define C_GREEN   0x00FF00FF  // Zelená (pro pohled hráče)

typedef struct s_texture
{
	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;
}	t_texture;

typedef struct s_image
{
	mlx_image_t		*NO;
	mlx_image_t		*SO;
	mlx_image_t		*WE;
	mlx_image_t		*EA;
}	t_image;

typedef struct s_hit
{
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	dist;
	int		step_x;
	int		step_y;
	int		found;
}	t_hit;

typedef struct s_render
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	line_height;
	double	draw_start;
	double	draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	text_pos;
	double	step;
}	t_render;

typedef struct s_player
{
	double	pos_x;      // Pozice v mapových jednotkách
	double	pos_y;
	double	dir_x;      // Směrový vektor
	double	dir_y;
	double	plane_x;    // Vektor kamery
	double	plane_y;
}	t_player;

typedef struct s_game
{
	mlx_t				*mlx;
    mlx_image_t			*game_img; // framebuffer
	struct s_texture	*text;
	struct s_image		*img;

	// Map data
	char	**map;
	int		width;
	int		height;
	char	*text_no;			// Texture North
	char	*text_so;			// Texture South
	char	*text_we;			// Texture West
	char	*text_ea;			// Texture East
	int		color_f[3];			// RGB Floor
	int		color_c[3];			// RGB Ceiling

	t_player    player;       // Vnořená struktura pro hráče
}	t_game;

// error.c
int 	ft_error(const char *message);

// game.c
void 	game_loop(t_game *game);
void	game_tick(void *param);

// init.c
int		init_game(t_game *game);

// minimap.c 
void	clear_framebuffer(t_game *game);
void	draw_minimap(t_game *game);

// player.c
void	handle_player_input(t_game *game);
int		check_collision(t_game *game, double new_x, double new_y);

int	init_data(t_game *game, char *map_path);

// cub_file.c
int	get_cub_file(char ***cub_file, int fd, char *line, char *map_path);

int	init_texture_color(char *line, t_game *game);
int	choose_texture_color(char *line, int *x, t_game *game);


int	get_height(int fd);
int	get_width(int fd);

// init_texture.c
int	texture_no_so(char *line, int *x, t_game *game);
int	texture_we_ea(char *line, int *x, t_game *game);
int	check_order_texture(char *text_1, char *text_2);

// init_color.c
int color_c_f(char *line, int *x, t_game *game);
int	check_order_color(t_game *game, int i);

// init_map.c
int	init_game_map(char **cub_map, int start, t_game *game);

// map_gamebility.c
int		check_gamebility(char **map_copy, t_game *game);
void	find_start_position(t_game *game);
char	**copy_of_map(t_game *game);

// map_utils.c
char	*ft_strdup(const char *s);
int	count_length(const char *s);
int	check_free_line(char *line);
char	*ft_strdup_with_spaces(const char *s, t_game *game);

// raycast.c
t_hit perform_dda(t_game *game, double ray_dir_x, double ray_dir_y);

// 3d_view.c
void	draw_3d_view(t_game *game);

// free_functions.c
void	free_texture(t_game *game);
void	free_map(t_game *game);
void	free_cub(char **cub_file);

//void	draw_ray(void *param);

#endif
