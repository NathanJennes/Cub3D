/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_update.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:36:24 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 14:10:50 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "leaky.h"

void	update_settings_menu(void)
{
	static int			last_fov;
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	update_ui_slider(&menu->slid_fov);
	update_ui_checkbox(&menu->chk_res_min);
	update_ui_checkbox(&menu->chk_res_med);
	update_ui_checkbox(&menu->chk_res_high);
	update_ui_checkbox(&menu->chk_res_fullscreen);
	update_ui_button(&menu->btn_back);
	if (last_fov != (int)menu->slid_fov.value)
	{
		gc_free(menu->lbl_fov.text);
		update_ui_label_text(&menu->lbl_fov,
			gc_itoa((int)menu->slid_fov.value));
		last_fov = (int)menu->slid_fov.value;
	}
}

void	update_settings_menu_click_begin(int button)
{
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	update_ui_slider_click_begin(&menu->slid_fov, button);
	update_ui_checkbox_click_begin(&menu->chk_res_min, button);
	update_ui_checkbox_click_begin(&menu->chk_res_med, button);
	update_ui_checkbox_click_begin(&menu->chk_res_high, button);
	update_ui_checkbox_click_begin(&menu->chk_res_fullscreen, button);
	update_ui_button_click_begin(&menu->btn_back, button);
}

void	update_settings_menu_click_end(int button)
{
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	update_ui_slider_click_end(&menu->slid_fov, button);
	update_ui_checkbox_click_end(&menu->chk_res_min, button);
	update_ui_checkbox_click_end(&menu->chk_res_med, button);
	update_ui_checkbox_click_end(&menu->chk_res_high, button);
	update_ui_checkbox_click_end(&menu->chk_res_fullscreen, button);
	update_ui_button_click_end(&menu->btn_back, button);
}
