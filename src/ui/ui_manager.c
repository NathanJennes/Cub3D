/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/26 18:05:05 by cybattis         ###   ########.fr       */
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

void	update_load_menu_click_begin(int mouse_btn);
void	update_load_menu_click_end(int mouse_btn);

void	update_map_menu_click_begin(int mouse_btn);
void	update_map_menu_click_end(int mouse_btn);

int	render_ui(void)
{
	t_mlx			*app;

	app = get_app();
	if (app->state != IN_MENU)
	{
		if (app->ui.state == KEYBINDS_MENU)
			print_keybindings();
		else if (app->ui.state == MAP_MENU)
			render_map_menu();
		return (0);
	}
	mlx_mouse_show();
	if (app->ui.state == MAIN_MENU)
	{
		if (app->maps_count > 0)
			render_main_menu_background();
		else
			clear_screen(BKGD_COLOR);
		render_main_menu();
	}
	else if (app->ui.state == NEW_GAME_MENU)
		render_new_game_menu();
	else if (app->ui.state == OPTION_MENU)
		render_settings_menu();
	else if (app->ui.state == LOAD_MENU)
		render_load_menu();
	return (0);
}

void	update_ui(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->state != IN_MENU)
	{
		if (app->ui.state == MAP_MENU)
			update_map_menu();
		return ;
	}
	if (app->ui.state == MAIN_MENU)
		update_main_menu();
	else if (app->ui.state == NEW_GAME_MENU)
		update_new_game_menu();
	else if (app->ui.state == OPTION_MENU)
		update_settings_menu();
	else if (app->ui.state == LOAD_MENU)
		update_load_menu();
}

void	update_ui_click_begin(int button)
{
	t_mlx	*app;

	app = get_app();
	if (app->state != IN_MENU)
	{
		if (app->ui.state == MAP_MENU)
			update_map_menu_click_begin(button);
		return ;
	}
	if (app->ui.state == MAIN_MENU)
		update_main_menu_click_begin(button);
	else if (app->ui.state == NEW_GAME_MENU)
		update_new_game_menu_click_begin(button);
	else if (app->ui.state == OPTION_MENU)
		update_settings_menu_click_begin(button);
	else if (app->ui.state == LOAD_MENU)
		update_load_menu_click_begin(button);
}

void	update_ui_click_end(int button)
{
	t_mlx	*app;

	app = get_app();
	if (app->state != IN_MENU)
	{
		if (app->ui.state == MAP_MENU)
			update_map_menu_click_end(button);
		return;
	}
	if (app->ui.state == MAIN_MENU)
		update_main_menu_click_end(button);
	else if (app->ui.state == NEW_GAME_MENU)
		update_new_game_menu_click_end(button);
	else if (app->ui.state == OPTION_MENU)
		update_settings_menu_click_end(button);
	else if (app->ui.state == LOAD_MENU)
		update_load_menu_click_end(button);
}
