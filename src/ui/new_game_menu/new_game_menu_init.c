/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game_menu_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:48:19 by njennes           #+#    #+#             */
/*   Updated: 2022/05/23 17:15:18 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "render.h"

int			btn_new_game_back(t_button *button);
int			btn_new_game_down(t_button *button);
int			btn_new_game_up(t_button *button);
int			btn_start_new_game(t_button *button);
int			btn_select_save1(t_button *button);
int			btn_select_save2(t_button *button);
int			btn_select_save3(t_button *button);
int			btn_select_save4(t_button *button);
int			btn_select_save5(t_button *button);

static void	init_positions(void);
void		init_textures(void);
void		update_display_status(void);

void	init_new_game_menu(void)
{
	t_ui_new_game_menu	*menu;

	menu = &get_ui()->new_game_menu;
	menu->selected_save = -1;
	menu->btn_back = create_button("assets/placeholder.xpm",
			ivec2(50, WIN_H - 50), btn_new_game_back);
	menu->btn_down = create_button("assets/placeholder.xpm",
			ivec2(0, 0), btn_new_game_down);
	menu->btn_up = create_button("assets/placeholder.xpm",
			ivec2(0, 0), btn_new_game_up);
	menu->btn_start = create_button("assets/placeholder.xpm",
			ivec2(0, 0), btn_start_new_game);
	menu->btn_save[0] = create_button(NULL, ivec2(0, 100), btn_select_save1);
	menu->btn_save[1] = create_button(NULL, ivec2(0, 0), btn_select_save2);
	menu->btn_save[2] = create_button(NULL, ivec2(0, 0), btn_select_save3);
	menu->btn_save[3] = create_button(NULL, ivec2(0, 0), btn_select_save4);
	menu->btn_save[4] = create_button(NULL, ivec2(0, 0), btn_select_save5);
	update_display_status();
	init_textures();
	init_positions();
}

static void	init_positions(void)
{
	t_ui_new_game_menu	*menu;

	menu = &get_ui()->new_game_menu;
	uic_padding(&menu->btn_save[0].infos, ivec2(25, 50), ivec2(50, 50));
	uic_padding(&menu->btn_save[1].infos, ivec2(50, 50), ivec2(50, 50));
	uic_padding(&menu->btn_save[2].infos, ivec2(50, 50), ivec2(50, 50));
	uic_padding(&menu->btn_save[3].infos, ivec2(50, 50), ivec2(50, 50));
	uic_padding(&menu->btn_save[4].infos, ivec2(50, 50), ivec2(50, 50));
	uic_padding(&menu->btn_down.infos, ivec2(50, 50), ivec2(50, 50));
	uic_center_win_w(&menu->btn_save[0].infos);
	uic_above(&menu->btn_start.infos, &menu->btn_save[0].infos);
	uic_side_right(&menu->btn_up.infos, &menu->btn_save[0].infos);
	uic_below(&menu->btn_down.infos, &menu->btn_up.infos);
	uic_below(&menu->btn_save[1].infos, &menu->btn_save[0].infos);
	uic_below(&menu->btn_save[2].infos, &menu->btn_save[1].infos);
	uic_below(&menu->btn_save[3].infos, &menu->btn_save[2].infos);
	uic_below(&menu->btn_save[4].infos, &menu->btn_save[3].infos);
}

void	init_textures(void)
{
	t_ui_new_game_menu	*menu;
	t_button			*btn;
	int64_t				i;
	t_mlx				*app;

	menu = &get_ui()->new_game_menu;
	i = 0;
	app = get_app();
	while (i < 5)
	{
		btn = &menu->btn_save[i];
		if (i < app->maps_count && (btn->infos.displayed
				|| btn->tex_id == INVALID_TEXTURE))
		{
			btn->tex_id = new_texture(250, 50);
			clear_texture(trgb(0, 255, 51, 51), btn->tex_id);
			render_text_tex(app->maps[i].name, "HelveticaNeue",
				text_center(app->maps[i].name, "HelveticaNeue", 30,
					ivec2(125, 25)),
				ivec2(30, btn->tex_id));
			finish_new_texture(btn->tex_id);
			btn->infos.size = get_texture_size(btn->tex_id);
		}
		i++;
	}
}

void	update_display_status(void)
{
	t_ui_new_game_menu	*menu;
	t_mlx				*app;
	int64_t				i;

	menu = &get_ui()->new_game_menu;
	app = get_app();
	i = 0;
	while (i < 5)
	{
		if (i < app->maps_count)
			menu->btn_save[i].infos.displayed = TRUE;
		else
			menu->btn_save[i].infos.displayed = FALSE;
		i++;
	}
}
