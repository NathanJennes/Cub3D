/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:22:29 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 18:39:01 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

void	init_keybings_menu(void)
{
	t_ui_keybind_menu	*menu;

	menu = &get_app()->ui.key_menu;
	menu->title = create_label(ivec2_zero(), "KEYBINDINGS",
			ivec2(300, 100), 30);
	menu->img = create_img_box("assets/placeholder.xpm", ivec2_zero());
	uic_center_win_w(&menu->title.infos);
	uic_padding_down(&menu->title.infos, 50);
	uic_below(&menu->img.infos, &menu->title.infos);
}

void	render_keybindings_menu(void)
{
	t_ui_keybind_menu	*menu;

	menu = &get_app()->ui.key_menu;
	render_ui_label(&menu->title);
	render_ui_img_box(&menu->img);
}
