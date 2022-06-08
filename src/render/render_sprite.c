/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:25:27 by njennes           #+#    #+#             */
/*   Updated: 2022/06/08 18:03:35 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

void	render_sprite(t_sprite *sprite)
{
	t_player	*player;
	t_math		*math;
	t_vec2		ray;
	double		angle;
	double		x_screen_pos;

	math = get_math();
	player = get_player();
	ray = vec2(sprite->pos.x - player->world_pos.x, sprite->pos.y - player->world_pos.y);
	vec2_normalize(&ray);
	angle = atan2(player->forward.x * ray.y - player->forward.y * ray.x, player->forward.x * ray.x + player->forward.y * ray.y);
	angle += math->r_halffov;
	if (angle < 0.0 || angle > math->r_fov)
		return ;
	double a = 40;
	double b = 4;
	double c = 6;
	double d = math->r_fov / 6;
	x_screen_pos = get_settings()->win_w * (angle / math->r_fov);
	x_screen_pos += a * sin(angle * 4);
	x_screen_pos += b * sin(angle * 8);
	if (angle < d || angle > math->r_fov - d)
	{
		x_screen_pos += c * sin(angle * 8);
		//printf("after c: %f\n", x_screen_pos);
	}
	draw_circle(ivec2((int)x_screen_pos, get_settings()->halfw_h), 10, trgb(0, 200, 100, 200));
}
