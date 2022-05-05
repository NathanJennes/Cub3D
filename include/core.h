/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:33:14 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/05 16:25:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "mlx.h"
# include "libft.h"

# ifdef FULL_SCREEN
#  define WIN_W		1920
#  define WIN_H		1080
# else
#  define WIN_W		960
#  define WIN_H		540
# endif

# define MMAP_W				100
# define MMAP_H				50
# define MMAP_PAD			20
# define MMAP_ZOOM_FACTOR	20
# define MMAP_PLAYER_DIAM	10

# define CELL_WIDTH		50
# define CELL_HEIGHT	50

# define PLAYER_SPEED	10

# define WALL		1
# define EMPTY		0
# define VOID		-1

# define BKGD_COLOR	0x0037464B

# define SLIDER_PAD		5
# define SLIDER_BTN_W	20
# define SLIDER_H		20
# define SLIDER_W		75
# define SLIDER_BTN2_XO	SLIDER_BTN_W + SLIDER_PAD * 2 + SLIDER_W

typedef struct s_slider
{
	int		displayed;
	t_vec2	pos;
	float	increment_size;
	float	min;
	float	max;
	float	value;
}	t_slider;

typedef struct s_map_info
{
	size_t	width;
	size_t	height;
	t_vec2	spawn_pos;
	char	spawn_dir;
	t_vec3	ceiling_color;
	t_vec3	floor_color;
	char	*no_tex;
	char	*ea_tex;
	char	*so_tex;
	char	*we_tex;
	int		**map;
	char	**map_raw;
}	t_map_info;

typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bits_pp;
	int		line_length;
	int		endian;
}	t_frame;

typedef struct s_player
{
	t_vec2	pos;
	float	direction;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_frame		frame;
	t_map_info	map;
	t_player	player;
	t_slider	map_scale_slider;
}	t_mlx;

/* core.c */
void		init_window(char *win_name);
int			close_app(void);
void		error_close_app(void);
int			error_code_msg(int code, char *msg);
void		check_leaky_errors(void);

/* initialization */
int			is_legal_file(int argc, char **argv);
void		init_app(char *file);
void		init_gc(void);

/* draw.c */
void		clear_screen(int color);
int			main_loop(void);
void		mlx_pixel_put_img(int x, int y, int color);
int			color_lerp(int col1, int col2, float value);

/* colors_utils.c */
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

/* rendering */
void		render_mmap(float zoom);
void		render_circle(t_vec2 pos, float diameter, int color);
void		render_rect(t_vec2 pos, t_vec2 size, int color);
void		render_line(t_vec2 start, t_vec2 end, int col1, int col2);
int			outside_mmap_bounds(int x, int y);

/* hooks.c.c */
int			key_hooks(int keycode);
int			mouse_hooks(int mousecode, int x, int y);

/* getters */
t_mlx		*get_app(void);
t_frame		*get_frame(void);
t_map_info	*get_map_infos(void);
t_player	*get_player(void);
void		*get_mlx(void);

/* UI */
void		show_slider(t_slider *slider);
void		update_slider(t_slider *slider, int mx, int my);

#endif
