/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:33:14 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/13 11:05:56 by cybattis         ###   ########.fr       */
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

# define PLAYER_SPEED	10

# define WALL		1
# define EMPTY		0
# define VOID		-1

# define BKGD_COLOR	0x0037464B

# define CELL_WIDTH		50
# define CELL_HEIGHT	50

# define MOUSE_DEBUG	1

# define MENU 		0
# define IN_GAME	1
# define PAUSE		2

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
	u_int8_t	flags;
	t_vec2		select_bar_pos;
	t_slider	map_scale_slider;
}	t_ui;

typedef struct s_mouse
{
	int	pos_x;
	int	pos_y;
}	t_mouse;

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
	int			width;
	int			height;
	t_frame		frame;
	t_mouse		mouse;
	t_map_info	map;
	t_player	player;
	int64_t		start_time;
	int8_t		game_state;
	t_ui		ui;
}	t_mlx;

/* core.c */
void		init_window(char *win_name);
int			close_app(void);
void		error_close_app(void);
void		check_leaky_errors(void);

/* initialization */
int			is_legal_file(int argc, char **argv);
void		init_app(char *file);
void		init_gc(void);

/* main_loop.c */
int			main_loop(void);

/* hooks.c.c */
int			key_hooks(int keycode);
int			mouse_hooks(int mousecode, int x, int y);

void		cub_get_mouse_pos(t_mlx *app);

/* getters */
t_mlx		*get_app(void);
t_frame		*get_frame(void);
t_map_info	*get_map_infos(void);
t_player	*get_player(void);
void		*get_mlx(void);
t_ui		*get_ui(void);

#endif
