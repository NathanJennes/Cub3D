/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listeners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:42:50 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 17:15:59 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"

inline static void	handle_escape(void);

int	key_pressed_listener(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode == KEY_BACKSPACE)
		close_app();
	else if (keycode == KEY_F3)
		switch_debug_ui();
	else if (keycode == KEY_TAB)
	{
		app->ui.lock_crosshair = !app->ui.lock_crosshair;
		if (app->ui.lock_crosshair == TRUE)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
	else if (keycode == KEY_ESC)
		handle_escape();
	else if (keycode == KEY_F4)
		app->renderer.multithreading = !app->renderer.multithreading;
	else if (keycode == KEY_F10)
		app->mandatory = !app->mandatory;
	return (0);
}

inline static void	handle_escape(void)
{
	t_mlx	*app;

	app = get_app();
	mlx_mouse_show();
	if (app->state == IN_GAME)
	{
		save_game(app->gamestate.name);
		app->state = IN_MENU;
		app->ui.state = MAIN_MENU;
		mlx_mouse_show();
	}
	else if (app->state == IN_MENU)
	{
		if (app->ui.state == NEW_GAME_MENU)
			app->ui.state = MAIN_MENU;
		else if (app->ui.state == LOAD_MENU)
			app->ui.state = MAIN_MENU;
		else if (app->ui.state == OPTION_MENU)
			app->ui.state = MAIN_MENU;
		else if (app->ui.state == MAIN_MENU)
			close_app();
	}
}
