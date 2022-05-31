/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_update.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:36:24 by njennes           #+#    #+#             */
/*   Updated: 2022/05/31 14:56:02 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

void	update_settings_menu(void)
{
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	update_ui_slider(&menu->slid_fov);
	update_ui_slider(&menu->slid_win_w);
	update_ui_slider(&menu->slid_win_h);
	update_ui_button(&menu->btn_back);
}

void	update_settings_menu_click_begin(int button)
{
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	update_ui_slider_click_begin(&menu->slid_fov, button);
	update_ui_slider_click_begin(&menu->slid_win_w, button);
	update_ui_slider_click_begin(&menu->slid_win_h, button);
	update_ui_button_click_begin(&menu->btn_back, button);
}

void	update_settings_menu_click_end(int button)
{
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	update_ui_slider_click_end(&menu->slid_fov, button);
	update_ui_slider_click_end(&menu->slid_win_w, button);
	update_ui_slider_click_end(&menu->slid_win_h, button);
	update_ui_button_click_end(&menu->btn_back, button);
}
