/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 17:11:36 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "ui.h"
#include "render.h"
#include <math.h>

int				key_up_callback(int keycode, void *unused);
int				key_down_callback(int keycode, void *unused);
int				mouse_down_callback(int button, int x, int y, void *unused);
int				mouse_up_callback(int button, int x, int y, void *unused);
void 			start_game(void);

static void		init_hooks(void);


void	init_app(char *path)
{
	t_mlx	*app;

	app = get_app();
	init_gc();
	app->settings = load_settings();
	init_window("Cub3d");
	init_texture_manager();
	update_precalc();
	init_hooks();
	if (load_map(&app->gamestate, path))
		start_game();
	else
		ft_error_exit("Error: couldn't load specified map\n");
}

void start_game(void)
{
	update_player_direction(get_player(), FALSE);
	update_player_vectors(get_player());
	mlx_mouse_hide();
	reset_mouse_pos();
}

static void	init_hooks(void)
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

void	update_precalc(void)
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
	settings->win_slice = (double)settings->win_h / 3;
	settings->win_two_slice = settings->win_slice * 2;
	settings->max_dist = fabs((double)1 / RAY_LENGTH * get_math()->plane_dist);
	settings->max_lerp = settings->halfw_h - (settings->max_dist / 2);
}
