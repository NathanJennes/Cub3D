/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:33:14 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/22 14:51:05 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "mlx.h"

# ifdef FULL_SCREEN
#  define WIN_W		1920
#  define WIN_H		1080
# else
#  define WIN_W		960
#  define WIN_H		540
# endif

# define BKGD_COLOR	0x0037464B

typedef struct s_frame {
	void	*img;
	char	*addr;
	int		bits_pp;
	int		line_length;
	int		endian;
}	t_frame;

typedef struct s_mlx {
	void		*mlx;
	void		*win;
	t_frame		frame;
}	t_mlx;

/* core.c */
void		init_window(t_mlx *app, char *win_name);
int			close_app(t_mlx *app);
void		error_close_app(t_mlx *app);

/* draw.c */
void		clear_screen(t_mlx *app, int color);
int			draw_frame(t_mlx *app);
void		mlx_pixel_put_img(t_frame *frame, int x, int y, int color);

/* hooks.c.c */
int			key_hooks(int keycode, t_mlx *app);
int			mouse_hooks(int mousecode, int x, int y);

#endif
