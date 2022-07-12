/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:50:34 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 17:44:44 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	init_textures(void);
void	update_display_status(void);

void	render_new_game_menu(void)
{
	t_ui_new_game_menu	*menu;

	menu = &get_ui()->new_game_menu;
	render_ui_button(&menu->btn_back);
	render_ui_button(&menu->btn_down);
	render_ui_button(&menu->btn_up);
	render_ui_button(&menu->btn_start);
	render_ui_checkbox(&menu->btn_save[0]);
	render_ui_checkbox(&menu->btn_save[1]);
	render_ui_checkbox(&menu->btn_save[2]);
	render_ui_checkbox(&menu->btn_save[3]);
	render_ui_checkbox(&menu->btn_save[4]);
}

void	update_new_game_menu(void)
{
	t_ui_new_game_menu	*menu;

	menu = &get_ui()->new_game_menu;
	update_ui_button(&menu->btn_back);
	update_ui_button(&menu->btn_down);
	update_ui_button(&menu->btn_up);
	update_ui_button(&menu->btn_start);
	update_ui_checkbox(&menu->btn_save[0]);
	update_ui_checkbox(&menu->btn_save[1]);
	update_ui_checkbox(&menu->btn_save[2]);
	update_ui_checkbox(&menu->btn_save[3]);
	update_ui_checkbox(&menu->btn_save[4]);
}

void	update_new_game_menu_click_begin(int button)
{
	t_ui_new_game_menu	*menu;

	menu = &get_ui()->new_game_menu;
	update_ui_button_click_begin(&menu->btn_back, button);
	update_ui_button_click_begin(&menu->btn_down, button);
	update_ui_button_click_begin(&menu->btn_up, button);
	update_ui_button_click_begin(&menu->btn_start, button);
	update_ui_checkbox_click_begin(&menu->btn_save[0], button);
	update_ui_checkbox_click_begin(&menu->btn_save[1], button);
	update_ui_checkbox_click_begin(&menu->btn_save[2], button);
	update_ui_checkbox_click_begin(&menu->btn_save[3], button);
	update_ui_checkbox_click_begin(&menu->btn_save[4], button);
}

void	update_new_game_menu_click_end(int button)
{
	t_ui_new_game_menu	*menu;

	menu = &get_ui()->new_game_menu;
	update_ui_button_click_end(&menu->btn_back, button);
	update_ui_button_click_end(&menu->btn_down, button);
	update_ui_button_click_end(&menu->btn_up, button);
	update_ui_button_click_end(&menu->btn_start, button);
	update_ui_checkbox_click_end(&menu->btn_save[0], button, get_mouse_pos());
	update_ui_checkbox_click_end(&menu->btn_save[1], button, get_mouse_pos());
	update_ui_checkbox_click_end(&menu->btn_save[2], button, get_mouse_pos());
	update_ui_checkbox_click_end(&menu->btn_save[3], button, get_mouse_pos());
	update_ui_checkbox_click_end(&menu->btn_save[4], button, get_mouse_pos());
}

void	refresh_new_game_menu(void)
{
	init_textures();
	update_display_status();
}