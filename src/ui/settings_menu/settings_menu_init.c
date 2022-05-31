/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:36:08 by njennes           #+#    #+#             */
/*   Updated: 2022/05/31 16:20:22 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "leaky.h"

int	btn_settings_back(t_button *button);

static void	init_positions(t_ui_settings_menu *menu);

void	init_settings_menu(void)
{
	t_ui_settings_menu	*menu;

	menu = &get_app()->ui.settings_menu;
	menu->slid_fov = create_slider(ivec2_zero(),
		ivec2(350, 30), vec3(10.0, 170.0,
			(float)get_settings()->fov));
	menu->lbl_fov = create_label(ivec2_zero(), gc_itoa(get_settings()->fov), ivec2(200, 100));
	menu->slid_win_w = create_slider(ivec2_zero(),
		ivec2(350, 30), vec3(960.0, 3000.0,
			(float)get_settings()->win_w));
	menu->slid_win_h = create_slider(ivec2_zero(),
		ivec2(350, 30), vec3(540.0, 3000.0,
			(float)get_settings()->win_h));
	menu->btn_back = create_button("assets/placeholder.xpm",
		ivec2(50, WIN_H - 50), btn_settings_back);
	init_positions(menu);
}

static void	init_positions(t_ui_settings_menu *menu)
{
	menu->slid_fov.infos.pos.y = 50;
	uic_center_win_w(&menu->slid_fov.infos);
	uic_padding_down(&menu->slid_fov.infos, 50);
	uic_padding_right(&menu->slid_fov.infos, 50);
	uic_padding_down(&menu->slid_win_w.infos, 50);
	uic_padding_down(&menu->slid_win_h.infos, 50);
	uic_below(&menu->slid_win_w.infos, &menu->slid_fov.infos);
	uic_below(&menu->slid_win_h.infos, &menu->slid_win_w.infos);
	uic_side_right(&menu->lbl_fov.infos, &menu->slid_fov.infos);
}
