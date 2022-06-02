/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stb47 <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/06/02 15:50:53 by stb47            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "io.h"
#include "ui.h"
#include "render.h"
#include <math.h>

int			key_up_callback(int keycode, void *unused);
int			key_down_callback(int keycode, void *unused);
int			mouse_down_callback(int button, int x, int y, void *unused);
int			mouse_up_callback(int button, int x, int y, void *unused);

static void	init_hooks(void);
static void	init_start_time(void);

void	init_app(void)
{
	t_mlx	*app;

	srand(time(0));
	app = get_app();
	app->settings = load_settings();
	init_start_time();
	init_gc();
	init_window("Cub3d");
	init_font_manager();
	load_all_saves();
	load_all_maps();
	printf("Saves loaded: %d\n", (int)app->savegames_count);
	printf("Maps loaded: %d\n", (int)app->maps_count);
	init_math();
	init_ui();
	init_hooks();
	init_renderer();
	printf("%lld\n", load_texture("assets/texture_06.xpm"));
	printf("%lld\n", load_texture("assets/texture_09.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_01.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_02.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_03.xpm"));
}

void	init_app_linux(char *path)
{
	t_mlx	*app;

	srand(time(0));
	app = get_app();
	app->settings = load_settings();
	init_start_time();
	init_gc();
	init_window("Cub3d");
	if (!load_map(&app->gamestate, path))
		exit(1);
	init_math();
	init_hooks();
	init_renderer();
	app->app_state = IN_GAME;
	printf("%lld\n", load_texture("assets/texture_06.xpm"));
	printf("%lld\n", load_texture("assets/texture_09.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_01.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_02.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_03.xpm"));
}

static void	init_hooks(void)
{
	t_mlx	*app;

	app = get_app();
	app->app_state = IN_MENU;
	mlx_hook(app->win, 17, 0, close_app, app);
	mlx_hook(app->win, 2, 0, key_down_callback, NULL);
	mlx_hook(app->win, 3, 0, key_up_callback, NULL);
	mlx_hook(app->win, 4, 0, mouse_down_callback, NULL);
	mlx_hook(app->win, 5, 0, mouse_up_callback, NULL);
	mlx_hook(app->win, 6, 0, mouse_move_hooks, app);
	mlx_loop_hook(app->mlx, main_loop, app);
}

static void	init_start_time(void)
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
	update_player_vectors(get_player());
	pc = get_math();
	pc->r_fov = settings->fov * (PI / 180.0);
	pc->r_halffov = settings->fov * (PI / 360.0);
	pc->r_vfov = 2 * atan(tan(pc->r_halffov) * ((double)settings->win_w / (double)settings->win_h));
	pc->plane_len = tan(pc->r_halffov);
	pc->plane_dist = settings->halfw_w / (get_math()->r_vfov / 2);
}
