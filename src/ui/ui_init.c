/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:21:25 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/18 14:56:54 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

static void	init_main_menu(void);

void	init_ui(void)
{
	t_ui	*ui;

	ui = get_ui();
	ui->state = MAIN_MENU;
	init_main_menu();
	// init_option_menu();
	// init_load_menu();
	// init_new_game_menu();
	// init_editor_menu();
	// init_pause_menu();
	// init_hud();
}

static void	init_main_menu(void)
{
	t_ui_main_menu	*main_menu;

	main_menu = &get_ui()->main_menu;
	main_menu->title.tex_id = load_texture("assets/ui/main_menu_title.xpm");
	main_menu->title.infos.pos = ivec2(320, 60);
	main_menu->title.infos.displayed = TRUE;

//	main_menu->btn_continue.tex_id = load_texture("assets/ui/btn_continue.xpm");
////	main_menu->btn_continue.tex_id = load_texture("assets/ui/btn_continue_select.xpm");
////	main_menu->btn_continue.tex_id = load_texture("assets/ui/btn_continue_hover.xpm");
//	main_menu->btn_continue.position = vec2(400.0f, 160.5f);
//	main_menu->btn_continue.bounding_box = vec2(240.0f, 40.0f);
//	main_menu->btn_continue.is_clickable = FALSE;
//	main_menu->btn_continue.displayed = TRUE;
}
