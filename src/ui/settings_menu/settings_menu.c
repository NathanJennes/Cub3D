/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:35:58 by njennes           #+#    #+#             */
/*   Updated: 2022/05/31 15:03:45 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	render_settings_menu(void)
{
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	render_ui_slider(&menu->slid_fov);
	render_ui_slider(&menu->slid_win_w);
	render_ui_slider(&menu->slid_win_h);
	render_ui_button(&menu->btn_back);
}
