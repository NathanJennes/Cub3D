/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/21 18:14:44 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "texture.h"

inline static double	calculate_shade(t_wall wall);
inline static void		render_wall(t_ivec2 pos, t_wall wall, t_ray *ray,
							t_vec3 lighting);
inline static t_texture	*get_face_texture(t_ray *ray, t_rgb ***tx_data);
inline static double	get_texture_position(t_texture *texture, t_ray *ray);
inline static t_ivec3	get_lighting_at_col(t_ray *ray);

void	render_column(int64_t xcol, t_wall wall, t_ray *ray)
{
	t_ivec2		pos;
	t_ivec3		lighting;
	t_vec3		real_light;

	pos = ivec2(xcol, wall.screen_origin);
	lighting = get_lighting_at_col(ray);
	if (!get_app()->mandatory)
	{
		real_light = vec3((double) lighting.x / 255.0,
				(double) lighting.y / 255.0,
				(double) lighting.z / 255.0);
	}
	else
		real_light = vec3(1.0, 1.0, 1.0);
	wall.size += wall.screen_origin;
	render_wall(pos, wall, ray, real_light);
}

inline static void	render_wall(t_ivec2 pos, t_wall wall, t_ray *ray, t_vec3 lighting)
{
	double		ratio;
	t_texture	*texture;
	t_rgb		**tx_data;
	t_rgb		*data;
	t_rgb		color;
	t_vec3		result;
	int64_t		tx;
	double		ty;
	double		shade;

	shade = calculate_shade(wall);
	set_depth_at(pos.x, ray->distance * CELL_SIZE);
	texture = get_face_texture(ray, &tx_data);
	tx = (int64_t)get_texture_position(texture, ray);
	data = tx_data[tx];
	ratio = (double)texture->height / (double)wall.real_size;
	ty = (double)wall.wall_origin * ratio;
	while (pos.y < wall.size)
	{
		if ((double)wall.screen_origin < get_settings()->max_lerp)
		{
			color = data[(int64_t) ty];
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
		}
		else
			color.color = BLACK;
		set_screen_pixel_unsafe(pos.x, pos.y, color.color);
		pos.y++;
		ty += ratio;
	}
}

inline static double	calculate_shade(t_wall wall)
{
	t_settings	*settings;
	double		shade;

	settings = get_settings();
	if ((double)wall.screen_origin > settings->max_lerp)
		return (0);
	if ((double)wall.screen_origin >= settings->win_slice)
	{
		shade = ft_ilerpf(settings->max_lerp, settings->win_slice,
				(double)wall.screen_origin);
		return (shade);
	}
	return (1.0);
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

inline static double	get_texture_position(t_texture *texture, t_ray *ray)
{
	double		pos_x;
	int64_t		ratio;

	pos_x = 0;
	if (ray->side == SIDE_X)
	{
		ratio = (int64_t)ray->hit_pos.y / CELL_SIZE;
		pos_x = ray->hit_pos.y - (double)(ratio * CELL_SIZE);
	}
	else if (ray->side == SIDE_Y)
	{
		ratio = (int64_t)ray->hit_pos.x / CELL_SIZE;
		pos_x = ray->hit_pos.x - (double)(ratio * CELL_SIZE);
	}
	return ((pos_x / (double)CELL_SIZE) * (double)texture->width);
}

inline static t_texture	*get_face_texture(t_ray *ray, t_rgb ***tx_data)
NOPROF
{
	t_texture	*texture;
	t_player	*player;

	player = get_player();
	texture = NULL;
	if (ray->side == SIDE_X)
	{
		if (ray->hit_pos.x < player->world_pos.x)
		{
			texture = get_texture_from_id(get_map_infos()->tx_list[3]);
			*tx_data = texture->vflip;
			return (texture);
		}
		texture = get_texture_from_id(get_map_infos()->tx_list[2]);
		*tx_data = texture->ao_flat;
		return (texture);
	}
	if (ray->hit_pos.y < player->world_pos.y)
	{
		texture = get_texture_from_id(get_map_infos()->tx_list[1]);
		*tx_data = texture->ao_flat;
		return (texture);
	}
	texture = get_texture_from_id(get_map_infos()->tx_list[0]);
	*tx_data = texture->vflip;
	return (texture);
}
