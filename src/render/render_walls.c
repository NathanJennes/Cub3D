/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/27 14:36:38 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

void	draw_col_wall(int64_t col, double dist, t_vec2 ray);

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

void	draw_col_wall(int64_t col, double dist, t_vec2 ray)
{
	int64_t	y;
	int64_t	wall_origin;
	int64_t	wall_size;
	double	angle;
	t_vec2	*pf;
	double	plane_dist;

	pf = &get_player()->forward;
	angle = acos(ft_minf(pf->x * ray.x + pf->y * ray.y, 1.0));
	dist = dist * cos(angle);
	plane_dist = HALFW_W / (get_math()->r_vfov / 2);
	wall_size = (int64_t)fabs(CELL_WIDTH / (dist * CELL_WIDTH) * plane_dist);
	if (wall_size > WIN_H)
		wall_size = WIN_H;
	else if (wall_size < 0)
		return ;
	wall_origin = HALFW_H - (wall_size / 2);
	y = 0;
	while (y < wall_size)
	{
		if (get_player()->last_ray.side == SIDE_X)
			set_screen_pixel_unsafe(col, y + wall_origin, WALL_COLOR_1);
		else if (get_player()->last_ray.side == SIDE_Y)
			set_screen_pixel_unsafe(col, y + wall_origin, WALL_COLOR_2);
		y++;
	}
}
