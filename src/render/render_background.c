/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:13:23 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/22 13:39:10 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "ui.h"
#include "render.h"

void	render_background_gradian(t_mlx *app, const t_settings *settings)
{
	t_rgb	color;
	t_vec3	res;
	double	shade;
	int64_t	i;

	draw_rect(ivec2(0, 0),
		ivec2(settings->win_w, (int64_t)settings->win_slice),
		get_map_infos()->ceiling.color);
	i = (int64_t)settings->win_slice;
	while (i <= (int64_t)(settings->max_lerp))
	{
		shade = ft_ilerpf(settings->halfw_h,
				settings->win_slice, (double)i);
		res.x = (double)(get_map_infos()->ceiling.r * shade);
		res.y = (double)(get_map_infos()->ceiling.g * shade);
		res.z = (double)(get_map_infos()->ceiling.b * shade);
		color.color = trgb(0, (int)res.x, (int)res.y, (int)res.z);
		draw_line(ivec2(0, i), ivec2(settings->win_w, i), color.color);
		draw_line(ivec2(0, settings->win_h - i),
			ivec2(settings->win_w, settings->win_h - i), color.color);
		i++;
	}
	draw_rect(ivec2(0, (int64_t)settings->max_lerp + 1),
		ivec2(settings->win_w, (int64_t)settings->max_dist + 1), BLACK);
	draw_rect(ivec2(0, (int64_t)settings->win_two_slice),
		ivec2(settings->win_w, (int64_t)settings->win_slice),
		get_map_infos()->floor.color);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}

void	render_background(t_mlx *app, const t_settings *settings)
{
	draw_rect(ivec2(0, 0),
		ivec2(settings->win_w, settings->halfw_h),
		get_map_infos()->ceiling.color);
	draw_rect(ivec2(0, (int64_t)(settings->halfw_h)),
		ivec2(settings->win_w, settings->halfw_h),
		get_map_infos()->floor.color);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}
