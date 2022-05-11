/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:37:04 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/11 19:19:28 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "colors.h"
# include "libft.h"

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

typedef enum e_flags
{
	MAIN_MENU = 0,
	DEBUG_UI = 1,
	NEW_GAME = 2,
	PAUSE_MENU = 4
}	t_flags;

int			ui_main_menu(void);

void		show_slider(t_slider *slider);
void		update_slider(t_slider *slider, int mx, int my);

void		fps_counter(void);

void		update_ui_flags(uint8_t flag);

void		put_text(t_mlx *app, t_vec2 pos, int color, char *str);
int			str_px_size(char *str);

int			put_xpm_to_window(char *path, t_vec2 pos);

#endif
