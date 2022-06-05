/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/01 17:12:58 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

static t_texture	*get_face_texture(t_ray *ray);
static double		get_texture_position(t_texture *texture, t_ray *ray);
static int32_t		get_pixel_color_from_texture(int64_t tx, int64_t y,
						t_texture *texture);
static t_ivec3		get_lighting_at_col(t_ray *ray);

void	draw_col_wall(int64_t xcol, t_wall wall, t_ray *ray)
{
	int64_t		y;
	t_texture	*texture;
	int64_t		tx;
	double		ratio;
	int			px_color;
	t_ivec3		lighting;

	y = 0;
	texture = get_face_texture(ray);
	tx = (int64_t)get_texture_position(texture, ray);
	ratio = (double)texture->width / (double)wall.real_size;
	lighting = get_lighting_at_col(ray);
	while (y < wall.size)
	{
		px_color = get_pixel_color_from_texture(tx, (y + wall.offset) * ratio, texture);
		px_color = apply_light_to_color(px_color, lighting);
		set_screen_pixel(xcol, y + wall.origin, px_color);
		y++;
	}
}

static t_ivec3		get_lighting_at_col(t_ray *ray)
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

static int32_t	get_pixel_color_from_texture(int64_t x, int64_t y,
		t_texture *texture)
NOPROF
{
	int32_t		px_color;

	px_color = *(int *)(texture->original + (x * 4) + (y * texture->line_size));
	return (px_color);
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

static t_texture	*get_face_texture(t_ray *ray)
NOPROF
{
	t_player	*player;

	player = get_player();
	if (ray->side == SIDE_X)
	{
		if (ray->hit_pos.x < player->world_pos.x)
			return (get_texture_from_id(get_map_infos()->tx_list[3]));
		return (get_texture_from_id(get_map_infos()->tx_list[2]));
	}
	else if (ray->side == SIDE_Y)
	{
		if (ray->hit_pos.y < player->world_pos.y)
			return (get_texture_from_id(get_map_infos()->tx_list[1]));
		return (get_texture_from_id(get_map_infos()->tx_list[0]));
	}
	return (NULL);
}
