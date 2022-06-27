/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:52:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 16:59:50 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

inline static t_ray	populate_ray(double dist, t_vec2 ray, t_bool hit, int side);
inline static t_vec2	calculate_lengths(t_vec2 *ray);
inline static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists,
						t_vec2 pos, t_ivec2 map_pos);
static void		update_distance(t_ivec2 *map_pos, t_raycasting *r);

t_ray	shoot_ray(t_vec2 ray, t_vec2 ray_world_pos, t_ivec2 map_pos,
		double max_dist)
{
	t_raycasting	r;

	if (get_map_type(map_pos.x, map_pos.y) == WALL)
		return (populate_ray(0, ray, TRUE, NOSIDE));
	vec2_divf(&ray_world_pos, CELL_SIZE);
	r.lengths = calculate_lengths(&ray);
	r.step = calculate_step_dists(&ray, &r.dists, ray_world_pos, map_pos);
	vec2_multv2(&r.dists, r.lengths);
	r.hit = FALSE;
	r.side = NOSIDE;
	while (!r.hit && (r.dists.x < max_dist || r.dists.y < max_dist))
		update_distance(&map_pos, &r);
	if (r.hit && r.side == SIDE_X)
		return (populate_ray(r.dists.x - r.lengths.x, ray, TRUE, r.side));
	if (r.hit)
		return (populate_ray(r.dists.y - r.lengths.y, ray, TRUE, r.side));
	return (populate_ray(RAY_LENGTH, ray, FALSE, NOSIDE));
}

static void	update_distance(t_ivec2 *map_pos, t_raycasting *r)
{
	if ((*r).dists.x < (*r).dists.y)
	{
		(*r).dists.x += (*r).lengths.x;
		(*map_pos).x += (*r).step.x;
		(*r).side = SIDE_X;
	}
	else
	{
		(*r).dists.y += (*r).lengths.y;
		(*map_pos).y += (*r).step.y;
		(*r).side = SIDE_Y;
	}
	if (get_map_type((*map_pos).x, (*map_pos).y) == WALL)
		(*r).hit = TRUE;
}

inline static t_ray	populate_ray(double dist, t_vec2 ray, t_bool hit, int side)
{
	t_ray		result;
	t_player	*player;

	player = get_player();
	result.distance = dist;
	if (hit)
		result.hit_pos = vec2(player->world_pos.x + ray.x * dist * CELL_SIZE,
				player->world_pos.y + ray.y * dist * CELL_SIZE);
	else
		result.hit_pos = vec2_zero();
	result.hit = hit;
	result.side = side;
	result.ray = ray;
	return (result);
}

inline static t_vec2	calculate_lengths(t_vec2 *ray)
{
	t_vec2	lengths;

	if (ray->x == 0)
		lengths.x = MAXFLOAT;
	else
		lengths.x = ft_abs(1.0f / ray->x);
	if (ray->y == 0)
		lengths.y = MAXFLOAT;
	else
		lengths.y = ft_abs(1.0f / ray->y);
	return (lengths);
}

inline static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists,
						t_vec2 pos, t_ivec2 map_pos)
{
	t_ivec2	step;

	if (ray->x > 0)
	{
		step.x = 1;
		dists->x = (double)map_pos.x + 1.0f - pos.x;
	}
	else
	{
		step.x = -1;
		dists->x = pos.x - (double)map_pos.x;
	}
	if (ray->y > 0)
	{
		step.y = 1;
		dists->y = (double)map_pos.y + 1.0f - pos.y;
	}
	else
	{
		step.y = -1;
		dists->y = pos.y - (double)map_pos.y;
	}
	return (step);
}
