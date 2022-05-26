/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 15:04:57 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static t_ray	populate_ray(double dist, t_vec2 ray, t_bool hit, int side);
static t_vec2	calculate_lengths(t_vec2 *ray);
static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos);
static int		get_map_type(int64_t x, int64_t y);
void			draw_col_wall(int64_t col, double dist, t_vec2 ray);

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
		offset = ((i * 2.0f / (WIN_W - 1.0f)) - 1.0f) * half_width;
		ray_direction.x = player->forward.x - offset * player->right.x;
		ray_direction.y = player->forward.y - offset * player->right.y;
		vec2_normalize(&ray_direction);
		player->last_ray = shoot_ray(ray_direction, player->map_pos);
		if (player->last_ray.hit == TRUE)
			draw_col_wall(i, player->last_ray.distance, player->last_ray.ray);
		i++;
	}
}

t_ray	shoot_ray(t_vec2 ray, t_ivec2 hit_pos)
{
	t_ivec2	step;
	t_vec2	lengths;
	t_vec2	dists;
	t_bool	hit;
	int		side;

	if (get_map_type(hit_pos.x, hit_pos.y) == WALL)
		return (populate_ray(-1.0f, ray, TRUE, NOSIDE));
	lengths = calculate_lengths(&ray);
	step = calculate_step_dists(&ray, &dists, get_player()->cell_pos, hit_pos);
	vec2_multv2(&dists, lengths);
	hit = FALSE;
	side = 0;
	while (!hit && (dists.x < RAY_LENGTH || dists.y < RAY_LENGTH))
	{
		if (dists.x < dists.y)
		{
			dists.x += lengths.x;
			hit_pos.x += step.x;
			side = SIDE_X;
		}
		else
		{
			dists.y += lengths.y;
			hit_pos.y += step.y;
			side = SIDE_Y;
		}
		if (get_map_type(hit_pos.x, hit_pos.y) == WALL)
			hit = TRUE;
	}
	if (hit && side == SIDE_X)
		return (populate_ray(dists.x - lengths.x, ray, TRUE, side));
	if (hit && side == SIDE_Y)
		return (populate_ray(dists.y - lengths.y, ray, TRUE, side));
	return (populate_ray(-1.0f, ray, FALSE, side));
}

void	draw_col_wall(int64_t col, double dist, t_vec2 ray)
{
	int64_t	y;
	int64_t	wall_origin;
	int64_t	wall_size;
	double	angle;
	t_vec2	*pf;

	pf = &get_player()->forward;
	angle = acos((pf->x * ray.x + pf->y * ray.y) / (vec2_mag(*pf) * vec2_mag(ray)));
	if (angle < 1)
		dist = dist * cos(angle);
	y = 0;
	wall_size = DFLT_SIZE / dist;
	wall_size = llabs(wall_size);
	if (wall_size < 0)
		printf("> %lf %f %lf\n", pf->x * ray.x + pf->y * ray.y, (vec2_mag(*pf) * vec2_mag(ray)), angle);
	wall_origin = (WIN_H / 2) - (wall_size / 2);
	if (wall_size > WIN_H)
		wall_size = WIN_H;
	if (wall_origin < 0)
		wall_origin = 0;
	while (y < WIN_H)
	{
		if (y < wall_origin)
			set_screen_pixel(col, y, CEILLING);
		else if (y < (wall_origin + wall_size))
		{
			if (get_player()->last_ray.side == SIDE_X)
				set_screen_pixel(col, y, WALL_COLOR_1);
			else if (get_player()->last_ray.side == SIDE_Y)
				set_screen_pixel(col, y, WALL_COLOR_2);
		}
		else if (y < WIN_H && y > (wall_origin + wall_size))
			set_screen_pixel(col, y, FLOOR);
		y++;
	}
}

static t_ray	populate_ray(double dist, t_vec2 ray, t_bool hit, int side)
{
	t_ray		result;
	t_player	*player;

	player = get_player();
	result.distance = dist;
	if (hit)
		result.hit_pos = vec2(player->world_pos.x + ray.x * dist * CELL_WIDTH,
			player->world_pos.y + ray.y * dist * CELL_WIDTH);
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
		lengths.x = (double)ft_abs(1.0f / ray->x);
	if (ray->y == 0)
		lengths.y = MAXFLOAT;
	else
		lengths.y = (double)ft_abs(1.0f / ray->y);
	return (lengths);
}

static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos)
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
