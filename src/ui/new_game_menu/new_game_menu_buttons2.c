/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game_menu_buttons2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:09:40 by njennes           #+#    #+#             */
/*   Updated: 2022/06/17 15:45:22 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	btn_new_game_back(t_button *button)
{
	t_ui	*ui;

	(void)button;
	ui = get_ui();
	ui->state = MAIN_MENU;
	return (0);
}

int	btn_new_game_down(t_button *button)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)button;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 5 < app->maps_count)
		menu->first_save_offset++;
	printf("btn_new_game_down not implemented\n");
	return (0);
}

int	btn_new_game_up(t_button *button)
{
	t_ui_new_game_menu	*menu;

	(void)button;
	menu = &get_ui()->new_game_menu;
	if (menu->first_save_offset > 0)
		menu->first_save_offset--;
	printf("btn_new_game_up not implemented\n");
	return (0);
}

int	btn_start_new_game(t_button *button)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)button;
	menu = &get_ui()->new_game_menu;
	if (menu->selected_save != -1)
	{
		app = get_app();
		printf("Creating a new game from map: %s\n",
			app->maps[menu->selected_save
			+ menu->first_save_offset].name);
		app->gamestate = app->maps[menu->selected_save
			+ menu->first_save_offset];
		update_player_vectors(get_player());
		init_sprite_manager();
		printf("selected save:\nF: ");
		ft_print_vec3(vec3((double)app->gamestate.map.floor.r,
			(double)app->gamestate.map.floor.g, (double)app->gamestate.map.floor.b));
		printf("C ");
		ft_print_vec3(vec3((double)app->gamestate.map.floor.r,
			(double)app->gamestate.map.floor.g, (double)app->gamestate.map.floor.b));
		printf("NORTH: %s, EAST: %s, SOUTH: %s, WEST: %s\n", get_texture_from_id(app->gamestate.map.tx_list[NORTH])->name,
			get_texture_from_id(app->gamestate.map.tx_list[EAST])->name,
			get_texture_from_id(app->gamestate.map.tx_list[SOUTH])->name,
			get_texture_from_id(app->gamestate.map.tx_list[WEST])->name);
		app->state = IN_GAME;
	}
	return (0);
}
