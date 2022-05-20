/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:37:04 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 17:55:18 by cybattis         ###   ########.fr       */
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

/* Zoom slider */
# define SLIDER_PAD		5
# define SLIDER_BTN_W	20
# define SLIDER_H		20
# define SLIDER_W		75
# define SLIDER_BTN2_XO	SLIDER_BTN_W + SLIDER_PAD * 2 + SLIDER_W

# define DEBUG_UI 1

typedef struct s_mlx t_mlx;

typedef enum e_ui_state
{
	MAIN_MENU = 1,
	NEW_GAME_MENU = 2,
	PAUSE_MENU = 4,
	LOAD_MENU = 8,
	OPTION_MENU = 16,
	EDITOR_MENU = 32,
}	t_ui_state;

typedef struct s_button
{
	int64_t		tex_id;
	t_bool		displayed;
	t_bool		is_clickable;
	t_bool		hovered;
	t_bool		clicked;
	t_vec2		position;
	t_vec2		bounding_box;
	int			(*event)(struct s_button *button);
}	t_button;

typedef struct s_label
{
	int64_t		tex_id;
	t_bool		displayed;
	t_vec2		position;
}	t_label;

typedef struct s_img_box
{
	int64_t		tex_id;
	t_bool		displayed;
	t_vec2		position;
}	t_img_box;

typedef struct s_slider
{
	int64_t		tex_id_bar;
	int64_t		tex_id_button;
	t_bool		displayed;
	t_vec2		position;
	t_bool		is_clickable;
	t_vec2		bounding_box;
	float		min;
	float		max;
	float		value;
	float		increment_size;
}	t_slider;

typedef struct s_text_box
{
	int64_t		tex_id;
	t_bool		displayed;
	t_bool		is_clickable;
	t_vec2		position;
	t_vec2		bounding_box;
	char		*str;
	int			(*event)(struct s_text_box *button);
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

typedef struct s_ui
{
	t_ui_state		state;
	t_bool			debug_ui;
	t_ui_main_menu	main_menu;
}	t_ui;

void		init_ui(void);
int			render_ui(void);
void		update_ui(t_bool mouse_clicked);

void		render_mmap(float zoom);
void		show_slider(t_slider *slider);
void		update_slider(t_slider *slider, int mx, int my);

void		print_debug(void);
void		fps_counter(void);

void		switch_debug_ui(void);

void		put_text(t_ivec2 pos, int color, char *str);
int			str_px_size(char *str);
void		print_float(float val, t_ivec2 pos, int color);
void		print_ivec(t_ivec2 v, t_ivec2 pos, int color);
void		print_vec(t_vec2 v, t_ivec2 pos, int color);
void		print_int(int val, t_ivec2 pos, int color);

t_button	create_button(
				int64_t tex_id,
				t_vec2 pos,
				int (*event)(struct s_button *button),
				t_bool displayed);
void		ui_button_update(t_button *button, t_bool mouse_clicked);

#endif
