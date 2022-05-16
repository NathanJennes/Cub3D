/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:57:26 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/16 23:39:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "core.h"
#include "input_code.h"
#include "ui.h"

static void	handle_moving(int keycode, t_mlx *app);

int	mouse_hooks(int mousecode, int x, int y)
{
	(void)x;
	(void)y;
	if (mousecode)
		dprintf(STDERR_FILENO, "Mouse: %d\n", mousecode);
	update_ui(TRUE);
	return (0);
}

int	mouse_move_hooks(int x, int y, void *param)
{
	(void)param;
	cub_update_mouse_pos(x, y);
	update_ui(FALSE);
	return (0);
}

int	key_hooks(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode == KEY_LEFT || keycode == KEY_UP || keycode == KEY_RIGHT
		|| keycode == KEY_DOWN)
	{}
	if (keycode == KEY_ESC)
		close_app();
	if (keycode == KEY_F3)
		update_ui_flags(DEBUG_UI);
	if (keycode == KEY_RETURN)
		app->game_state = IN_GAME;
	else
		handle_moving(keycode, app);
	return (0);
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
