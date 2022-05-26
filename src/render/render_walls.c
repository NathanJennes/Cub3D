/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 20:11:58 by njennes          ###   ########.fr       */
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
	double		start_angle;

	i = 0;
	player = get_player();
	start_angle = get_math()->base_angle;
	while (i < WIN_W)
	{
		ray_direction = vec2(sin(start_angle), cos(start_angle));
		vec2_normalize(&ray_direction);
		player->last_ray = shoot_ray(ray_direction, player->map_pos);
		draw_col_wall(i, player->last_ray.distance, player->last_ray.ray);
		start_angle -= get_math()->angle_inc;
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

	pf = &get_player()->forward;
	angle = acos((pf->x * ray.x + pf->y * ray.y)
			/ (vec2_mag(*pf) * vec2_mag(ray)));
	if (angle <= 1)
		dist = dist * cos(angle);
	double	plane_dist = HALFW_W / (get_math()->r_vfov / 2);
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
