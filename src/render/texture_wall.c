/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/31 19:26:34 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include <math.h>

static t_texture	*get_face_texture(void);
static int64_t		get_texture_position(t_texture *texture);
static int32_t		get_pixel_color_from_texture(int64_t tx, int64_t y,
						t_texture *texture);

void	draw_col_wall(int64_t xcol, t_wall wall)
{
	double		y;
	t_texture	*texture;
	int64_t		tx;
	int			ratio;
	int			px_color;

	y = 0.0;
	texture = get_face_texture();
	if (!texture)
	{
		printf("Texture NULL\n");
		return ;
	}
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

static int64_t	get_texture_position(t_texture *texture)
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
	return ((pos_x / CELL_SIZE) * texture->width);
}

static t_texture	*get_face_texture(void)
{
	double	direction;

	printf("side %d\n", get_player()->last_ray.side);
	direction = atan2(sin(get_player()->last_ray.direction.x),
			cos(get_player()->last_ray.direction.y));
	if (get_player()->last_ray.side == SIDE_X)
	{
		if (direction > PI)
			return (get_texture_from_id(get_map_infos()->tx_list[3]));
		return (get_texture_from_id(get_map_infos()->tx_list[2]));
	}
	else if (get_player()->last_ray.side == SIDE_Y)
	{
		if (direction > HALF_PI && direction < M_3_PI_2)
			return (get_texture_from_id(get_map_infos()->tx_list[1]));
		return (get_texture_from_id(get_map_infos()->tx_list[0]));
	}
	return (NULL);
}
