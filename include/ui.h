/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:37:04 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/15 17:35:51 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "libft.h"
# include "texture.h"
# include "colors.h"
# include "bool.h"
# include "profiling.h"

# ifdef __linux__
#  include <stdint.h>
# endif

/* Minimap */
# define MMAP_PAD			20
# define MMAP_ZOOM_FACTOR	30
# define MMAP_PLAYER_DIAM	6

typedef struct s_mlx	t_mlx;

typedef enum e_ui_state
{
	MAIN_MENU = 1,
	NEW_GAME_MENU = 2,
	PAUSE_MENU = 4,
	LOAD_MENU = 8,
	OPTION_MENU = 16,
	EDITOR_MENU = 32,
}	t_ui_state;

typedef struct s_mmap
{
	int64_t		mmap_w;
	int64_t		mmap_h;
	int64_t		mmap_halfw;
	int64_t		mmap_halfh;
}	t_mmap;

typedef struct s_ui_component
{
	t_ivec2	pos;
	t_ivec2	size;
	t_bool	displayed;
	int64_t	pad_up;
	int64_t	pad_right;
	int64_t	pad_down;
	int64_t	pad_left;
}	t_ui_component;

typedef struct s_button
{
	t_ui_component	infos;
	int64_t			tex_id;
	t_bool			is_clickable;
	t_bool			hovered;
	t_bool			clicked;
	int				(*event)(struct s_button *button);
}	t_button;

typedef struct s_checkbox
{
	t_ui_component	infos;
	int64_t			tex_id;
	t_bool			is_clickable;
	t_bool			hovered;
	t_bool			checked;
	t_bool			clicked;
	int				(*event_checked)(struct s_checkbox *checkbox);
	int				(*event_unchecked)(struct s_checkbox *checkbox);
}	t_checkbox;

typedef struct s_label
{
	t_ui_component	infos;
	char			*text;
	int64_t			tex_id;
}	t_label;

typedef struct s_img_box
{
	t_ui_component	infos;
	int64_t			tex_id;
}	t_img_box;

typedef struct s_slider
{
	t_ui_component	infos;
	int64_t			tex_id_bar;
	int64_t			tex_id_cursor;
	double			min;
	double			max;
	double			value;
	int64_t			cursor_pos_x;
	t_bool			selected;
	t_bool			hovered;
}	t_slider;

typedef struct s_text_box
{
	t_ui_component	infos;
	int64_t			tex_id;
	t_bool			is_clickable;
	char			*str;
	int				(*event)(struct s_text_box *button);
}	t_text_box;

typedef struct s_ui_main_menu
{
	t_img_box	title;
	t_button	btn_continue;
	t_button	btn_new_game;
	t_button	btn_load;
	t_button	btn_editor;
	t_button	btn_option;
	t_button	btn_exit;
}	t_ui_main_menu;

typedef struct s_ui_new_game_menu
{
	int64_t		selected_save;
	int64_t		first_save_offset;
	t_button	btn_back;
	t_button	btn_up;
	t_button	btn_down;
	t_button	btn_start;
	t_checkbox	btn_save[5];
}	t_ui_new_game_menu;

typedef struct s_ui_settings_menu
{
	t_slider	slid_fov;
	t_label		lbl_fov;
	t_slider	slid_sens;
	t_label		lbl_sens;
	t_checkbox	chk_res_min;
	t_checkbox	chk_res_med;
	t_checkbox	chk_res_high;
	t_checkbox	chk_res_fullscreen;
	t_button	btn_back;
}	t_ui_settings_menu;

typedef struct s_ui
{
	t_ui_state			state;
	t_bool				debug;
	t_ui_main_menu		main_menu;
	t_ui_new_game_menu	new_game_menu;
	t_ui_settings_menu	settings_menu;
	t_mmap				minimap;
}	t_ui;

/* Core */
void			init_ui(void);
int				render_ui(void);
void			update_ui(void);

void			fps_counter(void);
void			print_debug(void);

void			switch_debug_ui(void);

int64_t			str_px_size(char *str);
int64_t			str_px_size(char *str);
void			print_double(double val, char *font, int size, t_ivec2 pos);
void			print_int(int val, char *font, int size, t_ivec2 pos);
void			print_vec2(t_vec2 v, char *font, int size, t_ivec2 pos);
void			print_ivec2(t_ivec2 v, char *font, int size, t_ivec2 pos);

/* Main Menu */
void			init_main_menu(void);
void			render_main_menu(void);
void			update_main_menu(void);

/* New game menu */
void			init_new_game_menu(void);
void			render_new_game_menu(void);
void			update_new_game_menu(void);
void			refresh_new_game_menu(void);

/* Settings menu */
void			init_settings_menu(void);
void			render_settings_menu(void);
void			update_settings_menu(void);

/* Minimap */
void			render_minimap(double zoom);

/* Ui elements */
t_button		create_button(char *texture_path, t_ivec2 pos,
					int (*event)(struct s_button *button));
void			update_ui_button(t_button *button);
void			render_ui_button(t_button *button);
void			update_ui_button_click_begin(t_button *button, int mouse_btn);
void			update_ui_button_click_end(t_button *button, int mouse_btn);

t_checkbox		create_checkbox(char *texture_path, t_ivec2 pos,
					int (*event_checked)(struct s_checkbox *checkbox),
					int (*event_unchecked)(struct s_checkbox *checkbox));
void			update_ui_checkbox(t_checkbox *checkbox);
void			render_ui_checkbox(t_checkbox *checkbox);
void			update_ui_checkbox_click_begin(t_checkbox *checkbox, int mouse_btn);
void			update_ui_checkbox_click_end(t_checkbox *checkbox, int mouse_btn);

t_img_box		create_img_box(char *texture_path, t_ivec2 pos);
void			render_ui_img_box(t_img_box *box);

t_label			create_label(t_ivec2 pos, char *text, t_ivec2 size);
void			render_ui_label(t_label *label);
void			update_ui_label_text(t_label *label, char *text);

t_slider		create_slider(t_ivec2 pos, t_ivec2 size, t_vec3 min_max_val);
void			render_ui_slider(t_slider *slider);
void			update_ui_slider(t_slider *slider);
void			update_ui_slider_click_begin(t_slider *slider, int mouse_btn);
void			update_ui_slider_click_end(t_slider *slider, int mouse_btn);

/* Ui positionning */
t_ui_component	*uic_center_win_w(t_ui_component *comp) NOPROF;
t_ui_component	*uic_center_win_h(t_ui_component *comp) NOPROF;
t_ui_component	*uic_center_win(t_ui_component *comp) NOPROF;

t_ui_component	*uic_padding_up(t_ui_component *comp, int64_t pad) NOPROF;
t_ui_component	*uic_padding_right(t_ui_component *comp, int64_t pad) NOPROF;
t_ui_component	*uic_padding_down(t_ui_component *comp, int64_t pad) NOPROF;
t_ui_component	*uic_padding_left(t_ui_component *comp, int64_t pad) NOPROF;
t_ui_component	*uic_padding(t_ui_component *comp, t_ivec2 td, t_ivec2 lr) NOPROF;

t_ui_component	*uic_below(t_ui_component *comp, t_ui_component *other) NOPROF;
t_ui_component	*uic_above(t_ui_component *comp, t_ui_component *other) NOPROF;
t_ui_component	*uic_side_left(t_ui_component *comp, t_ui_component *other) NOPROF;
t_ui_component	*uic_side_right(t_ui_component *comp, t_ui_component *other) NOPROF;

#endif
