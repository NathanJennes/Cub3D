/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 12:58:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

void	update_main_menu_click_begin(int mouse_btn);
void	update_main_menu_click_end(int mouse_btn);

int	render_ui(void)
{
	t_mlx			*app;

	app = get_app();
	if (app->game_state == MENU)
	{
		if (app->ui.state == MAIN_MENU)
			render_main_menu();
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

void	update_ui_click_begin(int button)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu_click_begin(button);
}


void	update_ui_click_end(int button)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu_click_end(button);
}
