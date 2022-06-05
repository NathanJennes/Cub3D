/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/06/05 16:46:31 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static void			get_correct_distance(t_ray *ray);
static t_wall		get_wall_info(t_ray *ray);
void				draw_col_wall(int64_t col, t_wall wall, t_ray *ray);

void	render_walls(int64_t col_start, int64_t col_end)
{
	int64_t		i;
	t_vec2		ray_direction;
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
		ray_direction = \
			vec2(start.x - player->world_pos.x, start.y - player->world_pos.y);
		vec2_normalize(&ray_direction);
		ray = shoot_ray(ray_direction, player->world_pos, player->map_pos);
		draw_col_wall(i, get_wall_info(&ray), &ray);
		vec2_add(&start, player->plane_inc);
		i++;
	}
}

static	t_wall	get_wall_info(t_ray *ray)
{
	t_wall		wall;
	t_settings	*settings;

	settings = get_settings();
	get_correct_distance(ray);
	wall.size = (int64_t)
		fabs(CELL_SIZE / (ray->distance * CELL_SIZE)
			* get_math()->plane_dist);
	wall.real_size = wall.size;
	wall.offset = (wall.real_size - settings->win_h) / 2;
	if (wall.offset < 0)
		wall.offset = 0;
	if (wall.size > settings->win_h)
		wall.size = settings->win_h;
	else if (wall.size < 0)
		wall.size = 0;
	wall.origin = settings->halfw_h - (wall.size / 2);
	return (wall);
}

static void	get_correct_distance(t_ray *ray)
{
	double		angle;

	angle = acos(ft_minf(get_player()->forward.x * ray->ray.x
				+ get_player()->forward.y * ray->ray.y, 1.0));
	ray->distance *= cos(angle);
}
