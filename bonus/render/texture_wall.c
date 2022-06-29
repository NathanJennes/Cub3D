/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 17:29:14 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "texture.h"

t_texture			*get_face_texture(t_ray *ray, t_rgb ***tx_data,
						t_texture *texture);
double				get_texture_position(t_texture *texture, t_ray *ray);
inline static t_rgb		get_color(t_vec3 lighting, t_rgb color, double shade);
inline static double		calculate_shade(t_wall wall);
inline static void		render_wall(t_ivec2 pos, t_wall wall, t_ray *ray,
						t_vec3 lighting);
inline static t_ivec3		get_lighting_at_col(t_ray *ray);

void	render_column(int64_t xcol, t_wall wall, t_ray *ray)
{
	t_ivec2		pos;
	t_ivec3		lighting;
	t_vec3		real_light;

	pos = ivec2(xcol, wall.screen_origin);
	if (!get_app()->mandatory)
	{
		lighting = get_lighting_at_col(ray);
		real_light = vec3((double)lighting.x / 255.0,
				(double)lighting.y / 255.0,
				(double)lighting.z / 255.0);
	}
	else
		real_light = vec3(1.0, 1.0, 1.0);
	wall.size += wall.screen_origin;
	render_wall(pos, wall, ray, real_light);
}

inline static void	render_wall(t_ivec2 pos, t_wall wall, t_ray *ray,
			t_vec3 lighting)
{
	t_texture		*texture;
	t_rgb			**tx_data;
	t_rgb			*data;
	t_rgb			color;
	t_render_wall	rwall;

	rwall.shade = calculate_shade(wall);
	set_depth_at(pos.x, ray->distance * CELL_SIZE);
	texture = get_face_texture(ray, &tx_data, NULL);
	data = tx_data[(int64_t)get_texture_position(texture, ray)];
	rwall.ratio = (double)texture->height / (double)wall.real_size;
	rwall.ty = (double)wall.wall_origin * rwall.ratio;
	while (pos.y < wall.size)
	{
		color = data[(int64_t)rwall.ty];
		if (!get_app()->mandatory)
			color = get_color(lighting, color, rwall.shade);
		set_screen_pixel_unsafe(pos.x, pos.y, color.color);
		pos.y++;
		rwall.ty += rwall.ratio;
	}
}

inline static t_rgb	get_color(t_vec3 lighting, t_rgb color, double shade)
{
	t_vec3	result;

	result.x = (double)((color.r * lighting.x) * shade);
	result.y = (double)((color.g * lighting.y) * shade);
	result.z = (double)((color.b * lighting.z) * shade);
	if (result.x > 255.0)
		result.x = 255.0;
	if (result.y > 255.0)
		result.y = 255.0;
	if (result.z > 255.0)
		result.z = 255.0;
	color.color = trgb(color.t, (int) result.x, (int) result.y, (int) result.z);
	return (color);
}

inline static double	calculate_shade(t_wall wall)
{
	t_settings	*settings;
	double		shade;

	settings = get_settings();
	if ((double)wall.screen_origin < settings->win_slice)
		return (1.0);
	if ((double)wall.screen_origin >= settings->win_slice)
	{
		shade = ft_ilerpf(settings->max_lerp, settings->win_slice,
				(double)wall.screen_origin);
		return (shade);
	}
	return (0);
}

inline static t_ivec3	get_lighting_at_col(t_ray *ray)
{
	t_ivec3	result;
	t_vec3	normal;
	t_vec3	pos;

	normal = vec3_zero();
	pos = vec3(ray->hit_pos.x, ray->hit_pos.y, CELL_SIZE / 2.0);
	if (ray->side == SIDE_X)
	{
		normal.x = -ray->ray.x;
		pos.x -= ray->ray.x;
	}
	else if (ray->side == SIDE_Y)
	{
		normal.y = -ray->ray.y;
		pos.y -= ray->ray.y;
	}
	vec3_normalize(&normal);
	result = get_lighting_level(pos, normal);
	ivec3_clamp_min(&result, 25, 25, 25);
	return (result);
}
