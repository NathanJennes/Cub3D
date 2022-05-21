/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:37:39 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 17:25:39 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int			btn_continue(t_button *button);
int			btn_new_game(t_button *button);
int			btn_load_game(t_button *button);
int			btn_editor(t_button *button);
int			btn_option(t_button *button);
int			btn_exit_app(t_button *button);

static void	init_positions(t_ui_main_menu *main_menu);

void	init_main_menu(void)
{
	t_ui_main_menu	*main_menu;

	main_menu = &get_app()->ui.main_menu;
	main_menu->title = create_img_box("assets/ui/main_menu_title.xpm",
			ivec2(0, 50));
	main_menu->btn_continue = create_button("assets/ui/continue.xpm",
			ivec2(0, 0), btn_continue);
	if (get_app()->savegames_count == 0)
		main_menu->btn_continue.infos.displayed = FALSE;
	main_menu->btn_new_game = create_button("assets/ui/new_game.xpm",
			ivec2(0, 0), btn_new_game);
	if (get_app()->maps_count == 0)
		main_menu->btn_new_game.infos.displayed = FALSE;
	main_menu->btn_load = create_button("assets/ui/load.xpm",
			ivec2(0, 0), btn_load_game);
	if (get_app()->savegames_count == 0)
		main_menu->btn_load.infos.displayed = FALSE;
	main_menu->btn_editor = create_button("assets/ui/editor.xpm",
			ivec2(0, 0), btn_editor);
	main_menu->btn_option = create_button("assets/ui/option.xpm",
			ivec2(0, 0), btn_option);
	main_menu->btn_exit = create_button("assets/ui/exit.xpm",
			ivec2(0, 0), btn_exit_app);
	init_positions(main_menu);
}

static void	init_positions(t_ui_main_menu *main_menu)
{
	uic_padding(&main_menu->btn_continue.infos, ivec2(20, 20), ivec2(0, 0));
	uic_padding(&main_menu->btn_new_game.infos, ivec2(20, 20), ivec2(0, 0));
	uic_padding(&main_menu->btn_load.infos, ivec2(20, 20), ivec2(0, 0));
	uic_padding(&main_menu->btn_editor.infos, ivec2(20, 20), ivec2(0, 0));
	uic_padding(&main_menu->btn_exit.infos, ivec2(20, 20), ivec2(0, 0));
	uic_center_win_w(&main_menu->title.infos);
	uic_below(&main_menu->btn_continue.infos, &main_menu->title.infos);
	uic_below(&main_menu->btn_new_game.infos, &main_menu->btn_continue.infos);
	uic_below(&main_menu->btn_load.infos, &main_menu->btn_new_game.infos);
	uic_below(&main_menu->btn_editor.infos, &main_menu->btn_load.infos);
	uic_below(&main_menu->btn_exit.infos, &main_menu->btn_editor.infos);
}