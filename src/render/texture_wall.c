/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/31 13:42:59 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

static t_texture	*get_face_texture(void);
static double		get_texture_position(t_texture *texture);
static int32_t		get_pixel_color_from_texture(int64_t tx, int64_t y,
						t_texture *texture);

void	draw_col_wall(int64_t xcol, t_wall wall)
{
	double		y;
	t_texture	*texture;
	int64_t		tx;
	double		ratio;
	int			px_color;

	y = 0.0;
	texture = get_face_texture();
	tx = get_texture_position(texture);
	ratio = (double)texture->width / (double)wall.real_size;
	while (y < wall.size)
	{
		px_color = get_pixel_color_from_texture(tx, (y + wall.offset) * ratio, texture);
		set_screen_pixel(xcol, y + wall.origin, px_color);
		y++;
	}
}

static int32_t	get_pixel_color_from_texture(int64_t x, int64_t y,
		t_texture *texture)
NOPROF
{
	int32_t		px_color;

	px_color = *(int *)(texture->original + (x * 4) + (y * texture->line_size));
	return (px_color);
}

static double	get_texture_position(t_texture *texture)
{
	double		pos_x;
	int64_t		ratio;

	pos_x = 0;
	if (get_player()->last_ray.side == SIDE_X)
	{
		ratio = (int64_t)get_player()->last_ray.hit_pos.y / CELL_SIZE;
		pos_x = get_player()->last_ray.hit_pos.y - (double)(ratio * CELL_SIZE);
	}
	else if (get_player()->last_ray.side == SIDE_Y)
	{
		ratio = (int64_t)get_player()->last_ray.hit_pos.x / CELL_SIZE;
		pos_x = get_player()->last_ray.hit_pos.x - (double)(ratio * CELL_SIZE);
	}
	return ((pos_x / (double)CELL_SIZE) * (double)texture->width);
}

static t_texture	*get_face_texture(void)
NOPROF
{
	t_texture	*texture;

	texture = NULL;
	if (get_player()->last_ray.side == SIDE_X)
		texture = get_texture_from_id(16);
	else if (get_player()->last_ray.side == SIDE_Y)
		texture = get_texture_from_id(17);
	return (texture);
}
