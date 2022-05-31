/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/30 17:20:47 by cybattis         ###   ########.fr       */
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

static void	init_hooks(void);
static void	init_start_time(void);
static void	init_math(void);

void	init_app(void)
{
	t_mlx	*app;

	app = get_app();
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
	printf("%lld\n", load_texture("assets/texture_06.xpm"));
	printf("%lld\n", load_texture("assets/texture_09.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_01.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_02.xpm"));
	printf("%lld\n", load_texture("assets/wall_texture_03.xpm"));
	mlx_loop(get_mlx());
}

static void	init_hooks(void)
{
	t_mlx	*app;

	app = get_app();
	app->game_state = MENU;
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
}

static void	init_math(void)
{
	t_math		*pc;
	t_settings	*settings;

	settings = get_settings();
	settings->fov = 90;
	update_player_vectors(get_player());
	pc = get_math();
	pc->r_fov = settings->fov * (PI / 180.0);
	pc->r_halffov = settings->fov * (PI / 360.0);
	pc->r_vfov = 2 * atan(tan(pc->r_halffov) * ((double)WIN_W / (double)WIN_H));
	pc->plane_len = tan(pc->r_halffov);
	pc->plane_dist = HALFW_W / (get_math()->r_vfov / 2);
}
