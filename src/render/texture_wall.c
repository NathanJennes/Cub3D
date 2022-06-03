/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/03 17:35:08 by Cyril            ###   ########.fr       */
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
	int64_t		y;
	t_texture	*texture;
	int64_t		tx;
	double		ratio;
	int			px_color;

	y = 0;
	texture = get_face_texture();
	if (!texture)
		return ;
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
	t_player	*player;

	player = get_player();
	if (get_player()->last_ray.side == SIDE_X)
	{
		if (player->last_ray.hit_pos.x < player->world_pos.x)
			return (get_texture_from_id(get_map_infos()->tx_list[3]));
		return (get_texture_from_id(get_map_infos()->tx_list[2]));
	}
	else if (get_player()->last_ray.side == SIDE_Y)
	{
		if (player->last_ray.hit_pos.y < player->world_pos.y)
			return (get_texture_from_id(get_map_infos()->tx_list[1]));
		return (get_texture_from_id(get_map_infos()->tx_list[0]));
	}
	return (NULL);
}
