/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:33:14 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/15 14:55:43 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "mlx.h"
# include "libft.h"
# include "texture.h"
# include "error.h"
# include "io.h"

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

typedef struct s_gamestate
{
	t_map_info	map;
	t_player	player;
}	t_gamestate;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_frame				frame;
	t_gamestate			gamestate;
	t_gamestate			*savegames;
	size_t				savegames_count;
	t_gamestate			*maps;
	size_t				maps_count;
	t_slider			map_scale_slider;
	int64_t				start_time;
	u_int8_t			ui_flags;
	t_texture_manager	texture_manager;
	t_error				last_error;
}	t_mlx;

/* core.c */
void		init_window(char *win_name);
int			close_app(void);
void		error_close_app(void);
void		check_leaky_errors(void);

/* window.c */
void destroy_window();

/* initialization */
int			is_legal_file(int argc, char **argv);
void		init_app(char *file);
void		init_gc(void);

/* main_loop.c */
int			main_loop(void);

/* hooks.c.c */
int			key_hooks(int keycode);
int			mouse_hooks(int mousecode, int x, int y);

/* getters */
t_mlx		*get_app(void);
t_frame		*get_frame(void);
t_map_info	*get_map_infos(void);
t_player	*get_player(void);
void		*get_mlx(void);

#endif
