/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:35:58 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 15:31:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	render_settings_menu(void)
{
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	render_ui_slider(&menu->slid_fov);
	render_ui_slider(&menu->slid_sens);
	render_ui_checkbox(&menu->chk_res_min);
	render_ui_checkbox(&menu->chk_res_med);
	render_ui_checkbox(&menu->chk_res_high);
	render_ui_checkbox(&menu->chk_res_fullscreen);
	render_ui_button(&menu->btn_back);
	render_ui_label(&menu->lbl_fov);
	render_ui_label(&menu->lbl_sens);
}
