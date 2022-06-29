/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 19:09:48 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

inline static void		get_correct_distance(t_ray *ray);
inline static t_wall		get_wall_info(t_ray *ray);
void				render_column(int64_t xcol, t_wall wall, t_ray *ray);

void	render_walls(int64_t col_start, int64_t col_end)
{
	int64_t		i;
	t_player	*player;
	t_vec2		start;
	t_ray		ray;
	double		offset;

	i = col_start;
	offset = 1.0 - ((double)i / (double)get_settings()->win_w) * 2.0;
	player = get_player();
	start = vec2(player->world_pos.x + player->forward.x
			- player->right.x * (get_math()->plane_len * offset),
			player->world_pos.y + player->forward.y
			- player->right.y * (get_math()->plane_len * offset));
	while (i <= col_end)
	{
		ray.direction = \
			vec2(start.x - player->world_pos.x, start.y - player->world_pos.y);
		vec2_normalize(&ray.direction);
		ray = shoot_ray(ray.direction, player->world_pos,
				player->map_pos, RAY_LENGTH);
		if (ray.hit)
			render_column(i, get_wall_info(&ray), &ray);
		vec2_add(&start, player->plane_inc);
		i++;
	}
}

inline static	t_wall	get_wall_info(t_ray *ray)
{
	t_wall		wall;
	t_settings	*settings;

	settings = get_settings();
	get_correct_distance(ray);
	wall.size = (int64_t)fabs(1 / ray->distance * get_math()->plane_dist);
	wall.real_size = wall.size;
	wall.wall_origin = (wall.real_size - settings->win_h) / 2;
	if (wall.wall_origin < 0)
		wall.wall_origin = 0;
	if (wall.size > settings->win_h)
		wall.size = settings->win_h;
	else if (wall.size < 0)
		wall.size = 0;
	wall.screen_origin = settings->halfw_h - (wall.size / 2);
	return (wall);
}

inline static void	get_correct_distance(t_ray *ray)
{
	double		angle;

	angle = acos(ft_minf(get_player()->forward.x * ray->ray.x
				+ get_player()->forward.y * ray->ray.y, 1.0));
	ray->distance *= cos(angle);
}
