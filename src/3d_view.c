/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:54:46 by jakand            #+#    #+#             */
/*   Updated: 2025/10/14 21:27:40 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rgb_to_trgb(int t, int r, int g, int b)
{
	return (((t & 0xFF) << 24) | ((r & 0xFF) << 16)
		| ((g & 0xFF) << 8) | (b & 0xFF));
}

mlx_texture_t	*choose_wall(t_game *game, t_hit hit,
		double ray_dir_x, double ray_dir_y)
{
	mlx_texture_t	*tex;

	tex = NULL;
	if (hit.side == 0 && ray_dir_x > 0)
		tex = game->text->EA;
	else if (hit.side == 0 && ray_dir_x < 0)
		tex = game->text->WE;
	else if (hit.side == 1 && ray_dir_y > 0)
		tex = game->text->SO;
	else
		tex = game->text->NO;
	return (tex);
}

void	render_data(t_game *game, t_hit hit,
		t_render *render, mlx_texture_t *tex)
{
	if (hit.side == 0)
		render->wall_x = game->player.pos_y + hit.dist * render->ray_dir_y;
	else
		render->wall_x = game->player.pos_x + hit.dist * render->ray_dir_x;
	render->wall_x -= floor(render->wall_x);
	render->tex_x = (int)(render->wall_x * tex->width);
	if (hit.side == 0 && render->ray_dir_x > 0)
		render->tex_x = tex->width - render->tex_x - 1;
	if (hit.side == 1 && render->ray_dir_y < 0)
		render->tex_x = tex->width - render->tex_x - 1;
	render->step = 1.0 * tex->height / render->line_height;
	render->text_pos = (render->draw_start - HEIGHT / 2
			+ render->line_height / 2) * render->step;
}

void	make_wall_texture(t_game *game, t_hit hit, t_render *render, int x)
{
	mlx_texture_t	*tex;
	uint8_t			*pixel;
	uint32_t		color;
	int				y;

	tex = choose_wall(game, hit, render->ray_dir_x, render->ray_dir_y);
	render_data(game, hit, render, tex);
	y = render->draw_start;
	while (y < render->draw_end)
	{
		render->tex_y = (int)render->text_pos & (tex->height - 1);
		render->text_pos += render->step;
		pixel = tex->pixels + (render->tex_y * tex->width + render->tex_x) * 4;
		color = (pixel[0] << 24) | (pixel[1] << 16)
			| (pixel[2] << 8) | pixel[3];
		mlx_put_pixel(game->game_img, x, y, color);
		y++;
	}
}

void	draw_3d_view(t_game *game)
{
	int			x;
	t_hit		hit;
	t_render	render;

	x = 0;
	while (x < WIDTH)
	{
		render.camera_x = 2 * x / (double)WIDTH - 1;
		render.ray_dir_x = game->player.dir_x
			+ game->player.plane_x * render.camera_x;
		render.ray_dir_y = game->player.dir_y
			+ game->player.plane_y * render.camera_x;
		hit = perform_dda(game, render.ray_dir_x, render.ray_dir_y);
		render.line_height = HEIGHT / hit.dist;
		render.draw_start = (HEIGHT / 2) - (render.line_height / 2);
		if (render.draw_start < 0)
			render.draw_start = 0;
		render.draw_end = (HEIGHT / 2) + (render.line_height / 2);
		if (render.draw_end >= HEIGHT)
			render.draw_end = HEIGHT - 1;

		make_wall_texture(game, hit, &render, x);
		x++;
	}
}
