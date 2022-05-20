/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game_menu_buttons.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:09:40 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 19:54:47 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	btn_select_save1(t_button *button)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)button;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset > app->maps_count)
		return (0);
	menu->selected_save = menu->first_save_offset;
	return (0);
}

int	btn_select_save2(t_button *button)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)button;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 1 > app->maps_count)
		return (0);
	menu->selected_save = menu->first_save_offset + 1;
	return (0);
}

int	btn_select_save3(t_button *button)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)button;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 2 > app->maps_count)
		return (0);
	menu->selected_save = menu->first_save_offset + 2;
	return (0);
}

int	btn_select_save4(t_button *button)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)button;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 3 > app->maps_count)
		return (0);
	menu->selected_save = menu->first_save_offset + 3;
	return (0);
}

int	btn_select_save5(t_button *button)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)button;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 4 > app->maps_count)
		return (0);
	menu->selected_save = menu->first_save_offset + 4;
	return (0);
}
