/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcel <marcel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:06:08 by jakand            #+#    #+#             */
/*   Updated: 2025/09/18 19:55:44 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	count_lines(int height, char *line, int fd)
{
	height = 0;
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	lines_lenght(char ****cub_file, char *line, int height)
{
	int	lenght;
	int	j;

	lenght = 0;
	while (line[lenght] != '\n' && line[lenght])
		lenght++;
	(**cub_file)[height] = malloc((lenght + 1) * sizeof(char));
	if (!(**cub_file)[height])
		return (free(line), 1);
	j = 0;
	while (j < lenght)
	{
		(**cub_file)[height][j] = line[j];
		j++;
	}
	(**cub_file)[height][j] = '\0';
	free(line);
	return (0);
}

int	get_cub_file(char ***cub_file, int fd, char *line)
{
	int	height;

	height = count_lines(0, line, fd);
	*cub_file = malloc((height + 1) * sizeof(char *));
	if (!*cub_file)
		return (1);
	fd = open("maps/valid_map_1.cub", O_RDONLY);
	line = get_next_line(fd);
	height = 0;
	while (line)
	{
		if (lines_lenght(&cub_file, line, height))
			return (close(fd), 1);
		line = get_next_line(fd);
		height++;
	}
	(*cub_file)[height] = NULL;
	close(fd);
	return (0);
}

int	fill_texture(char *line, int i, t_game *game)
{
	int	y;
	int	j;

	while (line[i] == ' ')
		i++;
	if (line[i] >= 9 && line[i] <= 13)
		return (free(line), printf("Init whitespace\n"), 1);
	if (line[i] != '\n' && line[i] != '\0')
	{
		y = i;
		printf("y = %i\n", y);
		while (line[i] != '\n' && line[i] != '\0' && line[i] != ' ')
			i++;
		printf("i = %i\n", i);
		j = i - y;
		printf("j = %i\n", j);
		game->text_no = malloc((j + 1) * sizeof(char));
		if (!game->text_no)
			return (free(line), printf("text_no malloc error\n"), 1);
		i = 0;
		while (i < j)
		{
			game->text_no[i] = line[y];
			i++;
			y++;
		}
		game->text_no[i] = '\0';
	}

	return (0);
}

int	init_texture(char *line, t_game *game)
{
	int	x;

	x = 0;
	while (line[x] != '\n' && line[x] != '\0')
	{
		while (line[x] == ' ')
			x++;
		if (line[x] >= 9 && line[x] <= 13)
		{
			if (game->text_no)
				free(game->text_no);
			return (printf("Whitespace in file\n"), 1);
		}
		if (line[x] == 'N' && line[x + 1] && line[x + 1] == 'O')
		{
			x += 2;
			if (fill_texture(line, x, game))
				return (printf("Fill texture error\n"), 1);
		}
		x++;
	}
	return (0);
}

int	init_data(t_game *game, int fd)
{
	int		y;
	int		i;
	char	*line;
	char	**cub_file;

	fd = open("maps/valid_map_1.cub", O_RDONLY);
	line = get_next_line(fd);
	if (get_cub_file(&cub_file, fd, line))
		return (printf(".cub File Array Error\n"), 1);
	//i = 0;
	//while (cub_file[i])
	//{
	//	printf("%s\n", cub_file[i]);
	//	i++;
	//}
	y = 0;
	while (cub_file[y])
	{
		if (init_texture(cub_file[y], game))
		{
			i = 0;
			while (cub_file[i])
			{
				free(cub_file[i]);
				i++;
			}
			if (cub_file)
				free(cub_file);
			return (1);
		}
		y++;
	}
	printf("NO texture = %s\n", game->text_no);
	fd = open("maps/valid_map_1.cub", O_RDONLY);
	game->height = get_height(fd);
	close(fd);
	fd = open("maps/valid_map_1.cub", O_RDONLY);
	game->width = get_width(fd);
	close(fd);
	printf(" game height = %i\n game width = %i\n", game->height, game->width);
	i = 0;
	while (cub_file[i])
	{
		free(cub_file[i]);
		i++;
	}
	if (cub_file)
		free(cub_file);
	return (0);
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
			break ;
		}
		if (!line)
			break ;
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	game.text_no = NULL;
	if (init_data(&game, fd))
	{
		if (line)
			free(line);
		return (1);
	}
	if (game.text_no)
		free(game.text_no);
	if (init_game(&game) || init_player(&game))
    	return (1);
	game_loop(&game);
	return (0);
}



//i = 0;
//		y = 0;
//		line = get_next_line(fd);
//		if (!line)
//			break ;
//		while (line[i] != '\n')
//		{
//			if (line[i] >= 9 && line[i] <= 13)
//				return (free(line), 1);
//			if (line[i] == 'N' && line[i + 1] && line[i + 1] == 'O')
//			{
//				i += 2;
//				while (line[i] == ' ')
//					i++;
//				while (line[i] != '\n' && line[i] != ' ')
//				{
//					if (!game->text_no && (line[i] == '\n' || line[i] == ' '))
//					{
//						game->text_no = malloc((y + 1) * sizeof(char));
//						if (!game->text_no)
//							return (free(line), 1);
//						i = i - y;
//						y = 0;
//					}
//					if (game->text_no)
//						game->text_no[y] = line[i];
//					i++;
//					y++;
//				}
//				if (game->text_no)
//					game->text_no[y] = '\0';
//				i++;
//			}
//			i++;
//		}
//		free(line);


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
