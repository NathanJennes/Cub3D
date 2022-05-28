/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/28 19:02:52 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static void			get_correct_distance(void);
static t_texture	*get_face_texture(void);
static int64_t		get_texture_offset(t_texture *texture, t_wall wall);
static void			draw_col_wall(int64_t col, double dist, t_texture *texture);
static int32_t		get_pixel_color_from_texture(t_ivec2 pixel_pos,
						t_texture *texture, t_wall wall);

void	render_walls(void)
{
	int64_t		i;
	t_vec2		ray_direction;
	t_player	*player;
	t_vec2		start;

	i = 0;
	player = get_player();
	start = vec2(player->world_pos.x + player->forward.x
			- player->right.x * get_math()->plane_len,
			player->world_pos.y + player->forward.y
			- player->right.y * get_math()->plane_len);
	while (i < WIN_W)
	{
		ray_direction = vec2(start.x - player->world_pos.x, start.y - player->world_pos.y);
		vec2_normalize(&ray_direction);
		player->last_ray = shoot_ray(ray_direction, player->map_pos);
		get_correct_distance();
		draw_col_wall(i, player->last_ray.distance, get_face_texture());
		vec2_add(&start, player->plane_inc);
		i++;
	}
}

static void	draw_col_wall(int64_t col, double dist, t_texture *texture)
{
	double		y;
	int64_t		ty;
	t_wall		wall;
	int			px_color;
	double		ratio;

	wall.size = (int64_t)
		fabs(CELL_SIZE / (dist * CELL_SIZE) * get_math()->plane_dist);
	if (wall.size > WIN_H)
		wall.size = WIN_H;
	else if (wall.size < 0)
		return ;
	y = 0.0;
	ty = 0;
	wall.origin = HALFW_H - (wall.size / 2);
	ratio = (double)(texture->width / 2) / (double)wall.size;
	while (ty < wall.size)
	{
		px_color = get_pixel_color_from_texture(ivec2(col, y), texture, wall);
		set_screen_pixel(col, ty + wall.origin, px_color);
		y += ratio;
		ty++;
	}
}

static int32_t	get_pixel_color_from_texture(t_ivec2 pixel_pos,
		t_texture *texture, t_wall wall)
{
	int32_t		px_color;
	int64_t		offset;
	int64_t		tx_pos;

	offset = get_texture_offset(texture, wall);
	tx_pos = ((offset + pixel_pos.x) * 4) + (pixel_pos.y * texture->line_size);
	px_color = *(int *)(texture->original + tx_pos);
	return (px_color);
}

static int64_t	get_texture_offset(t_texture *texture, t_wall wall)
{
	int64_t	offset;

	offset = 0;
	if (get_player()->last_ray.side == SIDE_X)
		offset = (((int64_t)get_player()->last_ray.hit_pos.y % CELL_SIZE) * wall.size) / texture->width;
	else if (get_player()->last_ray.side == SIDE_Y)
		offset = (((int64_t)get_player()->last_ray.hit_pos.x % CELL_SIZE) * wall.size) / texture->width;
	return (offset);
}

static t_texture	*get_face_texture(void)
{
	t_texture	*texture;

	texture = NULL;
	if (get_player()->last_ray.side == SIDE_X)
		texture = get_texture_from_id(13);
	else if (get_player()->last_ray.side == SIDE_Y)
		texture = get_texture_from_id(13);
	return (texture);
}


void	get_correct_distance(void)
{
	double		angle;
	t_player	*player;

	player = get_player();
	angle = acos(ft_minf(get_player()->forward.x * player->last_ray.ray.x
						 + get_player()->forward.y * player->last_ray.ray.y, 1.0));
	player->last_ray.distance *= cos(angle);
}
