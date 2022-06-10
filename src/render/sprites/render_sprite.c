/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:25:27 by njennes           #+#    #+#             */
/*   Updated: 2022/06/10 14:26:22 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <sys/time.h>
#include "core.h"
#include "render.h"

int64_t	get_x_screen_pos(double angle);

void	render_sprite(t_sprite *sprite)
{
	t_player	*player;
	t_math		*math;
	t_vec2		ray;
	double		angle;
	int64_t		x_screen_pos;

	math = get_math();
	player = get_player();
	ray = vec2(sprite->pos.x - player->world_pos.x, sprite->pos.y - player->world_pos.y);
	vec2_normalize(&ray);
	angle = atan2(player->forward.x * ray.y - player->forward.y * ray.x, player->forward.x * ray.x + player->forward.y * ray.y);
	if (angle < -math->r_halffov || angle > math->r_halffov)
		return ;
	x_screen_pos = get_x_screen_pos(angle);
	draw_circle(ivec2((int)x_screen_pos, get_settings()->halfw_h), 10, trgb(0, 200, 100, 200));
}

int64_t	get_x_screen_pos(double angle)
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
