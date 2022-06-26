/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listeners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:42:50 by njennes           #+#    #+#             */
/*   Updated: 2022/06/25 18:57:23 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"

inline static void	handle_f1(t_mlx *app);
inline static void	handle_escape(void);
inline static void	handle_tab(t_mlx *app);

int	key_pressed_listener(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode == KEY_BACKSPACE)
		close_app();
	else if (keycode == KEY_TAB)
		handle_tab(app);
	else if (keycode == KEY_ESC)
		handle_escape();
	else if (keycode == KEY_F1)
		handle_f1(app);
	else if (keycode == KEY_F2)
		app->mandatory = !app->mandatory;
	else if (keycode == KEY_F3)
		handle_debug_ui();
	else if (keycode == KEY_F4)
		app->renderer.multithreading = !app->renderer.multithreading;
	return (0);
}

inline static void	handle_tab(t_mlx *app)
{
	if (app->state != IN_GAME)
		return ;
	if (app->ui.state == MAP_MENU)
	{
		app->gamestate.player.lock = FALSE;
		app->ui.state = NONE;
		mlx_mouse_hide();
		reset_mouse_pos();
		return ;
	}
	app->gamestate.player.lock = TRUE;
	app->ui.state = MAP_MENU;
	mlx_mouse_show();
}

inline static void	handle_f1(t_mlx *app)
{
	if (app->ui.state != KEYBINDS_MENU)
	{
		app->ui.prev_state = app->ui.state;
		app->ui.state = MAP_MENU;
		return ;
	}
	app->ui.state = app->ui.prev_state;
}

inline static void	handle_escape(void)
{
	t_mlx	*app;

	app = get_app();
	mlx_mouse_show();
	if (app->state == IN_GAME)
	{
		save_game(app->gamestate.name);
		refresh_main_menu();
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
