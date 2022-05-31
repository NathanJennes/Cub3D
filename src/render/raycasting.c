/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:52:09 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/27 16:39:39 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static t_ray	populate_ray(double dist, t_vec2 ray, t_bool hit, int side) NOPROF;
static t_vec2	calculate_lengths(t_vec2 *ray) NOPROF;
static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos) NOPROF;
static int		get_map_type(int64_t x, int64_t y) NOPROF;

t_ray	shoot_ray(t_vec2 ray, t_vec2 ray_world_pos, t_ivec2 map_pos)
{
	t_ivec2	step;
	t_vec2	lengths;
	t_vec2	dists;
	t_bool	hit;
	int		side;

	if (get_map_type(map_pos.x, map_pos.y) == WALL)
		return (populate_ray(-1.0f, ray, TRUE, NOSIDE));
	vec2_divf(&ray_world_pos, CELL_SIZE);
	lengths = calculate_lengths(&ray);
	step = calculate_step_dists(&ray, &dists, ray_world_pos, map_pos);
	vec2_multv2(&dists, lengths);
	hit = FALSE;
	side = 0;
	while (!hit && (dists.x < RAY_LENGTH || dists.y < RAY_LENGTH))
	{
		if (dists.x < dists.y)
		{
			dists.x += lengths.x;
			map_pos.x += step.x;
			side = SIDE_X;
		}
		else
		{
			dists.y += lengths.y;
			map_pos.y += step.y;
			side = SIDE_Y;
		}
		if (get_map_type(map_pos.x, map_pos.y) == WALL)
			hit = TRUE;
	}
	if (hit && side == SIDE_X)
		return (populate_ray(dists.x - lengths.x, ray, TRUE, side));
	if (hit && side == SIDE_Y)
		return (populate_ray(dists.y - lengths.y, ray, TRUE, side));
	return (populate_ray(-1.0f, ray, FALSE, side));
}

static t_ray	populate_ray(double dist, t_vec2 ray, t_bool hit, int side)
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

static t_vec2	calculate_lengths(t_vec2 *ray)
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

static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos,
		t_ivec2 map_pos)
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

static int	get_map_type(int64_t x, int64_t y)
{
	t_map_info	*map;

	map = get_map_infos();
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (VOID);
	return (map->map[y][x]);
}
