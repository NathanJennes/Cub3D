/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:57:26 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/14 13:22:41 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "core.h"
#include "input_code.h"
#include "ui.h"

static void	handle_main_menu(int keycode, t_mlx *app);
static void	handle_moving(int keycode, t_mlx *app);

int	mouse_hooks(int mousecode, int x, int y)
{
	t_mlx	*app;

	app = get_app();
	if (mousecode)
		dprintf(STDERR_FILENO, "Mouse: %d\n", mousecode);
	update_slider(&app->ui.map_scale_slider, x, y);
	return (0);
}

int	mouse_move_hooks(int x, int y, void *param)
{
	(void)param;
	cub_get_mouse_pos(x, y);
	return (0);
}

int	key_hooks(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode == KEY_LEFT || keycode == KEY_UP || keycode == KEY_RIGHT
		|| keycode == KEY_DOWN)
	{
		handle_main_menu(keycode, app);
	}
	if (keycode == KEY_ESC)
		close_app();
	if (keycode == KEY_F3)
		update_ui_flags(DEBUG_UI);
	if (keycode == KEY_RETURN)
	{
		app->game_state = IN_GAME;
	}
	else
		handle_moving(keycode, app);
	return (0);
}

static void	handle_main_menu(int keycode, t_mlx *app)
{
	if (keycode == KEY_LEFT){}
	if (keycode == KEY_UP)
	{
		if (app->ui.select_bar_pos.y > 170)
			app->ui.select_bar_pos.y -= 60;
	}
	if (keycode == KEY_RIGHT){}
	if (keycode == KEY_DOWN)
	{
		if (app->ui.select_bar_pos.y < 410)
			app->ui.select_bar_pos.y += 60;
	}
	dprintf(STDERR_FILENO, "%d -- %d\n", (int)app->ui.select_bar_pos.x, (int)app->ui.select_bar_pos.y);
}

static void	handle_moving(int keycode, t_mlx *app)
{
	if (keycode == KEY_W)
		app->gamestate.player.pos.y -= PLAYER_SPEED;
	if (keycode == KEY_S)
		app->gamestate.player.pos.y += PLAYER_SPEED;
	if (keycode == KEY_D)
		app->gamestate.player.pos.x += PLAYER_SPEED;
	if (keycode == KEY_A)
		app->gamestate.player.pos.x -= PLAYER_SPEED;
}
