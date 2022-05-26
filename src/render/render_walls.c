/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 16:21:18 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

void	draw_col_wall(int64_t col, double dist, t_vec2 ray);

void	render_walls(void)
{
	double		offset;
	int64_t		i;
	t_vec2		ray_direction;
	t_player	*player;
	double		half_width;

	i = 0;
	half_width = tan(get_settings()->fov * PI / 360.0f);
	player = get_player();
	while (i < WIN_W)
	{
		offset = (((double)i * 2.0f / (WIN_W - 1.0f)) - 1.0f) * half_width;
		ray_direction.x = player->forward.x - offset * player->right.x;
		ray_direction.y = player->forward.y - offset * player->right.y;
		vec2_normalize(&ray_direction);
		player->last_ray = shoot_ray(ray_direction, player->map_pos);
		if (player->last_ray.hit == TRUE)
			draw_col_wall(i, player->last_ray.distance, player->last_ray.ray);
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
	wall_size = (int64_t)fabs(DFLT_SIZE / dist);
	if (wall_size > WIN_H)
		wall_size = WIN_H;
	else if (wall_size < 0)
		return ;
	wall_origin = HALFW_H - (wall_size / 2);
	y = 0;
	while (y < wall_size)
	{
		if (get_player()->last_ray.side == SIDE_X)
			set_screen_pixel(col, y + wall_origin, WALL_COLOR_1);
		else if (get_player()->last_ray.side == SIDE_Y)
			set_screen_pixel(col, y + wall_origin, WALL_COLOR_2);
		y++;
	}
}
