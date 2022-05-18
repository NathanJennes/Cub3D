/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 19:57:18 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static void		shoot_rays(float ray_angle, float ray_angle_base);
static void		print_vec(const char *msg, t_vec2 vec);

static t_vec2	calculate_lengths(t_vec2 *ray);
static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos);
static int		get_map_type(int64_t x, int64_t y);

void	render_walls(int fov)
{
	float	dist;
	int64_t	i;
	t_ivec2	end;
	t_vec2	start;
	t_vec2	start_pos;
	t_ivec2	map_pos;

	i = 0;
	start = vec2(get_player()->pos.x - get_player()->right.x * 50,
			get_player()->pos.y - get_player()->right.y * 50);
	while (i < 100)
	{
		start_pos = start;
		vec2_divf(&start_pos, CELL_WIDTH);
		map_pos.x = (int)start_pos.x;
		map_pos.y = (int)start_pos.y;
		dist = shoot_ray(get_player()->forward, start_pos, map_pos);
		if (dist < 0.0f)
		{
			vec2_add(&start, get_player()->right);
			i++;
			continue ;
		}
		end = ivec2(start.x + get_player()->forward.x * dist * CELL_WIDTH,
				start.y + get_player()->forward.y * dist * CELL_WIDTH);
		render_line(v2_to_iv2(start), end, RED, RED);
		vec2_add(&start, get_player()->right);
		i++;
	}
}

static void	shoot_rays(float ray_angle, float ray_angle_base)
{
	size_t	i;
	t_vec2	pos;
	t_ivec2	map_pos;

	pos = get_player()->pos;
	vec2_divf(&pos, CELL_WIDTH);
	map_pos.x = (int)pos.x;
	map_pos.y = (int)pos.y;
	i = 0;
	while (i < WIN_W)
	{
		shoot_ray(vec2(cosf(ray_angle_base), sinf(ray_angle_base)), pos, map_pos);
		ray_angle_base += ray_angle;
		i++;
	}
}

float	shoot_ray(t_vec2 ray, t_vec2 pos, t_ivec2 map_pos)
{
	t_ivec2	step;
	t_vec2	lengths;
	t_vec2	dists;
	t_bool	hit;
	int		side;

	lengths = calculate_lengths(&ray);
	step = calculate_step_dists(&ray, &dists, pos, map_pos);
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
		return (dists.x - lengths.x);
	if (hit && side == SIDE_Y)
		return (dists.y - lengths.y);
	return (-1.0f);
}

static t_vec2 calculate_lengths(t_vec2 *ray)
{
	t_vec2	lengths;

	if (ray->x == 0)
		lengths.x = MAXFLOAT;
	else
		lengths.x = (float)ft_abs(1.0f / ray->x);
	if (ray->y == 0)
		lengths.y = MAXFLOAT;
	else
		lengths.y = (float)ft_abs(1.0f / ray->y);
	return (lengths);
}

static t_ivec2 calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos)
{
	t_ivec2	step;

	if (ray->x > 0)
	{
		step.x = 1;
		dists->x = (float)map_pos.x + 1.0f - pos.x;
	}
	else
	{
		step.x = -1;
		dists->x = pos.x - (float)map_pos.x;
	}
	if (ray->y > 0)
	{
		step.y = 1;
		dists->y = (float)map_pos.y + 1.0f - pos.y;
	}
	else
	{
		step.y = -1;
		dists->y = pos.y - (float)map_pos.y;
	}
	return (step);
}

static float	fast_mag(t_vec2 vec)
{
	return (vec.x * vec.x + vec.y * vec.y);
}

static int	get_map_type(int64_t x, int64_t y)
{
	t_map_info	*map;

	map = get_map_infos();
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (VOID);
	return (map->map[y][x]);
}

static t_vec2	get_grid_pos(t_vec2 pos)
{
	t_vec2	grid_pos;

	grid_pos.x = (int)pos.x - ((int)pos.x % (int)CELL_WIDTH);
	grid_pos.y = (int)pos.y - ((int)pos.y % (int)CELL_HEIGHT);
	return (grid_pos);
}

static void	print_vec(const char *msg, t_vec2 vec)
{
	printf("%s %f %f\n", msg, vec.x, vec.y);
}
