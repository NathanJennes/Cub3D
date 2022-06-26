/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_menu_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:09:46 by Cyril             #+#    #+#             */
/*   Updated: 2022/06/26 18:09:19 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "texture.h"
#include "render.h"

static int			chk_editor_mode_checked(t_checkbox *checkbox);
static int			chk_editor_mode_unchecked(t_checkbox *checkbox);
inline static void		init_textures_settings(t_ui_map_menu *menu);
inline static void		init_positions_map_menu(t_ui_map_menu *menu);

void	init_map_menu(void)
{
	t_ui_map_menu	*menu;
	t_settings		*settings;

	settings = get_settings();
	menu = &get_app()->ui.map_menu;
	menu->intensity = create_slider(
			ivec2(settings->win_w - 270, settings->win_h - 50),
			ivec2(250, 15), vec3(0, 255, 0));
	menu->intensity_label = create_label(
			ivec2_zero(), "Intensity", ivec2(250, 25), 20);
	menu->slid_blue_color = create_slider(
			ivec2_zero(), ivec2(250, 15), vec3(0, 255, 0));
	menu->blue_label = create_label(
			ivec2_zero(), "Blue", ivec2(250, 25), 20);
	menu->slid_green_color = create_slider(
			ivec2_zero(), ivec2(250, 15), vec3(0, 255, 0));
	menu->green_label = create_label(
			ivec2_zero(), "Green", ivec2(250, 25), 20);
	menu->slid_red_color = create_slider(
			ivec2_zero(), ivec2(250, 15), vec3(0, 255, 0));
	menu->red_label = create_label(
			ivec2_zero(), "Red", ivec2(250, 25), 20);
	menu->chk_editor_mode = create_checkbox(NULL,
			ivec2_zero(), chk_editor_mode_checked, chk_editor_mode_unchecked);
	init_positions_map_menu(menu);
}

inline static void	init_positions_map_menu(t_ui_map_menu *menu)
{
	init_textures_settings(menu);
	uic_padding_up(&menu->intensity.infos, 15);
	uic_padding_up(&menu->intensity_label.infos, 15);
	uic_padding_up(&menu->slid_blue_color.infos, 15);
	uic_padding_up(&menu->blue_label.infos, 15);
	uic_padding_up(&menu->slid_green_color.infos, 15);
	uic_padding_up(&menu->green_label.infos, 15);
	uic_padding_up(&menu->slid_red_color.infos, 15);
	uic_padding_up(&menu->red_label.infos, 15);
	uic_above(&menu->intensity_label.infos, &menu->intensity.infos);
	uic_above(&menu->slid_blue_color.infos, &menu->intensity_label.infos);
	uic_above(&menu->blue_label.infos, &menu->slid_blue_color.infos);
	uic_above(&menu->slid_green_color.infos, &menu->blue_label.infos);
	uic_above(&menu->green_label.infos, &menu->slid_green_color.infos);
	uic_above(&menu->slid_red_color.infos, &menu->green_label.infos);
	uic_above(&menu->red_label.infos, &menu->slid_red_color.infos);
	uic_above(&menu->chk_editor_mode.infos, &menu->red_label.infos);
}

inline static void	init_textures_settings(t_ui_map_menu *menu)
{
	menu->chk_editor_mode.tex_id = new_texture(200, 60);
	clear_texture(RED, menu->chk_editor_mode.tex_id);
	render_text_tex("EDITOR MODE", DEFAULT_FONT,
		text_center("EDITOR MODE", DEFAULT_FONT, 22, ivec2(100, 30)),
		ivec2(22, menu->chk_editor_mode.tex_id));
	finish_new_texture(menu->chk_editor_mode.tex_id);
	menu->chk_editor_mode.infos.size = \
		get_texture_size(menu->chk_editor_mode.tex_id);
}

int	chk_editor_mode_checked(t_checkbox *checkbox)
{
	(void)checkbox;
	get_app()->editor_mode = !get_app()->editor_mode;
	return (0);
}

int	chk_editor_mode_unchecked(t_checkbox *checkbox)
{
	(void)checkbox;
	get_app()->editor_mode = !get_app()->editor_mode;
	return (0);
}
