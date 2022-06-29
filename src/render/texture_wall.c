/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/29 17:15:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "texture.h"

t_texture			*get_face_texture(t_ray *ray, t_rgb ***tx_data,
						t_texture *texture);
double				get_texture_position(t_texture *texture, t_ray *ray);
inline static void		render_wall(t_ivec2 pos, t_wall wall, t_ray *ray);

void	render_column(int64_t xcol, t_wall wall, t_ray *ray)
{
	t_ivec2		pos;
	t_vec3		real_light;

	pos = ivec2(xcol, wall.screen_origin);
	real_light = vec3(1.0, 1.0, 1.0);
	wall.size += wall.screen_origin;
	render_wall(pos, wall, ray);
}

inline static void	render_wall(t_ivec2 pos, t_wall wall, t_ray *ray)
{
	t_texture		*texture;
	t_rgb			**tx_data;
	t_rgb			*data;
	t_rgb			color;
	t_render_wall	rwall;

	texture = get_face_texture(ray, &tx_data, NULL);
	data = tx_data[(int64_t)get_texture_position(texture, ray)];
	rwall.ratio = (double)texture->height / (double)wall.real_size;
	rwall.ty = (double)wall.wall_origin * rwall.ratio;
	while (pos.y < wall.size)
	{
		color = data[(int64_t)rwall.ty];
		set_screen_pixel_unsafe(pos.x, pos.y, color.color);
		pos.y++;
		rwall.ty += rwall.ratio;
	}
}
