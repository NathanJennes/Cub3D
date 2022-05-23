/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/23 21:54:56 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static t_ray	populate_ray(float dist, t_ivec2 hit_pos, t_bool hit, int side);
static t_vec2	calculate_lengths(t_vec2 *ray);
static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos);
static int		get_map_type(int64_t x, int64_t y);
void			draw_col_wall(int64_t col, float start_angle);

void	render_walls(void)
{
	float		start_angle;
	int64_t		i;
	t_vec2		v_ray;
	t_player	*player;
	int64_t		wall_size;

	i = 0;
	player = get_player();
	start_angle = player->ray_angle;
	while (i < WIN_W)
	{
		v_ray = vec2(sinf(start_angle), cosf(start_angle));
		player->last_ray = shoot_ray(v_ray, player->map_pos);
		draw_col_wall(i, start_angle);
		start_angle -= player->ray_increment;
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
		return (populate_ray(0.0f, hit_pos, TRUE, NOSIDE));
	lengths = calculate_lengths(&ray);
	step = calculate_step_dists(&ray, &dists, get_player()->world_pos, hit_pos);
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
		return (populate_ray(dists.x - lengths.x, hit_pos, TRUE, side));
	if (hit && side == SIDE_Y)
		return (populate_ray(dists.y - lengths.y, hit_pos, TRUE, side));
	return (populate_ray(-1.0f, hit_pos, FALSE, side));
}

void	draw_col_wall(int64_t col, float start_angle)
{
	int64_t	y;
	int64_t	wall_origin;
	int64_t	wall_size;

	y = 0;
	printf("Dist %f\n", get_player()->last_ray.distance);
	wall_size = (DFLT_SIZE * WIN_H) / (get_player()->last_ray.distance);
	wall_size = abs(wall_size);
	wall_origin = (WIN_H / 2) - (wall_size / 2);
	if (wall_size > WIN_H)
		wall_size = WIN_H;
	if (wall_origin < 0)
		wall_origin = 0;
	printf("%d -- %d\n", wall_size, wall_origin);
	while (y < WIN_H)
	{
		if (y < wall_origin)
			mlx_pixel_put_img(col, y, CEILLING);
//		else if (y == WIN_H / 2)
//			mlx_pixel_put_img(col, y, GREEN);
		else if (y < (wall_origin + wall_size))
		{
			if (get_player()->last_ray.side == SIDE_X)
				mlx_pixel_put_img(col, y, WALL_COLOR_1);
			else if (get_player()->last_ray.side == SIDE_Y)
				mlx_pixel_put_img(col, y, WALL_COLOR_2);
		}
		else if (y < WIN_H && y > (wall_origin + wall_size))
			mlx_pixel_put_img(col, y, FLOOR);
		y++;
	}
}

static t_ray	populate_ray(float dist, t_ivec2 hit_pos, t_bool hit, int side)
{
	t_ray	ray;

	ray.distance = dist;
	ray.hit_pos = hit_pos;
	ray.hit = hit;
	ray.side = side;
	return (ray);
}

static t_vec2	calculate_lengths(t_vec2 *ray)
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

static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos)
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
	x /= CELL_WIDTH, y /= CELL_WIDTH;
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
