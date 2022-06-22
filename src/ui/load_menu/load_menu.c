/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:17:06 by njennes           #+#    #+#             */
/*   Updated: 2022/06/20 18:07:06 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	render_load_menu(void)
{
	t_ui_load_menu	*load_menu;

	load_menu = &get_app()->ui.load_menu;
	render_ui_button(&load_menu->btn_back);
	render_ui_button(&load_menu->btn_start);
	render_ui_button(&load_menu->btn_next_save);
	render_ui_label(&load_menu->lbl_selected_save);
}

void	update_load_menu(void)
{
	t_ui_load_menu	*load_menu;

	load_menu = &get_app()->ui.load_menu;
	update_ui_button(&load_menu->btn_back);
	update_ui_button(&load_menu->btn_start);
	update_ui_button(&load_menu->btn_next_save);
}

void	update_load_menu_click_begin(int mouse_btn)
{
	t_ui_load_menu	*load_menu;

	load_menu = &get_app()->ui.load_menu;
	update_ui_button_click_begin(&load_menu->btn_back, mouse_btn);
	update_ui_button_click_begin(&load_menu->btn_start, mouse_btn);
	update_ui_button_click_begin(&load_menu->btn_next_save, mouse_btn);
}

void	update_load_menu_click_end(int mouse_btn)
{
	t_ui_load_menu	*load_menu;

	load_menu = &get_app()->ui.load_menu;
	update_ui_button_click_end(&load_menu->btn_back, mouse_btn);
	update_ui_button_click_end(&load_menu->btn_start, mouse_btn);
	update_ui_button_click_end(&load_menu->btn_next_save, mouse_btn);
}
