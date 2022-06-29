/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_buttons2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:36:12 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 13:52:34 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	chk_select_res_high(t_checkbox *checkbox)
{
	t_ui_settings_menu	*menu;
	t_settings			*settings;

	(void)checkbox;
	settings = get_settings();
	menu = &get_ui()->settings_menu;
	settings->desired_win_w = 1920;
	settings->desired_win_h = 1080;
	menu->chk_res_min.checked = FALSE;
	menu->chk_res_med.checked = FALSE;
	menu->chk_res_fullscreen.checked = FALSE;
	return (0);
}

int	chk_unselect_res_high(t_checkbox *checkbox)
{
	t_ui_settings_menu	*menu;

	(void)checkbox;
	menu = &get_ui()->settings_menu;
	menu->chk_res_high.checked = TRUE;
	return (0);
}

int	chk_select_res_fullscreen(t_checkbox *checkbox)
{
	(void)checkbox;
	return (0);
}

int	chk_unselect_res_fullscreen(t_checkbox *checkbox)
{
	(void)checkbox;
	return (0);
}
