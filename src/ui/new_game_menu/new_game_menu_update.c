/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game_menu_update.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:38:18 by njennes           #+#    #+#             */
/*   Updated: 2022/06/23 13:51:34 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "render.h"

inline static void	update_checkbox_text(t_ui_new_game_menu *menu, t_checkbox *checkbox, int64_t i);

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
	if (app->maps_count <= 5)
	{
		menu->btn_up.is_clickable = FALSE;
		menu->btn_down.is_clickable = FALSE;
	}
}

void	new_game_menu_refresh(void)
{
	t_ui_new_game_menu	*menu;
	t_checkbox			*checkbox;
	int64_t				i;

	update_display_status();
	menu = &get_ui()->new_game_menu;
	i = 0;
	while (i < 5)
	{
		checkbox = &menu->btn_save[i];
		if (checkbox->infos.displayed)
			update_checkbox_text(menu, checkbox, i);
		i++;
	}
}

inline static void	update_checkbox_text(t_ui_new_game_menu *menu, t_checkbox *checkbox, int64_t i)
{
	t_mlx	*app;

	app = get_app();
	if (checkbox->tex_id == INVALID_TEXTURE)
		checkbox->tex_id = new_texture(250, 50);
	clear_texture(trgb(0, 255, 51, 51), checkbox->tex_id);
	render_text_tex(app->maps[i + menu->first_save_offset].name, "HelveticaNeue",
		text_center(app->maps[i + menu->first_save_offset].name, "HelveticaNeue", 30,
			ivec2(125, 25)),
		ivec2(30, checkbox->tex_id));
	update_texture_variations(checkbox->tex_id);
	checkbox->infos.size = get_texture_size(checkbox->tex_id);
}
