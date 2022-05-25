/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:37:04 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/25 17:38:00 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "libft.h"
# include "texture.h"
# include "colors.h"
# include "bool.h"

# ifdef __linux__
#  include <stdint.h>
# endif

/* Minimap */
# define MMAP_W				100
# define MMAP_H				50
# define MMAP_PAD			20
# define MMAP_ZOOM_FACTOR	20
# define MMAP_PLAYER_DIAM	10

# define DEBUG_UI 1

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

typedef struct s_label
{
	t_ui_component	infos;
	char			*text;
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
	float			min;
	float			max;
	float			value;
	int64_t			cursor_pos_x;
	t_bool			selected;
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
	t_button	btn_save[5];
}	t_ui_new_game_menu;

typedef struct s_ui
{
	t_ui_state			state;
	uint8_t				debug_ui;
	t_ui_main_menu		main_menu;
	t_ui_new_game_menu	new_game_menu;
}	t_ui;

/* Core */
void			init_ui(void);
int				render_ui(void);
void			update_ui(void);

void			render_mmap(float zoom);

void			fps_counter(void);
void		print_debug(void);
void		fps_counter(void);

void			update_ui_flags(uint8_t flag);
void			switch_debug_ui(void);

int				str_px_size(char *str);
void			put_text(t_ivec2 pos, int color, char *str);
int				str_px_size(char *str);
void			print_float(float val, t_ivec2 pos, int color);
void			print_ivec(t_ivec2 v, t_ivec2 pos, int color);
void			print_vec(t_vec2 v, t_ivec2 pos, int color);
void			print_int(int val, t_ivec2 pos, int color);

/* Main Menu */
void			init_main_menu(void);
void			render_main_menu(void);
void			update_main_menu(void);

void			init_new_game_menu(void);
void			render_new_game_menu(void);
void			update_new_game_menu(void);
void			refresh_new_game_menu(void);

/* Ui elements */
t_button		create_button(char *texture_path, t_ivec2 pos,
					int (*event)(struct s_button *button));
void			update_ui_button(t_button *button);
void			render_ui_button(t_button *button);
void			update_ui_button_click_begin(t_button *button, int mouse_btn);
void			update_ui_button_click_end(t_button *button, int mouse_btn);

t_img_box		create_img_box(char *texture_path, t_ivec2 pos);
void			render_ui_img_box(t_img_box *box);

t_label			create_label(t_ivec2 pos, char *text);
void			render_label(t_label *label);

t_slider		create_slider(t_ivec2 pos, t_ivec2 size, float min, float max);
void			render_ui_slider(t_slider *slider);
void			update_ui_slider(t_slider *slider);
void			update_ui_slider_click_begin(t_slider *slider, int mouse_btn);
void			update_ui_slider_click_end(t_slider *slider, int mouse_btn);

/* Ui positionning */
t_ui_component	*uic_center_win_w(t_ui_component *comp);
t_ui_component	*uic_center_win_h(t_ui_component *comp);
t_ui_component	*uic_center_win(t_ui_component *comp);

t_ui_component	*uic_padding_up(t_ui_component *comp, int64_t pad);
t_ui_component	*uic_padding_right(t_ui_component *comp, int64_t pad);
t_ui_component	*uic_padding_down(t_ui_component *comp, int64_t pad);
t_ui_component	*uic_padding_left(t_ui_component *comp, int64_t pad);
t_ui_component	*uic_padding(t_ui_component *comp, t_ivec2 td, t_ivec2 lr);

t_ui_component	*uic_below(t_ui_component *comp, t_ui_component *other);
t_ui_component	*uic_above(t_ui_component *comp, t_ui_component *other);
t_ui_component	*uic_side_left(t_ui_component *comp, t_ui_component *other);
t_ui_component	*uic_side_right(t_ui_component *comp, t_ui_component *other);

#endif
