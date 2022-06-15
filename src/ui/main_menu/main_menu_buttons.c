/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_buttons.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:04:40 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 17:26:34 by njennes          ###   ########.fr       */
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
	app->state = IN_GAME;
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
	app->gamestate = app->savegames[0];
	app->state = IN_GAME;
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
