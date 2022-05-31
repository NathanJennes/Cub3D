/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:33:14 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/31 13:15:26 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "mlx.h"
# include "libft.h"
# include "texture.h"
# include "ui.h"
# include "io.h"
# include "font.h"
# include "profiling.h"

# ifdef __linux__
#  include <inttypes.h>
#  include <float.h>
#  define MAXFLOAT FLT_MAX
# endif

# define WIN_W		1920
# define WIN_H		1080
# define HALFW_W	960
# define HALFW_H	540

# define MAX_KEYCODE 1024
# define MAX_MOUSE_BUTTONS 5

# define PLAYER_SPEED	0.5

# define WALL		1
# define EMPTY		0
# define VOID		-1

# define CELL_SIZE	20

# define MOUSE_DEBUG	0

# define MENU 		0
# define IN_GAME	1
# define PAUSE		2

typedef struct s_mouse
{
	t_ivec2	position;
	t_bool	buttons[MAX_MOUSE_BUTTONS];
}	t_mouse;

typedef struct s_map_info
{
	int64_t		width;
	int64_t		height;
	t_vec2		spawn_pos;
	char		spawn_dir;
	t_vec3		ceiling_color;
	t_vec3		floor_color;
	char		*no_tex;
	char		*ea_tex;
	char		*so_tex;
	char		*we_tex;
	int			**map;
	char		**map_raw;
}	t_map_info;

typedef struct s_frame
{
	void		*img;
	char		*addr;
	int			bits_pp;
	int			line_length;
	int			endian;
}	t_frame;

typedef struct s_ray
{
	double		distance;
	t_vec2		hit_pos;
	t_bool		hit;
	int			side;
	t_vec2		ray;
}	t_ray;

typedef struct s_player
{
	t_vec2		world_pos;
	t_vec2		cell_pos;
	t_ivec2		map_pos;
	double		direction;
	t_vec2		forward;
	t_vec2		right;
	t_ray		last_ray;
	t_vec2		plane_inc;
}	t_player;

typedef struct s_settings
{
	int			fov;
	int			win_h;
	int			win_w;
}	t_settings;

typedef struct s_light	t_light;

typedef struct s_gamestate
{
	char		*name;
	t_map_info	map;
	t_player	player;
	t_light		*lights;
	int64_t		light_count;
}	t_gamestate;

typedef struct s_wall
{
	int64_t		origin;
	int64_t		size;
	int64_t		offset;
	int64_t		real_size;
}	t_wall;

typedef struct s_math
{
	double		r_fov;
	double		r_vfov;
	double		r_halffov;
	double		base_angle;
	double		plane_len;
	double		plane_dist;
}	t_math;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_frame				frame;
	t_gamestate			gamestate;
	t_settings			settings;
	t_mouse				mouse;
	t_gamestate			*savegames;
	size_t				savegames_count;
	t_gamestate			*maps;
	int64_t				maps_count;
	int64_t				last_time;
	int64_t				start_time;
	int8_t				game_state;
	t_ui				ui;
	t_texture_manager	texture_manager;
	t_font_manager		font_manager;
	t_bool				keys[MAX_KEYCODE];
	t_math				pc;
}	t_mlx;

/* core.c */
void		init_window(char *win_name);
int			close_app(void);
void		error_close_app(void);
void		check_leaky_errors(void);
void		init_math(void);

/* window.c */
void		destroy_window(void);

/* initialization */
void		init_app(void);
void		init_gc(void);

/* main_loop.c */
int			main_loop(void);

/* hooks.c.c */
int			mouse_move_hooks(int x, int y, void *unused);

/* Keys */
t_bool		is_key_down(int keycode) NOPROF;

/* Mouse */
t_bool		is_mouse_down(int button) NOPROF;

void		cub_update_mouse_pos(int x, int y) NOPROF;
t_ivec2		cub_get_mouse_position(void) NOPROF;

void		update_player_vectors(t_player *player) NOPROF;
void		update_player(t_player *player) NOPROF;

/* getters */
t_mlx				*get_app(void) NOPROF;
t_frame				*get_frame(void) NOPROF;
t_map_info			*get_map_infos(void) NOPROF;
t_player			*get_player(void) NOPROF;
void				*get_mlx(void) NOPROF;
t_ui				*get_ui(void) NOPROF;
t_settings			*get_settings(void) NOPROF;
t_math				*get_math(void) NOPROF;
t_texture_manager	*get_texture_manager(void) NOPROF;
t_light				*get_lights(void) NOPROF;

#endif
