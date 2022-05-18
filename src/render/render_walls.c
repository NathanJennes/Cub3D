/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/17 22:24:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static void		shoot_rays(float ray_angle, float ray_angle_base);
static void		shoot_ray(t_vec2 ray, t_vec2 pos);
static t_vec2	project_pos(float ray_angle, t_vec2 pos);
static t_vec2	get_grid_pos(t_vec2 pos);
static void		print_vec(const char *msg, t_vec2 vec);
static t_vec2	go_to_first_intersection(t_vec2 pos, t_vec2 x_inc, t_vec2 y_inc);

void	render_walls(int fov)
{
	float	ray_angle;
	float	ray_angle_base;

	get_player()->pos = vec2(60, 60);
	ray_angle = (float)WIN_W / (float)fov;
	ray_angle_base = PI / 5;//((float)PI - ((float)fov / 180.0f)) / 2.0f;
	shoot_rays(ray_angle, ray_angle_base);
}

static void	shoot_rays(float ray_angle, float ray_angle_base)
{
	size_t	i;
	t_vec2	pos;

	pos = get_player()->pos;
	i = 0;
	while (i < 1)
	{
		shoot_ray(vec2(cos(ray_angle_base), sin(ray_angle_base)), pos);
		ray_angle_base += ray_angle;
		i++;
	}
}

static void	shoot_ray(t_vec2 ray, t_vec2 pos)
{
	t_vec2	vertical_inc;
	t_vec2	horizontal_inc;
	t_vec2	vertical_pos;
	t_vec2	horizontal_pos;

	pos = project_pos(ray_angle, pos);
	print_vec("inter at", pos);
	vertical_pos = pos;
	horizontal_pos = pos;
}

static t_vec2	project_pos(float ray_angle, t_vec2 pos)
{
	t_vec2	grid_pos;
	t_vec2	x_inc;
	t_vec2	y_inc;

	grid_pos = get_grid_pos(pos);
	print_vec("player_pos", pos);
	print_vec("grid_pos", grid_pos);
	if (ray_angle < PI / 2 || ray_angle > 3 * PI / 2)
		x_inc.x = grid_pos.x + CELL_WIDTH - pos.x;
	else
		x_inc.x = grid_pos.x - pos.x;
	if (ray_angle == PI / 2 || ray_angle == 2 * PI / 3)
		x_inc.x = 0;
	x_inc.y = tan(ray_angle) * ft_abs(x_inc.x);
	if (ray_angle < PI)
		y_inc.y = grid_pos.y - pos.y;
	else
		y_inc.y = grid_pos.y + CELL_HEIGHT - pos.y;
	if (ray_angle == 0 || ray_angle == PI)
		y_inc.y = 0;
	y_inc.x = tan(PI / 2 - ray_angle) * ft_abs(y_inc.y);
	return (go_to_first_intersection(pos, x_inc, y_inc));
}

static float	fast_mag(t_vec2 vec)
{
	return (vec.x * vec.x + vec.y * vec.y);
}

static int	get_map_type(int x, int y)
{
	t_map_info	*map;

	map = get_map_infos();
	return (map->map[y][x]);
}

static t_vec2	go_to_first_intersection(t_vec2 pos, t_vec2 x_inc, t_vec2 y_inc)
{
	t_vec2	grid_pos;
	t_vec2	pos_copy;

	pos_copy = pos;
	print_vec("x_inc", x_inc);
	print_vec("y_inc", y_inc);
	if (fast_mag(x_inc) < fast_mag(y_inc))
	{
		printf("x_inc before\n");
		vec2_add(&pos, x_inc);
		return (pos);
	}
	printf("y_inc before\n");
	vec2_add(&pos, y_inc);
	return (pos);
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
