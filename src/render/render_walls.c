/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/27 16:58:15 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static uint8_t	get_texture_pixel_color(int64_t pos_col, double ratio);
static void		draw_col_wall(int64_t col, double dist, t_vec2 ray);

void	render_walls(void)
{
	int64_t		i;
	t_vec2		ray_direction;
	t_player	*player;
	t_vec2		start;

	i = 0;
	player = get_player();
	start = vec2(player->world_pos.x + player->forward.x - player->right.x * get_math()->plane_len,
			player->world_pos.y + player->forward.y - player->right.y * get_math()->plane_len);
	while (i < WIN_W)
	{
		ray_direction = vec2(start.x - player->world_pos.x, start.y - player->world_pos.y);
		vec2_normalize(&ray_direction);
		player->last_ray = shoot_ray(ray_direction, player->map_pos);
		draw_col_wall(i, player->last_ray.distance, player->last_ray.ray);
		vec2_add(&start, player->plane_inc);
		i++;
	}
}

static void	draw_col_wall(int64_t col, double dist, t_vec2 ray)
{
	int64_t	y;
	int64_t	wall_origin;
	int64_t	wall_size;
	uint8_t	px_color;
	double	angle;

	angle = acos(ft_minf(get_player()->forward.x * ray.x
				+ get_player()->forward.y * ray.y, 1.0));
	dist = dist * cos(angle);
	wall_size = (int64_t)
		fabs(CELL_SIZE / (dist * CELL_SIZE) * get_math()->plane_dist);
	if (wall_size > WIN_H)
		wall_size = WIN_H;
	else if (wall_size < 0)
		return ;
	wall_origin = HALFW_H - (wall_size / 2);
	y = 0;
	while (y < wall_size)
	{
		px_color = get_texture_pixel_color(y, 0);
		set_screen_pixel_unsafe(col, y + wall_origin, px_color);
		y++;
	}
}

static uint8_t	get_texture_pixel_color(int64_t pos_col, double ratio)
{
	t_texture			*texture;
	uint8_t				px_color;
	t_ray				ray;
	int64_t				offset;

	(void)ratio;
	ray = get_player()->last_ray;
	if (get_player()->last_ray.side == SIDE_X)
	{
		texture = get_texture_from_id(1);
		offset = (int64_t)ray.hit_pos.y % CELL_SIZE;
		px_color = texture->ao_flat[offset + pos_col * texture->line_size];
	}
	else if (get_player()->last_ray.side == SIDE_Y)
	{
		texture = get_texture_from_id(2);
		offset = (int64_t)ray.hit_pos.x % CELL_SIZE;
		px_color = texture->ao_flat[offset + pos_col * texture->line_size];
	}
	return (px_color);
}
