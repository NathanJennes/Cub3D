/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:31:13 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 15:08:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>

int					is_light_inside_map(t_ivec2 mouse_pos);
void				update_ui_click_begin(int button);
void				update_ui_click_end(int button);
void				delete_lights_in_minimap(void);
inline static void		mouse_click_editor_mode(t_ui_map_menu *map_menu);

void	mouse_click_begin(int button)
{
	update_ui_click_begin(button);
	mouse_click_editor_mode(&get_ui()->map_menu);
}

inline static void	mouse_click_editor_mode(t_ui_map_menu *map_menu)
{
	t_light		*new_light;
	t_rgb		color;
	t_sprite	new_sprite;

	if (get_app()->state == IN_GAME
		&& get_app()->editor_mode == TRUE
		&& is_light_inside_map(get_mouse_pos())
		&& get_app()->light_mode == ADD)
	{
		color.r = (uint8_t)map_menu->slid_red_color.value;
		color.g = (uint8_t)map_menu->slid_green_color.value;
		color.b = (uint8_t)map_menu->slid_blue_color.value;
		add_light(&get_app()->gamestate,
			vec3(get_mouse_pos().x, get_mouse_pos().y, 18),
			color,
			map_menu->intensity.value);
		new_light = &get_gamestate()->lights[get_gamestate()->light_count - 1];
		new_sprite.tex_id = get_app()->lamp_tex_id;
		new_sprite.size = ivec2(3, 4);
		new_sprite.pos = vec3(get_mouse_pos().x, get_mouse_pos().y, 8);
		new_sprite.color = vec3((double)new_light->color.r / 255.0,
				(double)new_light->color.g / 255.0,
				(double)new_light->color.b / 255.0);
		add_sprite_to_current_game(new_sprite);
	}
	else if (get_app()->state == IN_GAME
			&& get_app()->editor_mode == TRUE
			&& get_app()->light_mode == DELETE)
		delete_lights_in_minimap();
}

void	mouse_click_end(int button)
{
	update_ui_click_end(button);
}

void	mouse_wheel_up(void)
{
	t_mlx	*app;
	t_ui	*ui;

	app = get_app();
	if (app->state == IN_GAME)
		return ;
	ui = get_ui();
	if (ui->state == NEW_GAME_MENU && ui->new_game_menu.first_save_offset > 0)
	{
		ui->new_game_menu.first_save_offset--;
		new_game_menu_refresh();
	}
	if (ui->state == LOAD_MENU && ui->load_menu.save_selected >= 0)
	{
		if (ui->load_menu.save_selected == 0)
			ui->load_menu.save_selected = app->savegames_count - 1;
		else
			ui->load_menu.save_selected--;
		refresh_load_menu();
	}
}

void	mouse_wheel_down(void)
{
	t_mlx	*app;
	t_ui	*ui;

	app = get_app();
	if (app->state == IN_GAME)
		return ;
	ui = get_ui();
	if (ui->state == NEW_GAME_MENU
		&& ui->new_game_menu.first_save_offset < app->maps_count - 5)
	{
		ui->new_game_menu.first_save_offset++;
		new_game_menu_refresh();
	}
	if (ui->state == LOAD_MENU
		&& ui->load_menu.save_selected < app->savegames_count)
	{
		if (ui->load_menu.save_selected == app->savegames_count - 1)
			ui->load_menu.save_selected = 0;
		else
			ui->load_menu.save_selected++;
		refresh_load_menu();
	}
}
