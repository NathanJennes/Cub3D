/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:25:27 by njennes           #+#    #+#             */
/*   Updated: 2022/06/07 19:53:18 by njennes          ###   ########.fr       */
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
	x_screen_pos = get_settings()->win_w * (angle / math->r_fov);
	draw_circle(ivec2((int)x_screen_pos, get_settings()->halfw_h), 10, trgb(0, 200, 100, 200));
}
