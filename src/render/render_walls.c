/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 10:34:45 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static void		print_rays(int64_t i, t_vec2 start, t_ivec2 end, float dist);
static void		shoot_rays(float ray_angle, float ray_angle_base);

static t_vec2	calculate_lengths(t_vec2 *ray);
static t_ivec2	calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos);
static int		get_map_type(int64_t x, int64_t y);
void			draw_col_wall(float dist, int64_t col);

void print_ray(t_vec2 *pos, t_ivec2 *map_pos);

void	render_walls(int fov)
{
	float		ray_angle;
	float		ray_angle_base;

	ray_angle = ((float)fov) / 180.0f / (float)WIN_W;
	ray_angle_base = get_player()->direction + ((float)fov / 360.0f);
	while (ray_angle_base < 0.0f)
		ray_angle_base += 2.0f * PI;
	printf("Direction [%f]\n", get_player()->direction);
	ft_print_vec2(get_player()->forward);
	printf("angle_inc [%f]\n base [%f]\n", ray_angle, ray_angle_base);
	shoot_rays(ray_angle, ray_angle_base);
}

static void	shoot_rays(float ray_angle, float ray_angle_base)
{
	float	dist;
	int64_t	i;
	t_vec2	pos;
	t_ivec2	map_pos;

	pos = get_player()->pos;
	vec2_divf(&pos, CELL_WIDTH);
	map_pos.x = (int)pos.x;
	map_pos.y = (int)pos.y;
	i = 0;
	while (i < WIN_W)
	{
		dist = shoot_ray(vec2(cosf(ray_angle_base), sinf(ray_angle_base)), pos, map_pos);
//		draw_col_wall(dist * (float)cos(ray_angle_base), i);
		ray_angle_base += ray_angle;
		i++;
	}
}

void	draw_col_wall(float dist, int64_t col)
{
	int64_t	y;
	int64_t	out_size;
	int64_t	wall_size;

	y = 0;
	wall_size = WIN_H - DFLT_SIZE * dist;
	out_size = (WIN_H - wall_size) * 0.5;
	while (y < out_size)
		mlx_pixel_put_img(col, y++, BLACK);
	while (y < wall_size)
		mlx_pixel_put_img(col, y++, RED);
	while (y < WIN_H)
		mlx_pixel_put_img(col, y++, BLACK);
}

float	shoot_ray(t_vec2 ray, t_vec2 pos, t_ivec2 map_pos)
{
	t_ivec2	step;
	t_vec2	lengths;
	t_vec2	dists;
	t_bool	hit;
	int		side;

	if (get_map_type(map_pos.x, map_pos.y) == WALL)
	{
		print_ray(&pos, &map_pos);
		return (0);
	}
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
		{
			hit = TRUE;
			print_ray(&pos, &map_pos);
		}
	}
	if (hit && side == SIDE_X)
		return (dists.x - lengths.x);
	if (hit && side == SIDE_Y)
		return (dists.y - lengths.y);
	return (-1.0f);
}

void print_ray(t_vec2 *pos, t_ivec2 *map_pos)
{
//	ft_print_ivec2((*map_pos));
	t_vec2 start = vec2((*pos).x * CELL_WIDTH, (*pos).y * CELL_WIDTH);
	t_ivec2 line_end = ivec2((*map_pos).x * CELL_WIDTH, (*map_pos).y * CELL_WIDTH);
	render_line(v2_to_iv2(start), line_end, RED, RED);
	render_circle(line_end, 5, YELLOW);
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
