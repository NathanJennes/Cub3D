/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/16 18:57:26 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

static void	display_hud(t_mlx *app, t_ui *ui);

int	ui_manager(void)
{
	t_mlx			*app;
	t_ui			*ui;

	app = get_app();
	ui = get_ui();
	if (app->game_state == IN_GAME)
		display_hud(app, ui);
	if (app->game_state == MENU)
	{}
	if (app->ui.debug_ui & DEBUG_UI)
		fps_counter();
	return (0);
}

void	update_ui_flags(uint8_t flag)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.debug_ui & flag)
		app->ui.debug_ui ^= flag;
	else
		app->ui.debug_ui |= flag;
}

static void	display_hud(t_mlx *app, t_ui *ui)
{
}
