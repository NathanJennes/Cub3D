/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_menu_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:17:29 by njennes           #+#    #+#             */
/*   Updated: 2022/06/20 18:13:24 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "render.h"

int					btn_back(t_button *button);
int					btn_next_save(t_button *button);
int					btn_load_save(t_button *button);

inline static void	init_positions_load_menu(t_ui_load_menu *menu);

void	init_load_menu(void)
{
	t_ui_load_menu	*menu;

	menu = &get_ui()->load_menu;
	menu->lbl_selected_save = create_label(
		ivec2(get_settings()->halfw_w, 50),
		"", ivec2(get_settings()->win_w, 100));
	menu->btn_start = create_button("assets/placeholder.xpm",
		ivec2(0, 0), btn_load_save);
	menu->btn_next_save = create_button("assets/placeholder.xpm",
		ivec2(0, 0), btn_next_save);
	menu->btn_back = create_button("assets/placeholder.xpm",
		ivec2(50, get_settings()->win_h - 50), btn_back);
	init_positions_load_menu(menu);
}

void	refresh_load_menu(void)
{
	t_ui_load_menu	*menu;

	menu = &get_ui()->load_menu;
	update_ui_label_text(&menu->lbl_selected_save,
		get_app()->savegames[menu->save_selected].name);

}

inline static void	init_positions_load_menu(t_ui_load_menu *menu)
{
	uic_padding(&menu->lbl_selected_save.infos, ivec2(20, 20), ivec2_zero());
	uic_padding(&menu->btn_start.infos, ivec2(20, 20), ivec2_zero());
	uic_padding(&menu->btn_next_save.infos, ivec2(20, 20), ivec2_zero());
	uic_center_win_w(&menu->lbl_selected_save.infos);
	uic_below(&menu->btn_next_save.infos, &menu->lbl_selected_save.infos);
	uic_below(&menu->btn_start.infos, &menu->btn_next_save.infos);
}
