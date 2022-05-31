/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/30 16:55:54 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static void			get_correct_distance(void);
static	t_wall		get_wall_info(void);
void				draw_col_wall(int64_t col, t_wall wall);


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
		ray_direction = \
			vec2(start.x - player->world_pos.x, start.y - player->world_pos.y);
		vec2_normalize(&ray_direction);
		player->last_ray = shoot_ray(ray_direction, player->world_pos, player->map_pos);
		draw_col_wall(i, get_wall_info());
		vec2_add(&start, player->plane_inc);
		i++;
	}
}

static	t_wall	get_wall_info(void)
{
	t_wall	wall;

	get_correct_distance();
	wall.size = (int64_t)
		fabs(CELL_SIZE / (get_player()->last_ray.distance * CELL_SIZE)
			* get_math()->plane_dist);
	wall.real_size = wall.size;
	wall.offset = (wall.real_size - WIN_H) / 2;
	if (wall.offset < 0)
		wall.offset = 0;
	if (wall.size > WIN_H)
		wall.size = WIN_H;
	else if (wall.size < 0)
		wall.size = 0;
	wall.origin = HALFW_H - (wall.size / 2);
	return (wall);
}

static void	get_correct_distance(void)
{
	double		angle;
	t_player	*player;

	player = get_player();
	angle = acos(ft_minf(get_player()->forward.x * player->last_ray.ray.x
				+ get_player()->forward.y * player->last_ray.ray.y, 1.0));
	player->last_ray.distance *= cos(angle);
}
