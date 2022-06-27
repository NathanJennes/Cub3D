/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_init_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:46:12 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 17:47:22 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

void	init_current_res_checkbox(t_ui_settings_menu *menu)
{
	t_settings	*settings;

	settings = get_settings();
	if (settings->win_w == 960)
		menu->chk_res_min.checked = TRUE;
	else if (settings->win_w == 1280)
		menu->chk_res_med.checked = TRUE;
	else
		menu->chk_res_high.checked = TRUE;
}
