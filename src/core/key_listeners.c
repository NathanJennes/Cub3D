/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listeners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:42:50 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 15:44:33 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"

static void	handle_moving(int keycode, t_mlx *app);

int	key_pressed_listener(int keycode)
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
