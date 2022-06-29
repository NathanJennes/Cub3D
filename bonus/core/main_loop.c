/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/06/28 20:51:11 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "ui.h"
#include "render.h"

void				render_crosshair(void);
void				debug_time_frame(const t_mlx *app, struct timeval *time);
inline static void		render_background_gradian(t_mlx *app,
						const t_settings *settings);
inline static void		render_game(t_mlx *app, const t_settings *settings,
						struct timeval time[4]);
inline static void		render_gradian(t_mlx *app, const t_settings *settings);
inline static t_vec3		get_res_color(t_rgb base_color, double shade);

int	main_loop(void)
{
	t_mlx			*app;
	t_settings		*settings;
	struct timeval	time[4];

	app = get_app();
	settings = get_settings();
	if (app->state == IN_GAME)
	{
		if (app->gamestate.player.lock == FALSE)
		{
			update_player(&app->gamestate.player, TRUE);
			reset_mouse_pos();
		}
		render_game(app, settings, time);
	}
	print_debug();
	fps_counter();
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	render_crosshair();
	update_ui();
	render_ui();
	return (0);
}

inline static void	render_game(t_mlx *app, const t_settings *settings,
		struct timeval time[4])
{
	gettimeofday(&time[0], NULL);
	if (get_app()->mandatory)
	{
		draw_rect_unsafe(ivec2(0, 0),
			ivec2(settings->win_w, settings->halfw_h),
			get_map_infos()->ceiling.color);
		draw_rect_unsafe(ivec2(0, settings->halfw_h),
			ivec2(settings->win_w, settings->halfw_h),
			get_map_infos()->floor.color);
		mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	}
	else
	{
		render_background_gradian(app, settings);
		render_gradian(app, settings);
	}
	gettimeofday(&time[1], NULL);
	renderer_render();
	render_sprites();
	gettimeofday(&time[2], NULL);
	render_minimap(1);
	gettimeofday(&time[3], NULL);
	render_debug(app);
	debug_time_frame(app, time);
}

inline static void	render_background_gradian(t_mlx *app,
					const t_settings *settings)
{
	t_rgb	color_c;
	t_rgb	color_f;
	double	shade;
	t_vec3	res;
	int64_t	i;

	draw_rect_unsafe(ivec2(0, 0),
		ivec2(settings->win_w, (int64_t)settings->win_slice),
		get_map_infos()->ceiling.color);
	i = (int64_t)settings->win_slice - 1;
	while (++i <= (int64_t)(settings->max_lerp))
	{
		shade = ft_ilerpf(settings->halfw_h,
				settings->win_slice, (double)i);
		res = get_res_color(get_map_infos()->ceiling, shade);
		color_c.color = trgb(0, (int)res.x, (int)res.y, (int)res.z);
		res = get_res_color(get_map_infos()->floor, shade);
		color_f.color = trgb(0, (int)res.x, (int)res.y, (int)res.z);
		ft_memseti((int *)app->frame.addr + i * settings->win_w,
			color_c.color, settings->win_w);
		ft_memseti(
			(int *)app->frame.addr + (settings->win_h - i) * settings->win_w,
			color_f.color, settings->win_w);
	}
}

inline static t_vec3	get_res_color(t_rgb base_color, double shade)
{
	t_vec3	res;

	res.x = (double)(base_color.r * shade);
	res.y = (double)(base_color.g * shade);
	res.z = (double)(base_color.b * shade);
	return (res);
}

inline static void	render_gradian(t_mlx *app, const t_settings *settings)
{
	draw_rect_unsafe(ivec2(0, (int64_t)settings->max_lerp + 1),
		ivec2(settings->win_w, (int64_t)settings->max_dist + 1), BLACK);
	draw_rect_unsafe(ivec2(0, (int64_t)settings->win_two_slice),
		ivec2(settings->win_w, (int64_t)settings->win_slice),
		get_map_infos()->floor.color);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}
