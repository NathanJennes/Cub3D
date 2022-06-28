/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_menu_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:09:46 by Cyril             #+#    #+#             */
/*   Updated: 2022/06/28 20:50:34 by Cyril            ###   ########.fr       */
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
	update_ui_button_click_begin(&menu->add_light, mouse_btn);
	update_ui_button_click_begin(&menu->delete_light, mouse_btn);
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
	update_ui_button_click_end(&menu->add_light, mouse_btn);
	update_ui_button_click_end(&menu->delete_light, mouse_btn);
}

int	add_light_mode_button(t_button *button)
{
	(void)button;
	get_app()->light_mode = DELETE;
	get_ui()->map_menu.add_light.infos.displayed = FALSE;
	get_ui()->map_menu.delete_light.infos.displayed = TRUE;
	return (0);
}

int	delete_light_mode_button(t_button *button)
{
	(void)button;
	get_app()->light_mode = ADD;
	get_ui()->map_menu.add_light.infos.displayed = TRUE;
	get_ui()->map_menu.delete_light.infos.displayed = FALSE;
	return (0);
}
