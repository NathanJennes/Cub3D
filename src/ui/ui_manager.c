/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/26 18:41:02 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

void	update_main_menu_click_begin(int mouse_btn);
void	update_main_menu_click_end(int mouse_btn);

void	update_new_game_menu_click_begin(int mouse_btn);
void	update_new_game_menu_click_end(int mouse_btn);

int	render_ui(void)
{
	t_mlx			*app;

	app = get_app();
	if (app->game_state == MENU)
	{
		if (app->ui.state == MAIN_MENU)
			render_main_menu();
		else if (app->ui.state == NEW_GAME_MENU)
			render_new_game_menu();
	}
	if (get_ui()->debug_ui)
		print_debug();
	return (0);
}

void	update_ui(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu();
	else if (app->ui.state == NEW_GAME_MENU)
		update_new_game_menu();
}

void	update_ui_click_begin(int button)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu_click_begin(button);
	else if (app->ui.state == NEW_GAME_MENU)
		update_new_game_menu_click_begin(button);
}

void	update_ui_click_end(int button)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.state == MAIN_MENU)
		update_main_menu_click_end(button);
	else if (app->ui.state == NEW_GAME_MENU)
		update_new_game_menu_click_end(button);
}
