/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:37:04 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/15 16:04:45 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "texture.h"
# include "colors.h"

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

# define DEBUG_UI 255

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

typedef struct s_slider
{
	int		displayed;
	t_vec2	pos;
	float	increment_size;
	float	min;
	float	max;
	float	value;
}	t_slider;

typedef struct s_ui
{
	t_ui_state			state;
	u_int8_t			flags;
	t_vec2				select_bar_pos;
	t_slider			map_scale_slider;
}	t_ui;

void		init_ui(void);
int			ui_manager(void);

void		render_mmap(float zoom);
void		show_slider(t_slider *slider);
void		update_slider(t_slider *slider, int mx, int my);

void		fps_counter(void);

void		update_ui_flags(uint8_t flag);

void		put_text(t_mlx *app, t_vec2 pos, int color, char *str);
int			str_px_size(char *str);

int			put_xpm_to_window(char *path, t_vec2 pos);

#endif
