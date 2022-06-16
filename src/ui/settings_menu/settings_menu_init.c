/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:36:08 by njennes           #+#    #+#             */
/*   Updated: 2022/06/07 19:28:50 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "leaky.h"
#include "render.h"

int			btn_settings_back(t_button *button);
int			chk_select_res_min(t_checkbox *checkbox);
int			chk_unselect_res_min(t_checkbox *checkbox);
int			chk_select_res_med(t_checkbox *checkbox);
int			chk_unselect_res_med(t_checkbox *checkbox);
int			chk_select_res_high(t_checkbox *checkbox);
int			chk_unselect_res_high(t_checkbox *checkbox);
int			chk_select_res_fullscreen(t_checkbox *checkbox);
int			chk_unselect_res_fullscreen(t_checkbox *checkbox);

inline static void	init_positions(t_ui_settings_menu *menu);
inline static void	init_textures(t_ui_settings_menu *menu);
inline static void	init_current_res_checkbox(t_ui_settings_menu *menu);

void	init_settings_menu(void)
{
	t_ui_settings_menu	*menu;
	t_settings			*settings;

	settings = get_settings();
	menu = &get_app()->ui.settings_menu;
	menu->slid_fov = create_slider(ivec2_zero(),
			ivec2(350, 20), vec3(10.0, 170.0,
				(float)get_settings()->fov));
	menu->lbl_fov = create_label(ivec2_zero(),
			gc_itoa(get_settings()->fov), ivec2(200, 100));
	menu->slid_sens = create_slider(ivec2_zero(),
			ivec2(350, 20), vec3(0.1, 10.0,
				(float)get_settings()->cam_sensitivity));
	menu->lbl_sens = create_label(ivec2_zero(),
			gc_itoa(get_settings()->cam_sensitivity), ivec2(200, 100));
	menu->chk_res_min = create_checkbox(NULL, ivec2_zero(),
			chk_select_res_min, chk_unselect_res_min);
	menu->chk_res_med = create_checkbox(NULL, ivec2_zero(),
			chk_select_res_med, chk_unselect_res_med);
	menu->chk_res_high = create_checkbox(NULL, ivec2_zero(),
			chk_select_res_high, chk_unselect_res_high);
	menu->chk_res_fullscreen = create_checkbox(NULL, ivec2_zero(),
			chk_select_res_fullscreen, chk_unselect_res_fullscreen);
	menu->chk_res_fullscreen.is_clickable = FALSE;
	menu->btn_back = create_button("assets/placeholder.xpm",
			ivec2(50, settings->win_h - 50), btn_settings_back);
	init_textures(menu);
	init_positions(menu);
	init_current_res_checkbox(menu);
}

inline static void	init_positions(t_ui_settings_menu *menu)
{
	menu->slid_fov.infos.pos.y = 50;
	uic_center_win_w(&menu->slid_fov.infos);
	uic_padding_down(&menu->slid_fov.infos, 50);
	uic_padding_right(&menu->slid_fov.infos, 50);
	uic_padding_down(&menu->slid_sens.infos, 50);
	uic_padding_right(&menu->slid_sens.infos, 50);
	uic_padding_down(&menu->chk_res_min.infos, 30);
	uic_padding_down(&menu->chk_res_med.infos, 30);
	uic_padding_down(&menu->chk_res_high.infos, 30);
	uic_padding_down(&menu->chk_res_fullscreen.infos, 30);
	uic_below(&menu->slid_sens.infos, &menu->slid_fov.infos);
	uic_below(&menu->chk_res_min.infos, &menu->slid_sens.infos);
	uic_below(&menu->chk_res_med.infos, &menu->chk_res_min.infos);
	uic_below(&menu->chk_res_high.infos, &menu->chk_res_med.infos);
	uic_below(&menu->chk_res_fullscreen.infos, &menu->chk_res_high.infos);
	uic_side_right(&menu->lbl_fov.infos, &menu->slid_fov.infos);
	uic_side_right(&menu->lbl_sens.infos, &menu->slid_sens.infos);
}

inline static void	init_textures(t_ui_settings_menu *menu)
{
	menu->chk_res_min.tex_id = new_texture(200, 60);
	clear_texture(RED, menu->chk_res_min.tex_id);
	render_text_tex("960x540", DEFAULT_FONT,
		text_center("960x540", DEFAULT_FONT, 22, ivec2(100, 30)),
		ivec2(22, menu->chk_res_min.tex_id));
	finish_new_texture(menu->chk_res_min.tex_id);
	menu->chk_res_min.infos.size = get_texture_size(menu->chk_res_min.tex_id);
	menu->chk_res_med.tex_id = new_texture(200, 60);
	clear_texture(RED, menu->chk_res_med.tex_id);
	render_text_tex("1280x720", DEFAULT_FONT,
		text_center("1280x720", DEFAULT_FONT, 22, ivec2(100, 30)),
		ivec2(22, menu->chk_res_med.tex_id));
	finish_new_texture(menu->chk_res_med.tex_id);
	menu->chk_res_med.infos.size = get_texture_size(menu->chk_res_med.tex_id);
	menu->chk_res_high.tex_id = new_texture(200, 60);
	clear_texture(RED, menu->chk_res_high.tex_id);
	render_text_tex("1920x1080", DEFAULT_FONT,
		text_center("1920x1080", DEFAULT_FONT, 22, ivec2(100, 30)),
		ivec2(22, menu->chk_res_high.tex_id));
	finish_new_texture(menu->chk_res_high.tex_id);
	menu->chk_res_high.infos.size = \
		get_texture_size(menu->chk_res_high.tex_id);
	menu->chk_res_fullscreen.tex_id = new_texture(200, 60);
	clear_texture(RED, menu->chk_res_fullscreen.tex_id);
	render_text_tex("fullscreen", DEFAULT_FONT,
		text_center("fullscreen", DEFAULT_FONT, 22, ivec2(100, 30)),
		ivec2(22, menu->chk_res_fullscreen.tex_id));
	finish_new_texture(menu->chk_res_fullscreen.tex_id);
	menu->chk_res_fullscreen.infos.size = \
		get_texture_size(menu->chk_res_fullscreen.tex_id);
}

inline static void	init_current_res_checkbox(t_ui_settings_menu *menu)
{
	t_settings	*settings;

	settings = get_settings();
	if (settings->win_w == 960)
		menu->chk_res_min.checked = TRUE;
	else if (settings->win_w == 1280)
		menu->chk_res_med.checked = TRUE;
	else
		menu->chk_res_high.checked = TRUE;
}
