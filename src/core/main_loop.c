/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/06/21 18:09:37 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "ui.h"
#include "render.h"

inline static void	render_crosshair(void);
inline static void	render_background(t_mlx *app, const t_settings *settings);
inline static void	debug_time_frame(const t_mlx *app, struct timeval *time);
inline static void	render_game(t_mlx *app, const t_settings *settings,
						struct timeval time[4]);

int	main_loop(void)
{
	t_mlx			*app;
	t_settings		*settings;
	struct timeval	time[4];

	app = get_app();
	settings = get_settings();
	if (app->state & IN_GAME)
	{
		if (app->ui.lock_crosshair == TRUE)
			update_player(&app->gamestate.player);
		render_game(app, settings, time);
		if (app->ui.lock_crosshair == TRUE)
			reset_mouse_pos();
	}
	else
		clear_screen(BKGD_COLOR);
	if (get_ui()->debug)
		print_debug();
	fps_counter();
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	if (app->state & IN_GAME)
		render_crosshair();
	update_ui();
	render_ui();
	return (0);
}

inline static void	render_game(t_mlx *app, const t_settings *settings,
		struct timeval time[4])
{
	gettimeofday(&time[0], NULL);
	render_background(app, settings);
	gettimeofday(&time[1], NULL);
	renderer_render();
	gettimeofday(&time[2], NULL);
	render_minimap(1);
	if (get_ui()->debug)
		render_debug(app);
	gettimeofday(&time[3], NULL);
	debug_time_frame(app, time);
}

inline static void	render_background(t_mlx *app, const t_settings *settings)
{
	t_rgb	color;
	t_vec3	res;
	double	shade;
	int64_t	i;

	draw_rect(ivec2(0, 0),
		ivec2(settings->win_w, (int64_t)settings->win_slice),
		get_map_infos()->ceiling.color);
	i = (int64_t)settings->win_slice;
	while (i < (int64_t)(settings->max_lerp))
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
	draw_rect(ivec2(0, (int64_t)settings->win_two_slice),
		ivec2(settings->win_w, (int64_t)settings->win_slice),
		get_map_infos()->floor.color);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}

inline static void	render_crosshair(void)
{
	t_texture	*crosshair;

	crosshair = get_texture_from_id(get_ui()->tx_crosshair);
	render_ui_texture(get_ui()->tx_crosshair,
		get_settings()->halfw_w - crosshair->width / 2,
		get_settings()->halfw_h - crosshair->height / 2);
}

inline static void	debug_time_frame(const t_mlx *app, struct timeval *time)
{
	if (app->ui.debug == TRUE)
		printf("[FRAME - RENDER]: background: %lldms, walls: "
			"%lldms, test_scene: %lldms, total %lldms\n",
			(int64_t)((time[1].tv_sec * 1000 + time[1].tv_usec / 1000)
				- (time[0].tv_sec * 1000 + time[0].tv_usec / 1000)),
			(int64_t)((time[2].tv_sec * 1000 + time[2].tv_usec / 1000)
				- (time[1].tv_sec * 1000 + time[1].tv_usec / 1000)),
			(int64_t)((time[3].tv_sec * 1000 + time[3].tv_usec / 1000)
				- (time[2].tv_sec * 1000 + time[2].tv_usec / 1000)),
			(int64_t)((time[3].tv_sec * 1000 + time[3].tv_usec / 1000)
				- (time[0].tv_sec * 1000 + time[0].tv_usec / 1000)));
}
