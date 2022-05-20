/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/19 19:28:20 by njennes          ###   ########.fr       */
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
		if (app->ui.state == MAIN_MENU)
			update_main_menu();
	}
	if (app->ui.debug_ui & DEBUG_UI)
		fps_counter();
	return (0);
}

void	update_ui(t_bool mouse_clicked)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu();
}

static void	display_hud(t_mlx *app, t_ui *ui)
{
}
