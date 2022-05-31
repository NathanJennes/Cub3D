/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_buttons.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:50:46 by njennes           #+#    #+#             */
/*   Updated: 2022/05/31 15:42:49 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

int	btn_settings_back(t_button *button)
{
	t_ui		*ui;
	t_settings	*settings;

	(void)button;
	ui = get_ui();
	ui->state = MAIN_MENU;
	settings = get_settings();
	settings->fov = (int)ui->settings_menu.slid_fov.value;
	settings->win_w = (int)ui->settings_menu.slid_win_w.value;
	settings->win_h = (int)ui->settings_menu.slid_win_h.value;
	init_math();
	return (0);
}
