/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:06:08 by jakand            #+#    #+#             */
/*   Updated: 2025/09/18 22:50:09 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	check_map_char(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != ' ' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W' && *line != '\n')
			return (printf("Wrong char in the map\n"), 1);
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			count++;
		if (count > 1)
			return (printf("More than 1 starting position\n"), 1);
		line++;
	}
	return (0);
}

int	get_width(int fd)
{
	int		i;
	int		x;
	int		k;
	int		count;
	char	*line;

	i = 0;
	x = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		if (i > 7 && line)
		{
			k = 0;
			count = 0;
			while (line[k] && line[k] != '\n')
			{
				if (line[k] != ' ')
					count = k;
				k++;
			}
			if (count + 1 > x)
				x = count + 1;
		}
		free(line);
	}
	return (x);
}

int	get_height(int fd)
{
	int		i;
	int		y;
	int		k;
	char	*line;

	i = 0;
	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		if (i > 7)
		{
			k = 0;
			while (line[k] != '\n')
			{
				if (line[k] != ' ')
				{
					y++;
					break ;
				}
				k++;
			}
		}
		free(line);
	}
	return (y);
}

void	free_texture(t_game *game)
{
	if (game->text_no)
		free(game->text_no);
	if (game->text_so)
		free(game->text_so);
	if (game->text_we)
		free(game->text_we);
	if (game->text_ea)
		free(game->text_ea);
	game->text_no = NULL;
	game->text_so = NULL;
	game->text_we = NULL;
	game->text_ea = NULL;
}

int	main(void)
{
	char	*line;
	int		fd;
	int		i;
	t_game	game;

	fd = open("maps/valid_map_1.cub", O_RDONLY);
	if (fd < 0)
		return (printf("fd error\n"), 1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (i > 7 && line && check_map_char(line))
		{
			free(line);
			line = NULL;
			break ;
		}
		if (!line)
			break ;
		printf("%s", line);
		free(line);
		line = NULL;
		i++;
	}
	close(fd);
	game.text_no = NULL;
	game.text_so = NULL;
	game.text_we = NULL;
	game.text_ea = NULL;
	if (init_data(&game, fd))
	{
		free_texture(&game);
		return (1);
	}
	free_texture(&game);
	return (0);
}





//// -----------------------------------------------------------------------------
//// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
//// See README in the root project for more information.
//// -----------------------------------------------------------------------------

//#include "../header/cub3d.h"

//static mlx_image_t* image;

//// -----------------------------------------------------------------------------

//int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
//{
//    return (r << 24 | g << 16 | b << 8 | a);
//}

//void ft_randomize(void* param)
//{
//	(void)param;
//	for (uint32_t i = 0; i < image->width; ++i)
//	{
//		for (uint32_t y = 0; y < image->height; ++y)
//		{
//			uint32_t color = ft_pixel(
//				rand() % 0xFF, // R
//				rand() % 0xFF, // G
//				rand() % 0xFF, // B
//				rand() % 0xFF  // A
//			);
//			mlx_put_pixel(image, i, y, color);
//		}
//	}
//}

//void ft_hook(void* param)
//{
//	mlx_t* mlx = param;

//	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
//		mlx_close_window(mlx);
//	if (mlx_is_key_down(mlx, MLX_KEY_UP))
//		image->instances[0].y -= 5;
//	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
//		image->instances[0].y += 5;
//	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
//		image->instances[0].x -= 5;
//	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
//		image->instances[0].x += 5;
//}

//// -----------------------------------------------------------------------------

//int32_t main(void)
//{
//	mlx_t* mlx;

//	// Gotta error check this stuff
//	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
//	{
//		puts(mlx_strerror(mlx_errno));
//		return(EXIT_FAILURE);
//	}
//	if (!(image = mlx_new_image(mlx, 50, 50)))
//	{
//		mlx_close_window(mlx);
//		puts(mlx_strerror(mlx_errno));
//		return(EXIT_FAILURE);
//	}
//	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
//	{
//		mlx_close_window(mlx);
//		puts(mlx_strerror(mlx_errno));
//		return(EXIT_FAILURE);
//	}
	
//	mlx_loop_hook(mlx, ft_randomize, mlx);
//	mlx_loop_hook(mlx, ft_hook, mlx);

//	mlx_loop(mlx);
//	mlx_terminate(mlx);
//	return (EXIT_SUCCESS);
//}
