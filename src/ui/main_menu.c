/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:51:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 19:19:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	btn_continue(t_button *button);
int	btn_new_game(t_button *button);
int	btn_load_game(t_button *button);
int	btn_editor(t_button *button);
int	btn_option(t_button *button);
int	btn_exit_app(t_button *button);

void	init_main_menu(void)
{
	t_ui_main_menu	*main_menu;

	main_menu = &get_app()->ui.main_menu;
	main_menu->title = create_img_box("assets/ui/main_menu_title.xpm",
					ivec2(WIN_W / 2, 50));
	main_menu->btn_continue = create_button("assets/ui/continue.xpm",
		ivec2(WIN_W / 2, 100), btn_continue);
	if (get_app()->savegames_count == 0)
		main_menu->btn_continue.infos.displayed = FALSE;
	main_menu->btn_new_game = create_button("assets/ui/new_game.xpm",
		ivec2(WIN_W / 2, 150), btn_new_game);
	main_menu->btn_load = create_button("assets/ui/load.xpm",
		ivec2(WIN_W / 2, 200), btn_load_game);
	if (get_app()->savegames_count == 0)
		main_menu->btn_load.infos.displayed = FALSE;
	main_menu->btn_editor = create_button("assets/ui/editor.xpm",
		ivec2(WIN_W / 2, 250), btn_editor);
	main_menu->btn_option = create_button("assets/ui/option.xpm",
		ivec2(WIN_W / 2, 300), btn_option);
	main_menu->btn_exit = create_button("assets/ui/exit.xpm",
		ivec2(WIN_W / 2, 350), btn_exit_app);
}

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
