/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 16:15:08 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

int			key_up_callback(int keycode, void *unused);
int			key_down_callback(int keycode, void *unused);
int			mouse_down_callback(int button, int x, int y, void *unused);
int			mouse_up_callback(int button, int x, int y, void *unused);

static void	init_hooks(void);

void	init_app(void)
{
	t_mlx	*app;

	app = get_app();
	init_gc();
	init_window("Cub3d");
	init_font_manager();
	load_all_saves();
	load_all_maps();
	printf("Saves loaded: %d\n", (int)app->savegames_count);
	printf("Maps loaded: %d\n", (int)app->maps_count);
	init_ui();
	init_hooks();
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
