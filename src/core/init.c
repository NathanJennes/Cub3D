/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 21:08:29 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "ui.h"
#include "render.h"
#include <math.h>

int			key_up_callback(int keycode, void *unused);
int			key_down_callback(int keycode, void *unused);
int			mouse_down_callback(int button, int x, int y, void *unused);
int			mouse_up_callback(int button, int x, int y, void *unused);

inline static void	init_hooks(void);
inline static void	init_start_time(void);

void	init_app(char *path)
{
	t_mlx	*app;

	srand(time(0));
	app = get_app();
	app->settings = load_settings();
	init_start_time();
	init_gc();
	init_mlx(app);
	init_font_manager();
	if (path && load_map(&app->gamestate, path))
	{
		app->state = IN_GAME;
		app->renderer.multithreading = FALSE;
		mlx_mouse_hide();
	}
	else if (path)
		close_app();
	load_all_saves();
	load_all_maps();
	printf("Saves loaded: %d\n", (int) app->savegames_count);
	printf("Maps loaded: %d\n", (int) app->maps_count);
	init_window("Cub3d");
	init_math();
	init_ui();
	init_hooks();
	init_renderer();
}

inline static void	init_hooks(void)
{
	t_mlx	*app;

	app = get_app();
	mlx_hook(app->win, 17, 0, close_app, app);
	mlx_hook(app->win, 2, 0, key_down_callback, NULL);
	mlx_hook(app->win, 3, 0, key_up_callback, NULL);
	mlx_hook(app->win, 4, 0, mouse_down_callback, NULL);
	mlx_hook(app->win, 5, 0, mouse_up_callback, NULL);
	mlx_hook(app->win, 6, 0, mouse_move_hooks, app);
	mlx_loop_hook(app->mlx, main_loop, app);
}

inline static void	init_start_time(void)
{
	t_mlx			*app;
	struct timeval	time;

	app = get_app();
	gettimeofday(&time, NULL);
	app->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	app->last_time = app->start_time;
}

void	init_math(void)
{
	t_math		*pc;
	t_settings	*settings;

	settings = get_settings();
	pc = get_math();
	pc->r_fov = settings->fov * (PI / 180.0);
	pc->r_half_fov = settings->fov * (PI / 360.0);
	pc->r_vfov = 2 * atan(tan(pc->r_half_fov) * \
			((double)settings->win_w / (double)settings->win_h));
	pc->r_half_vfov = pc->r_vfov / 2;
	pc->plane_len = tan(pc->r_half_fov);
	pc->plane_dist = settings->halfw_w / (pc->r_vfov / 2);
}
