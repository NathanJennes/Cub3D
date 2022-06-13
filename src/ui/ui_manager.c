/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/13 23:31:13 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

void	update_main_menu_click_begin(int mouse_btn);
void	update_main_menu_click_end(int mouse_btn);

void	update_new_game_menu_click_begin(int mouse_btn);
void	update_new_game_menu_click_end(int mouse_btn);

void	update_settings_menu_click_begin(int button);
void	update_settings_menu_click_end(int button);

int	render_ui(void)
{
	t_mlx			*app;

	app = get_app();
	if (app->app_state == IN_MENU)
	{
		if (app->ui.state == MAIN_MENU)
			render_main_menu();
		else if (app->ui.state == NEW_GAME_MENU)
			render_new_game_menu();
		else if (app->ui.state == OPTION_MENU)
			render_settings_menu();
	}
	if (get_ui()->debug)
		print_debug();
	return (0);
}

void	update_ui(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu();
	else if (app->ui.state == NEW_GAME_MENU)
		update_new_game_menu();
	else if (app->ui.state == OPTION_MENU)
		update_settings_menu();
}

void	update_ui_click_begin(int button)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu_click_begin(button);
	else if (app->ui.state == NEW_GAME_MENU)
		update_new_game_menu_click_begin(button);
	else if (app->ui.state == OPTION_MENU)
		update_settings_menu_click_begin(button);
}

void	update_ui_click_end(int button)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu_click_end(button);
	else if (app->ui.state == NEW_GAME_MENU)
	{
		update_new_game_menu_click_end(button);
		if (app->ui.new_game_menu.btn_start.clicked == TRUE)
			reset_mouse_pos();
	}
	else if (app->ui.state == OPTION_MENU)
		update_settings_menu_click_end(button);
}
