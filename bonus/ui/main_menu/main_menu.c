/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:51:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 15:37:45 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	render_main_menu(void)
{
	t_ui_main_menu	*main_menu;

	main_menu = &get_app()->ui.main_menu;
	render_ui_img_box(&main_menu->title);
	render_ui_button(&main_menu->btn_continue);
	render_ui_button(&main_menu->btn_new_game);
	render_ui_button(&main_menu->btn_load);
	render_ui_button(&main_menu->btn_editor);
	render_ui_button(&main_menu->btn_option);
	render_ui_button(&main_menu->btn_exit);
	render_ui_label(&main_menu->lbl_help);
}

void	update_main_menu(void)
{
	t_ui_main_menu	*main_menu;

	main_menu = &get_app()->ui.main_menu;
	update_ui_button(&main_menu->btn_continue);
	update_ui_button(&main_menu->btn_new_game);
	update_ui_button(&main_menu->btn_load);
	update_ui_button(&main_menu->btn_editor);
	update_ui_button(&main_menu->btn_option);
	update_ui_button(&main_menu->btn_exit);
}

void	update_main_menu_click_begin(int mouse_btn)
{
	t_ui_main_menu	*main_menu;

	main_menu = &get_app()->ui.main_menu;
	update_ui_button_click_begin(&main_menu->btn_continue, mouse_btn);
	update_ui_button_click_begin(&main_menu->btn_new_game, mouse_btn);
	update_ui_button_click_begin(&main_menu->btn_load, mouse_btn);
	update_ui_button_click_begin(&main_menu->btn_editor, mouse_btn);
	update_ui_button_click_begin(&main_menu->btn_option, mouse_btn);
	update_ui_button_click_begin(&main_menu->btn_exit, mouse_btn);
}

void	update_main_menu_click_end(int mouse_btn)
{
	t_ui_main_menu	*main_menu;

	main_menu = &get_app()->ui.main_menu;
	update_ui_button_click_end(&main_menu->btn_continue, mouse_btn);
	update_ui_button_click_end(&main_menu->btn_new_game, mouse_btn);
	update_ui_button_click_end(&main_menu->btn_load, mouse_btn);
	update_ui_button_click_end(&main_menu->btn_editor, mouse_btn);
	update_ui_button_click_end(&main_menu->btn_option, mouse_btn);
	update_ui_button_click_end(&main_menu->btn_exit, mouse_btn);
}
