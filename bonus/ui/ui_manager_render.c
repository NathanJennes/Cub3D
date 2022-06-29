/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:35:02 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 19:29:46 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

static int	other_ui_render(const t_mlx *app);

int	render_ui(void)
{
	t_mlx			*app;

	app = get_app();
	if (other_ui_render(app))
		return (0);
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

static int	other_ui_render(const t_mlx *app)
{
	if (app->ui.state == KEYBINDS_MENU)
	{
		render_keybindings_menu();
		return (1);
	}
	else if (app->state == IN_GAME && app->ui.state == MAP_MENU)
	{
		render_map_menu();
		return (1);
	}
	if (app->state == IN_GAME)
		return (1);
	return (0);
}
