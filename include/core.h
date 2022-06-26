/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:33:14 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/26 17:22:49 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <pthread.h>

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

# define MAX_KEYCODE 1024
# define MAX_MOUSE_BUTTONS 5

# define PLAYER_SPEED	40

# define WALL		1
# define EMPTY		0
# define VOID		-1

# define CELL_SIZE		20
# define COLLISION_PAD	3

# define RENDER_WORKER_COUNT 4

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

typedef struct s_debug
{
	t_ivec2	dx;
	t_ivec2	dy;
}	t_debug;

typedef union u_rgb
{
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	t;
	};
	uint32_t	color;
}	t_rgb;

typedef struct s_mouse
{
	t_ivec2	position;
	t_bool	buttons[MAX_MOUSE_BUTTONS];
	t_ivec2	delta;
}	t_mouse;

typedef struct s_light	t_light;

typedef struct s_sprite
{
	t_vec3	pos;
	t_ivec2	size;
	int64_t	tex_id;
	t_vec3	color;
	int64_t	id;
}	t_sprite;

typedef struct s_sprite_manager
{
	t_sprite	*sprites;
	int64_t		sprite_count;
	double		*angle_lookup;
}	t_sprite_manager;

typedef struct s_map_info
{
	int64_t		width;
	int64_t		height;
	t_vec2		spawn_pos;
	char		spawn_dir;
	t_rgb		ceiling;
	t_rgb		floor;
	int64_t		tx_list[4];
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
	t_vec2		direction;
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
	t_vec2		plane_inc;
}	t_player;

typedef struct s_settings
{
	int			fov;
	int			win_h;
	int			win_w;
	int			halfw_h;
	int			halfw_w;
	int			desired_win_h;
	int			desired_win_w;
	double		cam_sensitivity;
	double		win_slice;
	double		win_two_slice;
	double		max_dist;
	double		max_lerp;
	char		*last_save;
}	t_settings;


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
	int64_t		screen_origin;
	int64_t		size;
	int64_t		wall_origin;
	int64_t		real_size;
}	t_wall;

typedef struct s_math
{
	double		r_fov;
	double		r_vfov;
	double		r_half_vfov;
	double		r_half_fov;
	double		base_angle;
	double		plane_len;
	double		plane_dist;
}	t_math;

typedef enum e_app_state
{
	IN_MENU,
	IN_GAME
}	t_app_state;

typedef struct s_renderer
{
	t_bool			multithreading;
	t_bool			running;
	pthread_mutex_t	running_lock;
	pthread_mutex_t	locks[RENDER_WORKER_COUNT];
	pthread_mutex_t	working_lock[RENDER_WORKER_COUNT];
	pthread_t		workers[RENDER_WORKER_COUNT];
	double			*depth_buffer;
}	t_renderer;

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
	double				delta_time;
	t_app_state			state;
	t_ui				ui;
	t_texture_manager	texture_manager;
	t_font_manager		font_manager;
	t_sprite_manager	sprite_manager;
	t_bool				keys[MAX_KEYCODE];
	t_math				pc;
	t_renderer			renderer;
	t_debug				debug;
	t_bool				mandatory;
	int64_t				lamp_tex_id;
}	t_mlx;

//TODO: quand on se deplace en diagonale, la minimap shake

/* core.c */
void 		init_mlx(t_mlx *app);
void		init_window(char *win_name);
int			close_app(void);
void		error_close_app(void);
void		check_leaky_errors(void);
void		update_precalc(void);

/* window.c */
void		destroy_window(void);

/* initialization */
void		init_app(char *path);
void		init_gc(void);

/* main_loop.c */
int			main_loop(void);
void		render_main_menu_background(void);

/* hooks.c.c */
int			mouse_move_hooks(int x, int y, void *unused);

/* Keys */
t_bool		is_key_down(int keycode) NOPROF;

void		is_colliding(t_vec2 future_pos);

/* Mouse */
t_bool		is_mouse_down(int button) NOPROF;

void		cub_update_mouse_pos(int x, int y) NOPROF;
t_ivec2		get_mouse_position(void) NOPROF;
void		reset_mouse_pos(void);
void		update_player_vectors(t_player *player) NOPROF;
void		update_player_direction(t_player *player, double delta_time, t_bool handle_input) NOPROF;
void		update_player(t_player *player, t_bool handle_input) NOPROF;
t_bool		is_player_position_legal(t_gamestate *gamestate) NOPROF;

/* Sprites */
void		init_sprite_manager(void) NOPROF;
void		add_sprite_to_current_game(t_sprite sprite) NOPROF;
void		clear_sprite_manager(void) NOPROF;
void		generate_sprites_for_new_map(void);
void		render_sprites(void);

double		get_depth_at(int64_t i) NOPROF;
void		set_depth_at(int64_t i, double distance) NOPROF;

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
