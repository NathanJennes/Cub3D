/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/19 18:29:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

static void	display_hud(t_mlx *app, t_ui *ui);

int	render_ui(void)
{
	t_mlx			*app;
	t_ui			*ui;

	app = get_app();
	ui = get_ui();
	if (app->game_state == IN_GAME)
		display_hud(app, ui);
	if (app->game_state == MENU)
	{
		render_ui_img_box(&ui->main_menu.title);
	}
	if (app->ui.debug_ui & DEBUG_UI)
		fps_counter();
	return (0);
}

void	update_ui(t_bool mouse_clicked)
{
	t_ui_main_menu	*main_menu;

	main_menu = &get_ui()->main_menu;
	update_ui_button(&main_menu->btn_continue);
}

static void	display_hud(t_mlx *app, t_ui *ui)
{
}
