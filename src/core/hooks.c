/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:57:26 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/09 18:04:13 by cybattis         ###   ########.fr       */
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
	t_mlx	*app;

	app = get_app();
	if (mousecode)
		dprintf(STDERR_FILENO, "Mouse: %d\n", mousecode);
	update_slider(&app->map_scale_slider, x, y);
	return (0);
}

int	key_hooks(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode == KEY_LEFT || keycode == KEY_UP || keycode == KEY_RIGHT
		|| keycode == KEY_DOWN)
		dprintf(STDERR_FILENO, "Arrow: %d\n", keycode);
	else if (keycode == KEY_ESC)
		close_app();
	else if (keycode == KEY_F3)
		update_ui_flags(DEBUG_UI);
	else
		handle_moving(keycode, app);
	return (0);
}

static void	handle_moving(int keycode, t_mlx *app)
{
	if (keycode == KEY_W)
		app->player.pos.y -= PLAYER_SPEED;
	if (keycode == KEY_S)
		app->player.pos.y += PLAYER_SPEED;
	if (keycode == KEY_D)
		app->player.pos.x += PLAYER_SPEED;
	if (keycode == KEY_A)
		app->player.pos.x -= PLAYER_SPEED;
}
