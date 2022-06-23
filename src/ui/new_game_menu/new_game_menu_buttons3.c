/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game_menu_buttons3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:01:37 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 13:03:08 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	btn_unselect_save1(t_checkbox *checkbox)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)checkbox;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset > app->maps_count)
		return (0);
	menu->selected_save = -1;
	menu->btn_start.is_clickable = FALSE;
	menu->btn_save[0].checked = FALSE;
	menu->btn_save[1].checked = FALSE;
	menu->btn_save[2].checked = FALSE;
	menu->btn_save[3].checked = FALSE;
	menu->btn_save[4].checked = FALSE;
	return (0);
}

int	btn_unselect_save2(t_checkbox *checkbox)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)checkbox;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 1 > app->maps_count)
		return (0);
	menu->selected_save = -1;
	menu->btn_start.is_clickable = FALSE;
	menu->btn_save[0].checked = FALSE;
	menu->btn_save[1].checked = FALSE;
	menu->btn_save[2].checked = FALSE;
	menu->btn_save[3].checked = FALSE;
	menu->btn_save[4].checked = FALSE;
	return (0);
}

int	btn_unselect_save3(t_checkbox *checkbox)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)checkbox;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 2 > app->maps_count)
		return (0);
	menu->selected_save = -1;
	menu->btn_start.is_clickable = FALSE;
	menu->btn_save[0].checked = FALSE;
	menu->btn_save[1].checked = FALSE;
	menu->btn_save[2].checked = FALSE;
	menu->btn_save[3].checked = FALSE;
	menu->btn_save[4].checked = FALSE;
	return (0);
}

int	btn_unselect_save4(t_checkbox *checkbox)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)checkbox;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 3 > app->maps_count)
		return (0);
	menu->selected_save = -1;
	menu->btn_start.is_clickable = FALSE;
	menu->btn_save[0].checked = FALSE;
	menu->btn_save[1].checked = FALSE;
	menu->btn_save[2].checked = FALSE;
	menu->btn_save[3].checked = FALSE;
	menu->btn_save[4].checked = FALSE;
	return (0);
}

int	btn_unselect_save5(t_checkbox *checkbox)
{
	t_mlx				*app;
	t_ui_new_game_menu	*menu;

	(void)checkbox;
	menu = &get_ui()->new_game_menu;
	app = get_app();
	if (menu->first_save_offset + 4 > app->maps_count)
		return (0);
	menu->selected_save = -1;
	menu->btn_start.is_clickable = FALSE;
	menu->btn_save[0].checked = FALSE;
	menu->btn_save[1].checked = FALSE;
	menu->btn_save[2].checked = FALSE;
	menu->btn_save[3].checked = FALSE;
	menu->btn_save[4].checked = FALSE;
	return (0);
}
