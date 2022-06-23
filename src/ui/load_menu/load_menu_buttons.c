/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_menu_buttons.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:17:28 by njennes           #+#    #+#             */
/*   Updated: 2022/06/23 15:51:08 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	btn_back(t_button *button)
{
	t_ui			*ui;
	t_ui_load_menu	*menu;

	(void)button;
	ui = get_ui();
	menu = &ui->load_menu;
	ui->state = MAIN_MENU;
	menu->save_selected = 0;
	return (0);
}

int	btn_next_save(t_button *button)
{
	t_ui			*ui;
	t_ui_load_menu	*menu;

	(void)button;
	ui = get_ui();
	menu = &ui->load_menu;
	menu->save_selected++;
	if (menu->save_selected >= get_app()->savegames_count)
		menu->save_selected = 0;
	refresh_load_menu();
	return (0);
}

int	btn_load_save(t_button *button)
{
	t_ui			*ui;
	t_ui_load_menu	*menu;
	t_mlx			*app;

	(void)button;
	ui = get_ui();
	menu = &ui->load_menu;
	app = get_app();
	app->gamestate = app->savegames[menu->save_selected];
	update_player_direction(get_player(), app->delta_time, FALSE);
	update_player_vectors(get_player());
	init_sprite_manager();
	app->state = IN_GAME;
	mlx_mouse_hide();
	app->ui.lock_crosshair = TRUE;
	reset_mouse_pos();
	return (0);
}

