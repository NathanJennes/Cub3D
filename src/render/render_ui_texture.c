/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:37:18 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 15:57:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "core.h"
#include "render.h"

void render_invalid_texture(int64_t x, int64_t y);

void	render_ui_texture(int64_t tex_id, int64_t x, int64_t y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
	{
		render_invalid_texture(x, y);
		return ;
	}
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
			texture->original_handle, (int)x, (int)y);
}

void	render_ui_texture_grayscale(int64_t tex_id, int64_t x, int64_t y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
	{
		render_invalid_texture(x, y);
		return ;
	}
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
			texture->grayscale_handle, (int)x, (int)y);
}

void	render_ui_texture_inverse_grayscale(int64_t tex_id, int64_t x, int64_t y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
	{
		render_invalid_texture(x, y);
		return ;
	}
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
			texture->inversed_grayscale_handle, (int)x, (int)y);
}

void	render_ui_texture_inversed(int64_t tex_id, int64_t x, int64_t y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
	{
		render_invalid_texture(x, y);
		return ;
	}
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
			texture->inversed_handle, (int)x, (int)y);
}

void render_invalid_texture(int64_t x, int64_t y)
{
	draw_rect(ivec2(x, y), ivec2(50, 50), trgb(0, 215, 50, 180));
}
