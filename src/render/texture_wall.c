/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/15 15:34:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "texture.h"

void				render_floor(t_ivec2 pos, t_wall wall, t_ray *ray,
						t_ivec3 lighting);
static void			render_wall(t_ivec2 pos, t_wall wall, t_ray *ray,
						t_ivec3 lighting);

static t_texture	*get_face_texture(t_ray *ray, t_rgb ***tx_data);
static double		get_texture_position(t_texture *texture, t_ray *ray);
static t_ivec3		get_lighting_at_col(t_ray *ray);

void	render_column(int64_t xcol, t_wall wall, t_ray *ray)
{
	t_ivec2		pos;
	t_ivec3		lighting;

	pos = ivec2(xcol, 0);
	lighting = get_lighting_at_col(ray);
	render_wall(pos, wall, ray, lighting);
//	render_floor(pos, wall, ray, lighting);
}

static void	render_wall(t_ivec2 pos, t_wall wall, t_ray *ray, t_ivec3 lighting)
{
	double		ratio;
	t_texture	*texture;
	t_rgb		**tx_data;
	int64_t		tx;
	double		ty;
	int			px_color;

	set_depth_at(pos.x, ray->distance * CELL_SIZE);
	texture = get_face_texture(ray, &tx_data);
	tx = (int64_t)get_texture_position(texture, ray);
	ratio = (double)texture->height / (double)wall.real_size;
	ty = (double)wall.wall_origin * ratio;
	pos.y += wall.screen_origin;
	wall.size += wall.screen_origin;
	while (pos.y < wall.size)
	{
		px_color = tx_data[tx][(int64_t)ty].color;
		px_color = apply_light_to_color(px_color, lighting);
		set_screen_pixel_unsafe(pos.x, pos.y, px_color);
		pos.y++;
		ty += ratio;
	}
}

static t_ivec3	get_lighting_at_col(t_ray *ray)
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

static double	get_texture_position(t_texture *texture, t_ray *ray)
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

static t_texture	*get_face_texture(t_ray *ray, t_rgb ***tx_data)
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
