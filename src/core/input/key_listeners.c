/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listeners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:42:50 by njennes           #+#    #+#             */
/*   Updated: 2022/06/13 23:16:16 by Cyril            ###   ########.fr       */
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
	else if (keycode == KEY_ESC)
		handle_escape();
	else if (keycode == KEY_F4)
		app->renderer.multithreading = !app->renderer.multithreading;
	return (0);
}

inline static void	handle_escape(void)
{
	t_mlx	*app;

	app = get_app();
	mlx_mouse_show();
	if (app->app_state == IN_GAME)
	{
		save_game(app->gamestate.name);
		app->app_state = IN_MENU;
		app->ui.state = MAIN_MENU;
	}
	else if (app->app_state == IN_MENU)
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
