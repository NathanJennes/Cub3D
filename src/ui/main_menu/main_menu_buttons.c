/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_buttons.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:04:40 by njennes           #+#    #+#             */
/*   Updated: 2022/06/25 18:37:07 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

int	btn_continue(t_button *button)
{
	t_mlx	*app;

	(void)button;
	app = get_app();
	app->gamestate = app->savegames[0];
	update_player_direction(get_player(), app->delta_time, FALSE);
	update_player_vectors(get_player());
	init_sprite_manager();
	app->state = IN_GAME;
	mlx_mouse_hide();
	reset_mouse_pos();
	return (0);
}

int	btn_new_game(t_button *button)
{
	t_mlx	*app;

	(void)button;
	app = get_app();
	app->ui.state = NEW_GAME_MENU;
	return (0);
}

int	btn_load_game(t_button *button)
{
	t_mlx	*app;

	(void)button;
	app = get_app();
	refresh_load_menu();
	app->ui.state = LOAD_MENU;
	return (0);
}

int	btn_editor(t_button *button)
{
	(void)button;
	printf("Editor button not implemented\n");
	return (0);
}

int	btn_option(t_button *button)
{
	t_ui	*ui;

	(void)button;
	ui = get_ui();
	ui->state = OPTION_MENU;
	return (0);
}
