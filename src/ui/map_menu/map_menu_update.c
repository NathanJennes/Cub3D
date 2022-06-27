/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_menu_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:09:46 by Cyril             #+#    #+#             */
/*   Updated: 2022/06/27 17:44:44 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	update_map_menu(void)
{
	t_ui_map_menu	*menu;

	if (get_app()->ui.state != MAP_MENU)
		return ;
	menu = &get_app()->ui.map_menu;
	update_ui_checkbox(&menu->chk_editor_mode);
	update_ui_slider(&menu->intensity);
	update_ui_slider(&menu->slid_blue_color);
	update_ui_slider(&menu->slid_green_color);
	update_ui_slider(&menu->slid_red_color);
}

void	update_map_menu_click_begin(int mouse_btn)
{
	t_ui_map_menu	*menu;

	menu = &get_app()->ui.map_menu;
	update_ui_checkbox_click_begin(&menu->chk_editor_mode, mouse_btn);
	update_ui_slider_click_begin(&menu->intensity, mouse_btn);
	update_ui_slider_click_begin(&menu->slid_blue_color, mouse_btn);
	update_ui_slider_click_begin(&menu->slid_green_color, mouse_btn);
	update_ui_slider_click_begin(&menu->slid_red_color, mouse_btn);
}

void	update_map_menu_click_end(int mouse_btn)
{
	t_ui_map_menu	*menu;

	menu = &get_app()->ui.map_menu;
	update_ui_checkbox_click_end(&menu->chk_editor_mode, mouse_btn,
		get_mouse_pos());
	update_ui_slider_click_end(&menu->intensity, mouse_btn);
	update_ui_slider_click_end(&menu->slid_blue_color, mouse_btn);
	update_ui_slider_click_end(&menu->slid_green_color, mouse_btn);
	update_ui_slider_click_end(&menu->slid_red_color, mouse_btn);
}
