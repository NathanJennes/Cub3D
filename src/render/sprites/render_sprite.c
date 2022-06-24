/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:25:27 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 17:09:24 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

inline static int64_t	get_x_position(t_sprite *sprite, double *distance);
inline static int64_t	get_x_from_angle(double angle);
inline static void		draw_sprite(t_sprite *sprite, int64_t x_pos, double distance);
inline static void		draw_col_sprite(t_sprite *sprite, int64_t x_pos, int64_t tex_x, double distance);

void	render_sprite(t_sprite *sprite)
{
	double	distance;
	int64_t x_pos;

	x_pos = get_x_position(sprite, &distance);
	if (x_pos == -1)
		return ;
	draw_sprite(sprite, x_pos, distance);
}

inline static void		draw_sprite(t_sprite *sprite, int64_t x_pos, double distance)
{
	int64_t		i;
	int64_t		size_x;
	int64_t		x_base;
	double		ratio;
	double		tex_x;
	t_texture	*texture;

	texture = get_texture_from_id(sprite->tex_id);
	size_x = (int64_t)fabs((double)sprite->size.x / (distance * 1) * get_math()->plane_dist);
	if (size_x < 2)
		return ;
	ratio = (double)texture->width / (double)size_x;
	x_base = x_pos - size_x / 2;
	i = 0;
	tex_x = 0;
	while (i < size_x)
	{
		if (get_depth_at(x_base + i) >= distance)
			draw_col_sprite(sprite, x_base + i, (int64_t)tex_x, distance);
		i++;
		tex_x += ratio;
	}
}

inline static void		draw_col_sprite(t_sprite *sprite, int64_t x_pos, int64_t tex_x, double distance)
{
	int64_t		i;
	int64_t		size_h;
	int64_t		y_base;
	double		ratio;
	double		tex_y;
	t_texture	*texture;

	set_depth_at(x_pos, distance);
	texture = get_texture_from_id(sprite->tex_id);
	size_h = (int64_t)fabs((double)sprite->size.y / distance * get_math()->plane_dist);
	ratio = (double)texture->height / (double)size_h;
	y_base = get_settings()->halfw_h - size_h / 2;
	y_base -= (int64_t)fabs((double)sprite->pos.z / distance * get_math()->plane_dist);
	i = 0;
	tex_y = 0;
	while (i < size_h)
	{
		if (texture->wall[tex_x][(int64_t)tex_y].t < 255)
			set_screen_pixel(x_pos, y_base + i, texture->wall[tex_x][(int64_t)tex_y].color);
		i++;
		tex_y += ratio;
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
