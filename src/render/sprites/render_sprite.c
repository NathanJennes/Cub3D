/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:25:27 by njennes           #+#    #+#             */
/*   Updated: 2022/06/26 16:47:44 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

inline static int64_t	get_x_position(t_sprite *sprite, double *distance);
inline static int64_t	get_x_from_angle(double angle);
inline static void		draw_sprite(t_rsprite *rsprite, double distance);
inline static void		draw_col_sprite(t_rsprite *rsprite, int64_t x_pos, int64_t tex_x, double distance);

void	render_sprite(t_sprite *sprite)
{
	double		distance;
	int64_t		x_pos;
	t_rsprite	rsprite;

	x_pos = get_x_position(sprite, &distance);
	if (x_pos == -1)
		return ;
	rsprite.size_x = (int64_t)fabs((double)sprite->size.x / (distance * 1) * get_math()->plane_dist);
	if (rsprite.size_x < 2)
		return ;
	rsprite.texture = get_texture_from_id(sprite->tex_id);
	if (get_lights()[sprite->id].enabled)
		rsprite.color = sprite->color;
	else
		rsprite.color = vec3(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0);
	rsprite.size_h = (int64_t)fabs((double)sprite->size.y / distance * get_math()->plane_dist);
	rsprite.ratio_y = (double)rsprite.texture->height / (double)rsprite.size_h;
	rsprite.ratio_x = (double)rsprite.texture->width / (double)rsprite.size_x;
	rsprite.y_base = get_settings()->halfw_h - rsprite.size_h / 2;
	rsprite.y_base -= (int64_t)fabs((double)sprite->pos.z / distance * get_math()->plane_dist);
	rsprite.x_base = x_pos - rsprite.size_x / 2;
	draw_sprite(&rsprite, distance);
}

inline static void		draw_sprite(t_rsprite *rsprite, double distance)
{
	int64_t		i;
	double		tex_x;

	i = 0;
	tex_x = 0;
	while (i < rsprite->size_x)
	{
		if (get_depth_at(rsprite->x_base + i) >= distance)
			draw_col_sprite(rsprite, rsprite->x_base + i, (int64_t)tex_x, distance);
		i++;
		tex_x += rsprite->ratio_x;
	}
}

inline static void		draw_col_sprite(t_rsprite *rsprite, int64_t x_pos, int64_t tex_x, double distance)
{
	int64_t	i;
	double	tex_y;
	t_rgb	color;
	t_vec3	result;

	set_depth_at(x_pos, distance);
	i = 0;
	tex_y = 0;
	while (i < rsprite->size_h)
	{
		if (rsprite->texture->wall[tex_x][(int64_t)tex_y].t < 255)
		{
			color = rsprite->texture->wall[tex_x][(int64_t)tex_y];
			if (!get_app()->mandatory)
			{
				result.x = ((double)color.r * rsprite->color.x);
				result.y = ((double)color.g * rsprite->color.y);
				result.z = ((double)color.b * rsprite->color.z);
				color.color = trgb(color.t, (int) result.x, (int) result.y, (int) result.z);
			}
			set_screen_pixel(x_pos, rsprite->y_base + i, color.color);
		}
		i++;
		tex_y += rsprite->ratio_y;
	}
}

inline static int64_t	get_x_position(t_sprite *sprite, double *distance)
{
	t_player	*player;
	t_math		*math;
	int64_t		x_screen_pos;
	t_vec2		ray;
	double		angle;

	math = get_math();
	player = get_player();
	ray = vec2(sprite->pos.x - player->world_pos.x, sprite->pos.y - player->world_pos.y);
	*distance = sqrt(ft_pow2(ray.x) + ft_pow2(ray.y));
	vec2_normalize(&ray);
	angle = atan2(player->forward.x * ray.y - player->forward.y * ray.x, player->forward.x * ray.x + player->forward.y * ray.y);
	if (angle < -math->r_half_fov || angle > math->r_half_fov)
		return (-1);
	x_screen_pos = get_x_from_angle(angle);
	return (x_screen_pos);
}

inline static int64_t	get_x_from_angle(double angle)
{
	int64_t		start;
	int64_t		end;
	int64_t		current;
	t_settings	*settings;
	double		*lookup;

	settings = get_settings();
	lookup = get_app()->sprite_manager.angle_lookup;
	start = 0;
	end = settings->win_w;
	current = (end + start) / 2;
	while (start < current && end > current)
	{
		if (angle > lookup[current])
			start = current;
		else if (angle < lookup[current])
			end = current;
		else
			return (current);
		current = (end + start) / 2;
	}
	return (current);
}
