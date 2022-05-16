/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/16 22:09:00 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

static void	display_hud(t_mlx *app, t_ui *ui);

int	update_ui(void)
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

static void	display_hud(t_mlx *app, t_ui *ui)
{
}
