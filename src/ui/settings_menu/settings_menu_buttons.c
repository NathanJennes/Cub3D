/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_buttons.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:50:46 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 13:35:50 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

int	btn_settings_back(t_button *button)
{
	t_ui		*ui;
	t_settings	*settings;

	(void)button;
	ui = get_ui();
	ui->state = MAIN_MENU;
	settings = get_settings();
	settings->fov = (int)ui->settings_menu.slid_fov.value;
	init_math();
	return (0);
}

int	chk_select_res_min(t_checkbox *checkbox)
{
	t_ui_settings_menu	*menu;
	t_settings			*settings;

	(void)checkbox;
	settings = get_settings();
	menu = &get_ui()->settings_menu;
	settings->desired_win_w = 960;
	settings->desired_win_h = 540;
	menu->chk_res_med.checked = FALSE;
	menu->chk_res_high.checked = FALSE;
	menu->chk_res_fullscreen.checked = FALSE;
	return (0);
}

int	chk_unselect_res_min(t_checkbox *checkbox)
{
	t_ui_settings_menu	*menu;

	(void)checkbox;
	menu = &get_ui()->settings_menu;
	menu->chk_res_min.checked = TRUE;
	return (0);
}

int	chk_select_res_med(t_checkbox *checkbox)
{
	t_ui_settings_menu	*menu;
	t_settings			*settings;

	(void)checkbox;
	settings = get_settings();
	menu = &get_ui()->settings_menu;
	settings->desired_win_w = 1280;
	settings->desired_win_h = 720;
	menu->chk_res_min.checked = FALSE;
	menu->chk_res_high.checked = FALSE;
	menu->chk_res_fullscreen.checked = FALSE;
	return (0);
}

int	chk_unselect_res_med(t_checkbox *checkbox)
{
	t_ui_settings_menu	*menu;

	(void)checkbox;
	menu = &get_ui()->settings_menu;
	menu->chk_res_med.checked = TRUE;
	return (0);
}
